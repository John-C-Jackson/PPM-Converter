#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void fail(char *s)
{
    printf("\nError: %s\n\n", s);
    printf("Usage:\n");
    printf("./ppmrw FORMAT_# INPUT_PPM OUTPUT_PPM\n\n");
    exit(1);
}

unsigned int *read_p3(FILE *file_in, int width, int height)
{
    // I think everything in read_p3 and read_p6 will be inside
    // a while loop -> while not at end of file
    return 0;
}

unsigned int *read_p6(FILE *file_in, int width, int height)
{
    return 0;
}

int write_p3(FILE *file_out) // this and write_p6 might have an additional argument (int *pixmap)
{
    // fprintf
    return 0;
}

int write_p6(FILE *file_out)
{
    return 0;
}

int main(int argc, char *argv[])
{
    const int MAX = 100;
    char buffer[100], hash, magic;
    char *magic_number, *line, *color;
    int maxcolor, dimensions, width, height;
    bool p3 = false, p6 = false;

    // check correct number of arguments
    if (argc != 4)
    {
        fail("Wrong number of arguments.");
    }

    int format = atoi(argv[1]);

    // check user-supplied format is 3 or 6
    if ((format != 3) && (format != 6))
    {
        fail("PPM format must be either 3 or 6.");
    }

    // check file extensions
    if ((strstr(argv[2], ".ppm") == NULL) || (strstr(argv[3], ".ppm") == NULL))
    {
        fail("Input and output files must be of type .ppm.");
    }

    FILE *infile = fopen(argv[2], "rb");
    FILE *outfile = fopen(argv[3], "wb");

    // get magic number
    magic_number = fgets(buffer, MAX, infile);
    if (strcmp(magic_number, "P3\n") == 0)
    {
        p3 = true;
    }
    else if (strcmp(magic_number, "P6\n") == 0)
    {
        p6 = true;
    }
    printf("%s\n", magic_number);

    // pass over comments
    while (1)
    {
        line = fgets(buffer, MAX, infile);
        hash = line[0];

        if (hash != '#')
        {
            break;
        }
    }

    // get width and height
    dimensions = sscanf(buffer, "%u %u", &width, &height);
    printf("%u\n", width);
    printf("%u\n", height);

    // get max color value
    color = fgets(buffer, MAX, infile);
    printf("%s\n", color);

    if (strncmp(color, "255", 3) != 0)
    {
        fail("Wrong max color.\n");
    }

    // call either read_p6 or read_p3
    if (p3)
    {
        printf("convert data to P%d\n", format);
        printf("call read_p3\n");
        read_p3(infile, width, height);
    }
    else if (p6)
    {
        printf("convert data to P%d\n", format);
        printf("call read_p6\n");
        read_p6(infile, width, height);
    }
    else
    {
        fail("Incorrect header data.\n");
    }
}
