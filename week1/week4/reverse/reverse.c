#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fclose(input);
        printf("Could not open file.\n");
        return 2;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    if (fread(&header, sizeof(WAVHEADER), 1, input) != 1)
    {
        fclose(input);
        printf("Could not read header.\n");
        return 3;
    }

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        fclose(input);
        printf("Invalid input file.\n");
        return 4;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        fclose(input);
        fclose(output);
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    long int block_size = get_block_size(header);

    // Write reversed audio to file
    // initiate buffer
    BYTE buffer[block_size];

    // set all elements of arr to 0
    memset(buffer, 0, sizeof(block_size));

    // reverse input and get full size od audio data
    fseek(input, -block_size, SEEK_END);


    // repeat until input pointer reach header
    while (ftell(input) >= sizeof(header))
    {
        // read one block to buffer // pointer is in the end of readed block
        fread(buffer, sizeof(uint8_t), block_size, input);

        // write buffer into block
        fwrite(buffer, sizeof(uint8_t), block_size, output);

        // move back 2 positions
        fseek(input, -2 * block_size * sizeof(uint8_t), SEEK_CUR);


    }

    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    //TODO 4
    if (memcmp(header.format, "WAVE", 4))
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.bitsPerSample * header.numChannels / 8;
}
