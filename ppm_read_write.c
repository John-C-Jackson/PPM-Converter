#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void fail(char *s) {
    printf("\nError: %s\n\n", s);
    printf("Usage:\n");
    printf("./ppmrw FORMAT_# INPUT_PPM OUTPUT_PPM\n\n");
    exit(1);
}

uint8_t *read_p3(FILE *file_in, int width, int height) {
    int pixmap_size = width * height * 3;
    uint8_t *pixmap = malloc(pixmap_size);
    uint8_t *pixel = pixmap;

    while (!feof(file_in)) {
        for(int i = 0; i < pixmap_size; i++) {
            fread(pixel, sizeof(uint8_t), pixmap_size, file_in);
        }
    }

    fclose(file_in);
    return pixmap;
}

uint8_t *read_p6(FILE *file_in, int width, int height) {
    int pixmap_size = width * height * 3 * sizeof(uint8_t);
    uint8_t *pixmap = malloc(pixmap_size);

    while (!feof(file_in)) {
        fread(pixmap, sizeof(uint8_t), width * height * 3, file_in);
    }

    fclose(file_in);
    return pixmap;
}

void write_p3(char *outfile, uint8_t *pixmap, int width, int height) {
    FILE *file = fopen(outfile, "wb");
    fprintf(file, "P3\n%u %u\n255\n", width, height);
/*
    fwrite(pixmap, 1, width * height * 3, file);
*/
    printf("Converted to P3\n");
    fclose(file);
    return;
}

void write_p6(char *outfile, uint8_t *pixmap, int width, int height) {
    FILE *file = fopen(outfile, "wb");
    fprintf(file, "P6\n%u %u\n255\n", width, height);

    fwrite(pixmap, 3, width * height * 3, file);

    printf("Converted to P6\n");
    fclose(file);
    return;
}

int main(int argc, char *argv[]) {
    const int MAX = 100;
    int maxcolor, dimensions, width, height, out_format;
    char buffer[100], hash;
    char *line, *outfile;
    bool p3 = false, p6 = false;
    FILE *infile;
    uint8_t *pixmap;

    // check correct number of arguments
    if (argc != 4) {
        fail("Wrong number of arguments.");
    }

    out_format = atoi(argv[1]);

    // check user-supplied format is 3 or 6
    if ((out_format != 3) && (out_format != 6)) {
        fail("PPM format must be either 3 or 6.");
    }

    // check file extensions
    if ((strstr(argv[2], ".ppm") == NULL) || (strstr(argv[3], ".ppm") == NULL)) {
        fail("Input and output files must be of type .ppm.");
    }

    infile = fopen(argv[2], "rb");
    outfile = argv[3];

    if (infile == NULL) {
        fail("The input file is empty.");
    }

    // get magic number
    line = fgets(buffer, MAX, infile);
    if (strcmp(line, "P3\n") == 0) {
        p3 = true;
    }
    else if (strcmp(line, "P6\n") == 0) {
        p6 = true;
    }
    printf("%s\n", line);

    // pass over comments
    while (1) {
        line = fgets(buffer, MAX, infile);
        hash = line[0];

        if (hash != '#') {
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

    if (strncmp(line, "255", 3) != 0) {
        fail("Wrong max color.\n");
    }

    // call either read_p3 or read_p6
    if (p3) {
        printf("convert data to P%d\n", out_format);
        printf("call read_p3\n");
        pixmap = read_p3(infile, width, height);
    }
    else if (p6) {
        printf("convert data to P%d\n", out_format);
        printf("call read_p6\n");
        pixmap = read_p6(infile, width, height);
    }
    else {
        fail("Incorrect header data.\n");
    }

    // call either write_p3 or write_p6
    if(out_format == 3) {
        printf("calling write_p3\n");
        write_p3(outfile, pixmap, width, height);
    }
    else {
        printf("calling write_p6\n");
        write_p6(outfile, pixmap, width, height);
    }
}
