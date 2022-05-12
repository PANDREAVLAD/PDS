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


	fread(&chunk, sizeof(chunk), 1, file_in);
	
	uint16_t sample_size = header.BitsPreSample / 8;
	uint32_t samples_count = chunk.size / sample_size;

	fwrite(&header, sizeof(header), 1, file_out);
	fwrite(&chunk, sizeof(chunk), 1, file_out);
	int32_t sample_buffer_L[6] = { 0, 0, 0, 0, 0, 0 };
	int32_t sample_buffer_R[6] = { 0, 0, 0, 0, 0, 0 };
	int16_t s_buf[2*SIZE];
	int16_t outputL;
	int16_t outputR;
	int16_t signalL;
	int16_t signal;

	int a0, a1, a2, b1, b2;
	int32_t coeffs[5] = { 0, 0, 0, 0, 0 };

	a0 = 0.2185718974189478;
	a1 = 0.2754975197979510;
	a2 = 0.2145185794171419;
	b1 = 0.1115854841587418;
	b2 = 0.1958794741897444;

	coeffs[0] = flt2fixd(a0);
	coeffs[1] = flt2fixd(a1);
	coeffs[2] = flt2fixd(a2);
	coeffs[3] = flt2fixd(b1);
	coeffs[4] = flt2fixd(b2);
	while (1)
	{
		size_t read_size = fread(s_buf, 2*sample_size, 128, file_in);
		
		if (!read_size)
			break;
		
		for (int n = 0; n < read_size; n++) {

			outputL = IIR(sample_buffer_L, coeffs,s_buf[2*n]);
			outputR = IIR(sample_buffer_R, coeffs, s_buf[2 * n + 1]);

			s_buf[2*n] = outputL;
			s_buf[2 * n + 1] = outputR;
		}
	....
	}
