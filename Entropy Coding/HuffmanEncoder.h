#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include"SymbolVector.h"
#include"BinaryTree.h"
#include<string>
#include<vector>
#include<list>
#include<fstream>
using std::ofstream;
using std::string;
using std::vector;
using std::list;

typedef struct HMCodeWord {
	unsigned char symbol;
	string binCode;
	float relativeFreq;
	HMCodeWord() : symbol('\0'), binCode("0"), relativeFreq(0) {}
	HMCodeWord(unsigned char s, float f) : symbol(s), relativeFreq(f) {}
}*HMCW;

class HuffmanEncoder : public SymbolVector, public BinaryTree
{
protected:
	list<Node> activeNodeList;
	ofstream outFile;
	int bin2dec(list<unsigned char>);
public:
	vector<HMCW> HMCodeTable;
	HuffmanEncoder() {
		HMCodeTable.push_back(new HMCodeWord);
		nodeList = new treeNode(0, '\0', 0, 0, 0, 0);
		nodeVector.push_back(new treeNode(0, '\0', 0, 0, 0, 0));
	}
	void initialActiveList();
	bool isEmpty();
	void printActiveList();
	void buildHMTree();
	void encodeHM();
	void printHMCode();
	float computeAvgLength();
	void outputHMEncodedFile(string fileName);
};


#endif	// HUFFMANENCODER_H