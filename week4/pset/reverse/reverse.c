#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[]) {
    // Ensure proper usage
    if (argc != 3) {
        printf("Usage: reverse infile outfile\n");
        return 1;
    }

    // Open input file for reading
    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (!check_format(header) && header.audioFormat != 1) {
        printf("Bad format - please use WAV file");
        return 3;
    }

    // Open output file for writing
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 4;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    fseek(inptr, 0, SEEK_END);
    BYTE buffer[block_size];
    while (ftell(inptr) > sizeof(header)) {
        // Keep in mind that after you use fread to load in a block of data,
        // the input pointer will be pointing at the location where the read concluded.
        // In other words, the input pointer may need to be moved back two block sizes after each fread,
        // one to move back to where the fread began, and the second to move to the previous, unread block.
        fseek(inptr, -block_size, SEEK_CUR);
        fread(buffer, block_size, 1, inptr);
        fwrite(buffer, block_size, 1, outptr);
        fseek(inptr, -block_size, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
}

int check_format(WAVHEADER header) {
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E') {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header) {
    return header.numChannels * header.bitsPerSample / 8;
}