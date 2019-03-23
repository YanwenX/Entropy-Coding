#ifndef SHANNONFANOENCODER_H
#define SHANNONFANOENCODER_H

#include"SymbolVector.h"
#include"BinaryTree.h"
#include<vector>
#include<string>
#include<fstream>
#include<list>
#include<bitset>
using std::list;
using std::string;
using std::vector;
using std::ofstream;
using std::bitset;

typedef struct SFCodeWord{
	unsigned char symbol;
	int decIndex;			// code word index in decimal
	string binCode;			// a string representation of code word
	float relativeFreq;
	SFCodeWord() : symbol('\0'), binCode("0"), relativeFreq(0) {}
}*SFCW;

class ShannonFanoEncoder : public SymbolVector, public BinaryTree
{
protected:
	string dec2binEncode(int);
	int bin2dec(list<unsigned char>);
	ofstream outFile;
public:
	vector<SFCW> SFCodeTable;	// the table storing the symbol - code pairs
	ShannonFanoEncoder() {
		SFCodeTable.push_back(new SFCodeWord);
		nodeVector.push_back(new treeNode(1, '\0', 1, 0, 0, 0));
	}
	void buildSFTree(int, int, float, int);
	void encodeSF();
	void printSFCode();
	float computeAvgLength();
	void outputSFEncodedFile(string fileName);
	void outputSFCodeTable(string);
};



#endif	// SHANNONFANOENCODER_H
