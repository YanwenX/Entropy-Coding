#include"ShannonFanoEncoder.h"
#include"ShannonFanoDecoder.h"
#include"BinaryTree.h"
#include"SymbolVector.h"
using std::noskipws;
using std::ios;

string ShannonFanoDecoder::dec2binDecode(int n)
{
	vector<bool> binNum;
	while (n / 2 != 0) {
		binNum.push_back(n % 2);
		n /= 2;
	}
	binNum.push_back(n % 2);
	
	if (binNum.size() < 8) {
	for (int i = binNum.size(); i < 8; ++i)
	binNum.push_back(0);
	}

	string bitString;
	for (int i = binNum.size(); i > 0; --i) {
		if (binNum[i - 1])
			bitString.push_back('1');
		else
			bitString.push_back('0');
	}

	return bitString;
}

void ShannonFanoDecoder::outputSFDecodedFile(string inFileName, string outFileName)
{
	// bug for decoding last character
	readEncodedFile.open(inFileName, ios::binary);
	string tempDecodedString, decodeBuffer;
	vector<unsigned char> tempCharVector;
	unsigned char readNext;
	while (readEncodedFile >> noskipws >> readNext) {
		tempCharVector.push_back(readNext);
	}
	readEncodedFile.close();

	for (int i = 0; i < tempCharVector.size(); ++i) {
		if (i != tempCharVector.size() - 1) {
			tempDecodedString.append(dec2binDecode(int(tempCharVector[i])));
		}
		else
			tempDecodedString.append(dec2binEncode(int(tempCharVector[i])));
	}

	outFile.open(outFileName, ios::binary);
	for (int i = 0; i < tempDecodedString.size(); ++i) {
		decodeBuffer.push_back(tempDecodedString[i]);
		for (int j = 1; j < SFCodeTable.size(); ++j) {
			if (SFCodeTable[j]->binCode == decodeBuffer) {
				outFile << SFCodeTable[j]->symbol;
				decodeBuffer.clear();
				break;
			}
		}
	}
	outFile.close();
}
