#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

struct HEADER
{
	uint8_t ChunkID[4];
	uint32_t ChunkSize;
	uint8_t Format[4];
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;

	uint16_t BitsPreSample;
};

struct CHUNK
{
	uint8_t ID[4];
	uint32_t size;
};

int main() {

	FILE* file_in;
	FILE* file_out;
	struct HEADER header;
	struct CHUNK chunk;
	int8_t filename[30];
	puts("Enter filename:");
	gets(filename);

	fopen_s(&file_in, filename, "rb");
	fopen_s(&file_out, "filteredwave.wav", "wb");

	fread(&header, sizeof(header), 1, file_in);

	printf("NumChannels=%i\n", header.NumChannels);
	printf("SampleRate=%i\n", header.SampleRate);
	printf("BitsPreSample=%i\n", header.BitsPreSample);

	if (header.BitsPreSample != 16) {
		printf("Audiofile isn't 16bit\n");
		system("pause");
		return 0;
	}
	fread(&chunk, sizeof(chunk), 1, file_in);
	
	uint16_t sample_size = header.BitsPreSample;
	uint32_t samples_count = chunk.size / sample_size;
	printf("Samples=%d\n", samples_count);

	fwrite(&header, sizeof(header), 1, file_out);
	fwrite(&chunk, sizeof(chunk), 1, file_out);