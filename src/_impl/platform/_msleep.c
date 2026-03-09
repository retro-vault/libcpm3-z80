/*
 * _msleep.c
 *
 * Provide the default millisecond-delay hook as an empty stub.
 * Platforms may override _msleep() with a real implementation.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
void _msleep(int millisec) {
    millisec;
}
