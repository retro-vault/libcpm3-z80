.PHONY:	all
all:

	# Compile hello.c
	sdcc -o ../build/hello.rel \
		-c --std-c11 -mz80 \
		--nostdinc -I ../include \
		hello.c
		
	# Link both
	sdcc -o ../build/hello.ihx \
		-mz80 --code-loc 0x0100 \
		--no-std-crt0 --nostdlib \
		-L../bin -llibcpm3-z80 -llibsdcc-z80 \
		../bin/crt0cpm3-z80.rel ../build/hello.rel
	
	# SDCC data segment fix. Update .lk file and link again.
	sed '/-b _DATA = 0x8000/d' ../build/hello.lk > ../build/hello.link
	sdldz80 -nf ../build/hello.link

	# Finally, convert ihx to binary
	sdobjcopy -I ihex -O binary ../build/hello.ihx ../bin/hello.com
