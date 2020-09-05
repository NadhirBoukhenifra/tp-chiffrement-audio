#include "CompressionMP3.h"



CompressionMP3::CompressionMP3()
{
}


CompressionMP3::~CompressionMP3()
{
}

int main()
{
	WaveAudio MyAudio("audio.wav");

	printf("Hello, World! \n");
	printf("File Name: %s \n", MyAudio.WavName);
	printf("NumChannels: %i \n", MyAudio.NumChannels);
	printf("SampleRate: %i \n", MyAudio.SampleRate);
	printf("BitsPerSample: %i \n", MyAudio.BitsPerSample);
	printf("ByteRate: %i \n", MyAudio.ByteRate);

	lame_t lame = lame_init();

	lame_set_in_samplerate(lame, MyAudio.SampleRate);

	switch (MyAudio.NumChannels)
	{
	case 1:
		lame_set_mode(lame, MONO);
		break;
	case 2:
		lame_set_mode(lame, STEREO);
		break;
	}

	lame_set_brate(lame, MyAudio.ByteRate / 1000);

	lame_init_params(lame);
	
	unsigned char MP3Buffer[8192];

	FILE *mp3File;

	string mp3Name = (string)MyAudio.WavName; //name.wav
	mp3Name.replace((mp3Name.length() - 3), (mp3Name.length() - 1), "mp3"); //name.mp3

	mp3File = fopen(mp3Name.c_str(), "wb");

	int read, write;

	do
	{
		read = MyAudio.GetNextBuffer();
		if (read == 0)
		{
			write = lame_encode_flush(lame, MP3Buffer, 8192);
			printf("write: %i \n", write);
		}
		else
		{
			write = lame_encode_buffer_interleaved(lame, MyAudio.WavBuffer, read, MP3Buffer, 8192);
			printf("write: %i \n", write);
		}
		printf("read: %i \n", read);
		fwrite(MP3Buffer, write, 1, mp3File);

	} while (read != 0);

	lame_close(lame);
	fclose(mp3File);

	system("pause");
	return 0;
}