#include "WaveAudio.h"

WaveAudio::WaveAudio()
{
}

WaveAudio::WaveAudio(const char *FileName)
{
	WavName = FileName;

	WavBuffer = new short int[8192 * 2];

	WavFile = fopen(WavName, "rb");

	byte *Header = new byte[44];

	memset(Header, 0, 44);

	fread(Header, 1, 44, WavFile);

	NumChannels = (Header[23] << 8) | (Header[22] << 0);
	SampleRate = (Header[27] << 24) | (Header[26] << 16) | (Header[25] << 8) | (Header[24] << 0);
	BitsPerSample = (Header[35] << 8) | (Header[34] << 0);
	ByteRate = (Header[31] << 24) | (Header[30] << 16) | (Header[29] << 8) | (Header[28] << 0);

	delete[] Header;
}

int WaveAudio::GetNextBuffer()
{
	memset(WavBuffer, 0, 8192 * 2);
	return fread(WavBuffer, sizeof(short int) * 2, 8192, WavFile);
}

WaveAudio::~WaveAudio()
{
	delete[] WavBuffer;
	fclose(WavFile);
}
