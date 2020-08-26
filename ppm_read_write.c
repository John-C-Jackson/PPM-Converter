#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(char *s)
{
    printf("\nError: %s\n\n", s);
    printf("Usage:\n");
    printf("./ppmrw FORMAT_# INPUT_PPM OUTPUT_PPM\n\n");
    exit(1);
}

#define col 255

uint8_t color[] =
{
    col, col, col,
    col, col, 0,
    0, col, col,
    0, col, 0,
    col, 0, col,
    col, 0, 0,
    0, 0, col
};

int main(int argc, char *argv[])
{
    if (argc != 4) // check correct number of arguments
    {
        fail("Wrong number of arguments.");
    }

    int format = atoi(argv[1]);

    if ((format != 3) && (format != 6)) // check magic number = 3 or 6
    {
        fail("PPM format must be either 3 or 6.");
    }

    if ((strstr(argv[2], ".ppm") == NULL) || (strstr(argv[3], ".ppm") == NULL)) // check file extensions
    {
        fail("Input and output files must be of type .ppm.");
    }

    FILE *infile = fopen(argv[2], "rb");
    FILE *outfile = fopen(argv[3], "wb");
}
