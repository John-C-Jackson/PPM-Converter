#include <stdio.h>
#include <stdlib.h>

void fail(char *s)
{
    printf("Error: %s\n\n", s);
    printf("Usage:\n");
    printf("./ppmrw FORMAT_# INPUT_PPM OUTPUT_PPM\n\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fail("Wrong number of arguments.");
    }

    int format = atoi(argv[1]);

    if ((format != 3) && (format != 6))
    {
        fail("PPM format must be either 3 or 6.");
    }
}