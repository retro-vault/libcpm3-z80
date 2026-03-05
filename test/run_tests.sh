#!/bin/sh
#
# run_tests.sh
#
# Run CP/M .COM test binaries under RunCPM and capture results.
# Each test result is written to /src/bin/<name>.txt.
#
# Usage: run_tests.sh <name> [name ...]
#   name  - test binary name without extension (e.g. tctype)
#           must match a file in /src/bin/<name>.com
#

BINDIR=/src/bin
RESDIR=/src/bin

mkdir -p "$RESDIR"

for TEST in "$@"; do
    COM=$(echo "$TEST" | tr '[:lower:]' '[:upper:]')
    COMFILE="${BINDIR}/${TEST}.com"
    OUTFILE="${RESDIR}/${TEST}.txt"

    if [ ! -f "$COMFILE" ]; then
        printf "SKIP %s: %s not found\n" "$TEST" "$COMFILE"
        printf "SKIP %s: binary not found\n" "$TEST" > "$OUTFILE"
        continue
    fi

    # Set up RunCPM workspace: directory A/0 simulates CP/M drive A: user 0.
    WORK=$(mktemp -d)
    mkdir -p "${WORK}/A/0"
    cp "$COMFILE" "${WORK}/A/0/${COM}.COM"

    printf "Running %s ...\n" "$TEST"

    # Pipe the command into RunCPM; timeout kills hung tests after 15s.
    # awk strips the RunCPM banner and CP/M prompts, then exits (SIGPIPE to
    # RunCPM) when:
    #   a) the test summary line is seen (clean exit), or
    #   b) the test header appears a second time (crash/warm-boot loop).
    {
        cd "$WORK"
        printf '%s\r\n' "$COM" | timeout 15 RunCPM 2>/dev/null
    } | tr -d '\r' \
      | awk -v hdr="$COM:" '
            /^[A-Z][0-9]*>/          { next }
            /CP.M Emulator/          { next }
            /RunCPM Version/         { next }
            /^  CP.M Emulator/       { next }
            /Built [A-Z]/            { next }
            /^CPU is /               { next }
            /T-states|MHz/           { next }
            /BIOS at|BDOS at/        { next }
            /BIOS.BDOS/              { next }
            /^CCP |^FILEBASE/        { next }
            /^-+$/                   { next }
            /^[[:space:]]*$/         { next }
            index($0, hdr) == 1 {
                runs++
                if (runs > 1) exit
                print
                next
            }
            /^PASS all /       { print; exit }
            /^FAIL [0-9]/      { print; exit }
            { print }
        ' \
      > "$OUTFILE" 2>/dev/null || true

    rm -rf "$WORK"

    printf "=== %s ===\n" "$TEST"
    cat "$OUTFILE"
    printf "\n"
done
