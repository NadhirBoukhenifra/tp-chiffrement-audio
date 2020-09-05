#include "Compressmp3.h"
Compressmp3::Compressmp3()
{
}

Compressmp3::~Compressmp3()
{
}

int main(void)
{
		
		FILE *File_MP3;
		string Name_MP3 = (string)myAudio.Name_WAV;

		Name_MP3.replace((Name_MP3.length()-3), (Name_MP3.length()-1), "mp3");
		const char *C_String = Name_MP3.c_str();
		File_MP3 = fopen(C_String, "wb");
		unsigned char Buffer_MP3[8192];
		lame_t lame = lame_init();
		lame_set_in_samplerate(lame, myAudio.sampleRate);
		lame_set_VBR(lame, vbr_default);
		if (myAudio.numChannels == 1)
		{
			lame_set_num_channels(lame, 1);
			lame_set_mode(lame, MONO);
		}
		else if (myAudio.numChannels == 2) {
			lame_set_num_channels(lame, 2);
			lame_set_mode(lame, STEREO);
		}
		lame_set_brate(lame, myAudio.byteRate / 1000); //kb/s
		lame_init_params(lame);

		int read, write;
		do
		{
			read = myAudio.getNextBuffer();
			if (read == 0)
			{
				write = lame_encode_flush(lame, mp3Buffer, 8192);
			}
			else
			{
				write = lame_encode_buffer_interleaved(lame, myAudio.Buffer_WAV, read, Buffer_MP3, 8192);
			}
			fwrite(Buffer_MP3, write, 1,File_MP3);
		} while (read != 0);
		lame_close(lame);
		fclose(File_MP3);
}
