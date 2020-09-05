#include "WaveAudio.h"

WaveAudio::WaveAudio()
{
}

WaveAudio::WaveAudio(char *fileName)
{
	Buffer_WAV = new short int[8192*2];
	Name_WAV = fileName;
	File_WAV = fopen(Name_WAV, "rb");
	byte *Header = new byte[44];
	memset(Header, 0, 44);
	fread(Header, 1, 44, File_WAV);
	chunkID[0] = Header[0]; chunkID[1] = Header[1]; chunkID[2] = Header[2]; chunkID[3] = Header[3];
	chunkSize = (Header[7] << 24) | (Header[6] << 16) | (Header[5] << 8) | (Header[4]);
	format[0] = Header[8]; format[1] = Header[9]; format[2] = Header[10]; format[3] = Header[11];
	subchunk1ID[0] = Header[12]; subchunk1ID[1] = Header[13]; subchunk1ID[2] = Header[14]; subchunk1ID[3] = Header[15];
	subchunk1Size = (Header[19] << 24) | (Header[18] << 16) | (Header[17] << 8) | (Header[16]);
	audioFormat = (Header[20]);
	numChannels = (Header[23] << 8) | (Header[22]);
	sampleRate = (Header[27] << 24) | (Header[26] << 16) | (Header[25] << 8) | (Header[24]);
	byteRate = (Header[35] << 8) | (Header[34]);
	blockAlign = (Header[33] << 8) | (Header[32]);
	bitsPerSample = (Header[35] << 8) | (Header[34]);
	subchunk2ID[0] = Header[36]; subchunk2ID[1] = Header[37]; subchunk2ID[2] = Header[38]; subchunk2ID[3] = Header[39];
	subchunk2Size = (Header[43] << 24) | (Header[42] << 16) | (Header[41] << 8) | (Header[40]);
	delete[] Header;
}

WaveAudio::~WaveAudio()
{
	delete[] Buffer_WAV;
	fclose(File_WAV);
}

int WaveAudio::getNextBuffer()
{
	memset(Buffer_WAV, 0, 8192*2*sizeof(short));
	return fread(Buffer_WAV, 2*sizeof(short), 8192, File_WAV);
}
