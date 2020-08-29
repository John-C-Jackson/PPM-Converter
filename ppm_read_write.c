#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel;

typedef struct PPM
{
    int width;
    int height;
    struct Pixel pixel;
} ppm;

void fail(char *s)
{
    printf("\nError: %s\n\n", s);
    printf("Usage:\n");
    printf("./ppmrw FORMAT_# INPUT_PPM OUTPUT_PPM\n\n");
    exit(1);
}

unsigned int *read_p3(FILE *file_in, int width, int height)
{
    int i, j, pixmap_size;
    uint8_t *pixmap, *pixel;

    // allocate memory for pixmap
    pixmap_size = width * height * 3;
    pixmap = malloc(pixmap_size);
    pixel = pixmap;

    // read P3
    return 0;
}

unsigned int *read_p6(FILE *file_in, int width, int height)
{
    return 0;
}

void write_p3(unsigned char *file_out) // this and write_p6 might have an additional argument (int *pixmap)
{
    // fprintf
    return;
}

void write_p6(unsigned char *file_out)
{
    /*
    fwrite(pixmap, 1, bar_width * 7 * bar_height * 4, file);
    fclose(file);
    */
    return;
}

int main(int argc, char *argv[])
{
    const int MAX = 100;
    int maxcolor, dimensions, width, height, out_format;
    char buffer[100], hash;
    char *line;
    bool p3 = false, p6 = false;
    FILE *infile;
    const char *outfile;

    // check correct number of arguments
    if (argc != 4)
    {
        fail("Wrong number of arguments.");
    }

    out_format = atoi(argv[1]);

    // check user-supplied format is 3 or 6
    if ((out_format != 3) && (out_format != 6))
    {
        fail("PPM format must be either 3 or 6.");
    }

    // check file extensions
    if ((strstr(argv[2], ".ppm") == NULL) || (strstr(argv[3], ".ppm") == NULL))
    {
        fail("Input and output files must be of type .ppm.");
    }

    infile = fopen(argv[2], "rb");
    outfile = argv[3];

    if (infile == NULL)
    {
        fail("The input file is empty.");
    }

    // get magic number
    line = fgets(buffer, MAX, infile);
    if (strcmp(line, "P3\n") == 0)
    {
        p3 = true;
    }
    else if (strcmp(line, "P6\n") == 0)
    {
        p6 = true;
    }
    printf("%s\n", line);

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
    line = fgets(buffer, MAX, infile);
    printf("%s\n", line);

    if (strncmp(line, "255", 3) != 0)
    {
        fail("Wrong max color.\n");
    }

    // call either read_p6 or read_p3
    if (p3)
    {
        printf("convert data to P%d\n", out_format);
        printf("call read_p3\n");
        read_p3(infile, width, height);
    }
    else if (p6)
    {
        printf("convert data to P%d\n", out_format);
        printf("call read_p6\n");
        read_p6(infile, width, height);
    }
    else
    {
        fail("Incorrect header data.\n");
    }
}
