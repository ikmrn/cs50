#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[]) {
    // Ensure proper usage
    // TODO #1
    if (argc != 3) {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }
    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 1) {
        printf("Input is not a WAV file.\n");
        return 4;
    }

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL) {
        printf("Could not open %s", argv[2]);
        return 5;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    const int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];
    int count = 0;

    if (fseek(inptr, block_size, SEEK_END)) {
        perror("Error using fseek");
        return 6;
    }

    int header_size = sizeof(header);
    while (ftell(inptr) - block_size > header_size) {
        if (fseek(inptr, -block_size * 2, SEEK_CUR)) {
            perror("Error using fseek");
            return 6;
        }
        fread(buffer, block_size, 1, inptr);
        fwrite(buffer, block_size, 1, outptr);
    }

    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header) {
    // TODO #4
    BYTE wav_marker[4] = "WAVE";
    BYTE *input_marker = header.format;
    for (int i = 0, n = sizeof(wav_marker); i < n; i++) {
        if (wav_marker[i] != input_marker[i]) {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header) {
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}
