#ifndef SHANNONFANODECODER_H
#define SHANNONFANODECODER_H

#include"ShannonFanoEncoder.h"

class ShannonFanoDecoder : public ShannonFanoEncoder
{
private:
	ifstream readEncodedFile;
	string dec2binDecode(int n);
public:
	void outputSFDecodedFile(string inFileName, string outFileName);
};


#endif	// SHANNONFANODECODER
