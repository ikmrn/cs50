#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;
int BUFFER_SIZE = 512;

int main(int argc, char *argv[]) {
    // Accept a single line command
    if (argc != 2) {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    // Open raw file
    FILE *inptr = fopen(argv[1], "rb");
    if (inptr == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }

    byte buffer[BUFFER_SIZE];
    int count = 0;

    // Create output file
    FILE *outptr = NULL;

    while (fread(buffer, 1, BUFFER_SIZE, inptr) == BUFFER_SIZE) {
        // Check for jpg file signatures and create a new file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) {
            // Close the current output file if open
            if (outptr != NULL) {
                fclose(outptr);
            }
            char *filename = malloc(12);
            snprintf(filename, sizeof(filename), "%03i.jpg", count++);
            outptr = fopen(filename, "w");

            // Check for issues with opening output file
            if (outptr == NULL) {
                fclose(inptr);
                free(filename);
                printf("Cannot create output file\n");
                return 3;
            }
            free(filename);
        }

        // Check if output not NULL and write into it if so
        if (outptr != NULL) {
            fwrite(buffer, 1, BUFFER_SIZE, outptr);
        }
    }
    if (outptr != NULL){
      fclose(outptr);
    }

    fclose(inptr);
}