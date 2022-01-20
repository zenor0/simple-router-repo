// This source code is verified on CS50 IDE
// BUT it doesn't work on my Windows PC ????
// I don't know why, and I'm confused
// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// A char variable represents a byte data
// Number of bytes in .wav header
// Assume that all the input wav files are 16-bits signed sampled.
const int HEADER_SIZE = 44;
const int WAV_SAMPLE_SIZE = 16;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t wavHeader[HEADER_SIZE];
    fread(&wavHeader, sizeof(wavHeader), 1, input);
    fwrite(&wavHeader, sizeof(wavHeader), 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
