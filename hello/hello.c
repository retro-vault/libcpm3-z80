#include <stdio.h>

void main(int argc, char *argv[]) {
    if (argc==2)
        printf("Hello %s!\n", argv[1]);
    else
        printf("Hello world!\n");
}