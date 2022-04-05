#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

struct HEADER
{
	uint8_t ChunkID[4];
	uint8_t Format[4];
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPreSample;
};

int main() {

	FILE* file_in;
	FILE* file_out;
	struct HEADER header;
	int8_t filename[30];
	gets(filename);

	fopen_s(&file_in, filename, "r");
	fopen_s(&file_out, "filteredwave.wav");

	fread(&header, sizeof(header), 1, file_in);

	printf("NumChannels=%i\n", header.NumChannels);
	printf("SampleRate=%i\n", header.SampleRate);
	printf("BitsPreSample=%i\n", header.BitsPreSample);

	if (header.BitsPreSample != 16) {
		printf("Audiofile isn't 16bit\n");
		system("pause");
		return 0;
	}