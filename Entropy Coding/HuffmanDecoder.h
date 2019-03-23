#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include"HuffmanEncoder.h"

class HuffmanDecoder : public HuffmanEncoder
{
private:
	ifstream readEncodedFile;
	string dec2binDecode(int);
public:
	void outputHMDecodedFile(string inFileName, string outFileName);
};

#endif	// HUFFMANDECODER_H