#pragma once
#include <iostream>
#include <atlstr.h>
#include <stdio.h>
using namespace std;

class WaveAudio
{
public:
	char *Name_WAV;
	short int *Buffer_WAV;

	char chunkID[4];
	unsigned long chunkSize;
	char format[4];

	char subchunk1ID[4];
	unsigned long subchunk1Size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char subchunk2ID[4];
	unsigned long subchunk2Size;

	FILE *File_WAV;

	WaveAudio();
	WaveAudio(char *fileName);
	virtual ~WaveAudio();

	int getNextBuffer();
};

