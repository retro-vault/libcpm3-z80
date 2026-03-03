/*
 * msleep.c
 *
 * Sleep for a given number of milliseconds (stub).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 17.02.2026   tstih
 *
 */

/* CP/M 3 provides no timer facility; override this function with a
   platform-specific busy-wait if millisecond delay is needed. */
void msleep(int millisec) {
    millisec;
}
