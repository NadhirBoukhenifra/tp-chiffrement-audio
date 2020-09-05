#pragma once
#include <iostream>
#include <atlstr.h>
#include <fstream>

using namespace std;
class WaveAudio
{
public:
	FILE *WavFile;
	const char *WavName;
	short int *WavBuffer;
	int NumChannels;
	int SampleRate;
	int BitsPerSample;
	int WaveAudio;


	WaveAudio();
	WaveAudio(const char *FileName);
	int GetNextBuffer();
	virtual ~WaveAudio();


};

WaveAudio::NumChannels

