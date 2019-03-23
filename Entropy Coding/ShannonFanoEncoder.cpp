#include"ShannonFanoEncoder.h"
#include"BinaryTree.h"
#include"SymbolVector.h"
#include<iostream>
#include<fstream>
#include<bitset>
#include<cmath>
#include<list>
using std::list;
using std::pow;
using std::cout;
using std::cerr;
using std::endl;
using std::bitset;
using std::ios;

string ShannonFanoEncoder::dec2binEncode(int n)
{
	vector<bool> binNum;
	while (n / 2 != 0) {
		binNum.push_back(n % 2);
		n /= 2;
	}
	binNum.push_back(n % 2);

	string bitString;
	for (int i = binNum.size(); i > 0; --i) {
		if (binNum[i - 1])
			bitString.push_back('1');
		else
			bitString.push_back('0');
	}

	return bitString;
}

int ShannonFanoEncoder::bin2dec(list<unsigned char> buffer)
{
	int symbolDec = 0, countDigit = buffer.size() - 1;
	for (list<unsigned char>::iterator i = buffer.begin(); i != buffer.end(); ++i) {
		symbolDec += int((*i) == '1') * pow(2, countDigit--);
	}

	return symbolDec;
}

void ShannonFanoEncoder::buildSFTree(int start, int end, float maxFreq, int currentNode)
{
	if (start >= end)
		cerr << "Error! No symbol input." << endl;
	else if (start == end - 1) {
		assignValue(currentNode, sortedSymbolDescend[end]->value, sortedSymbolDescend[end]->relativeFreq);
	}
	else {
		splitNode(currentNode);

		float sumFreq = 0;
		int i = start, separateIdx;
		while (sumFreq < maxFreq / 2 && i < end - 1) {
			sumFreq += sortedSymbolDescend[i + 1]->relativeFreq;
			++i;
		}

		if ((sumFreq < maxFreq / 2) ||
			((sumFreq - maxFreq / 2) < (maxFreq / 2 - sumFreq + sortedSymbolDescend[i]->relativeFreq))) {
			separateIdx = i;
		}
		else {
			separateIdx = i - 1;
			sumFreq -= sortedSymbolDescend[i]->relativeFreq;
		}

		buildSFTree(start, separateIdx, sumFreq, 2 * currentNode);
		buildSFTree(separateIdx, end, maxFreq - sumFreq, 2 * currentNode + 1);
	}
}

void ShannonFanoEncoder::encodeSF()
{
	for (int i = 1; i < nodeVector.size(); ++i) {
		if (nodeVector[i]->relativeFreq > 0 && nodeVector[i]->relativeFreq < 1) {
			SFCodeTable.push_back(new SFCodeWord);
			SFCodeTable.back()->symbol = nodeVector[i]->attribute;
			SFCodeTable.back()->relativeFreq = nodeVector[i]->relativeFreq;
			SFCodeTable.back()->decIndex = nodeVector[i]->index;
			SFCodeTable.back()->binCode = dec2binEncode(nodeVector[i]->index).erase(0, 1);
		}
	}
}

void ShannonFanoEncoder::printSFCode()
{
	for (int i = 1; i < SFCodeTable.size(); ++i) {
		cout << i << '\t' << SFCodeTable[i]->symbol <<
			'\t' << SFCodeTable[i]->binCode << endl;
	}
}

float ShannonFanoEncoder::computeAvgLength()
{
	float Bavg = 0;
	for (int i = 1; i < SFCodeTable.size(); ++i) {
		Bavg += SFCodeTable[i]->binCode.size() * SFCodeTable[i]->relativeFreq;
	}
	return Bavg;
}

void ShannonFanoEncoder::outputSFEncodedFile(string fileName)
{
	outFile.open(fileName, ios::binary);
	string tempEncodedString;
	list<unsigned char> outputBuffer;
	for (long i = 0; i < rawData.size(); ++i) {
		for (int j = 0; j < SFCodeTable.size(); ++j) {
			if (rawData[i] == SFCodeTable[j]->symbol) {
				tempEncodedString.append(SFCodeTable[j]->binCode);
				// cout << SFCodeTable[j]->binCode;
			}
		}
	}
	// cout << endl;
	
	for (long i = 0; i < tempEncodedString.size(); ++i) {
		if (i == 0) {
			outputBuffer.push_back(tempEncodedString[i]);
		}
		else if (i == tempEncodedString.size() - 1 && i % 8 != 0) {
			outputBuffer.push_back(tempEncodedString[i]);
			outFile << unsigned char(bin2dec(outputBuffer));
		}
		else if (i % 8 == 0 && i != 0) {
			outFile << unsigned char(bin2dec(outputBuffer));
			outputBuffer.clear();
			outputBuffer.push_back(tempEncodedString[i]);
		}
		else {
			outputBuffer.push_back(tempEncodedString[i]);
		}
	}

	outFile.close();
}

void ShannonFanoEncoder::outputSFCodeTable(string fileName)
{
	outFile.open(fileName, ios::binary);
	for (int i = 0; i < SFCodeTable.size(); ++i) {
		outFile << SFCodeTable[i]->symbol << '\t'
			<< SFCodeTable[i]->binCode << '\n';
	}
	outFile.close();
}