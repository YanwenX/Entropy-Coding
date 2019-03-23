#include"HuffmanEncoder.h"
#include"SymbolVector.h"
#include"BinaryTree.h"
#include<algorithm>
#include<list>
#include<iostream>
using std::list;
using std::iterator;
using std::cout;
using std::endl;
using std::sort;
using std::ios;

int HuffmanEncoder::bin2dec(list<unsigned char> buffer)
{
	int symbolDec = 0, countDigit = buffer.size() - 1;
	for (list<unsigned char>::iterator i = buffer.begin(); i != buffer.end(); ++i) {
		symbolDec += int((*i) == '1') * pow(2, countDigit--);
	}

	return symbolDec;
}


bool compareByFreqAscend(const Node& node_a, const Node& node_b)
{
	return (node_a->relativeFreq < node_b->relativeFreq);
}

bool compareByCodeLength(const HMCW& codeword_a, const HMCW& codeword_b)
{
	return (codeword_a->binCode.size() < codeword_b->binCode.size());
}

void HuffmanEncoder::initialActiveList()
{
	for (int i = 1; i < sortedSymbolAscend.size(); ++i) {
		activeNodeList.push_back(new treeNode(
			sortedSymbolAscend[i]->value, sortedSymbolAscend[i]->relativeFreq, true));
	}
}

bool HuffmanEncoder::isEmpty()
{
	return activeNodeList.empty();
}

void HuffmanEncoder::printActiveList()
{
	list<Node>::iterator i;
	for (i = activeNodeList.begin(); i != activeNodeList.end(); ++i) {
		if ((*i)->attribute != '\0')
			cout << (*i)->attribute << '\t' << (*i)->relativeFreq << endl;
	}
}

void HuffmanEncoder::buildHMTree()
{
	Node tempNode1, tempNode2;
	while (nodeList->relativeFreq < 1) {
		tempNode1 = activeNodeList.front();
		activeNodeList.pop_front();
		tempNode2 = activeNodeList.front();
		activeNodeList.pop_front();

		nodeList = mergeNode(tempNode1, tempNode2);
		nodeList->left_child->index = 0;
		nodeList->right_child->index = 1;
		nodeVector.push_back(tempNode1);
		nodeVector.push_back(tempNode2);

		activeNodeList.push_front(nodeList);
		activeNodeList.sort(compareByFreqAscend);
	}
}

void HuffmanEncoder::encodeHM()
{
	Node tempNode;
	list<int> tempCode;
	int countSymbol = 0;
	for (int i = 1; i < nodeVector.size(); ++i) {
		if (nodeVector[i]->isLeaf) {
			++countSymbol;		
			tempCode.clear();
			HMCodeTable.push_back(new HMCodeWord(nodeVector[i]->attribute, nodeVector[i]->relativeFreq));
			tempNode = nodeVector[i];
			while (tempNode->parent != 0) {
				tempCode.push_front(tempNode->index);
				tempNode = tempNode->parent;
			}
			for (list<int>::iterator j = tempCode.begin(); j != tempCode.end(); ++j) {
				if ((*j) == 1)
					HMCodeTable[countSymbol]->binCode.push_back('1');
				else HMCodeTable[countSymbol]->binCode.push_back('0');
			}
		}
	}
	sort(HMCodeTable.begin() + 1, HMCodeTable.end(), compareByCodeLength);
}

void HuffmanEncoder::printHMCode()
{
	for (int i = 1; i < HMCodeTable.size(); ++i) {
		cout << i << '\t' << HMCodeTable[i]->symbol <<
			'\t' << HMCodeTable[i]->binCode << endl;
	}
}

float HuffmanEncoder::computeAvgLength()
{
	float Bavg = 0;
	for (int i = 1; i < HMCodeTable.size(); ++i) {
		Bavg += HMCodeTable[i]->binCode.size() * HMCodeTable[i]->relativeFreq;
	}
	return Bavg;
}

void HuffmanEncoder::outputHMEncodedFile(string fileName)
{
	outFile.open(fileName, ios::binary);
	string tempEncodedString;
	list<unsigned char> outputBuffer;
	for (int i = 0; i < rawData.size(); ++i) {
		for (int j = 0; j < HMCodeTable.size(); ++j) {
			if (rawData[i] == HMCodeTable[j]->symbol) {
				tempEncodedString.append(HMCodeTable[j]->binCode);
				// cout << HMCodeTable[j]->binCode;
			}
		}
	}
	// cout << endl;

	for (int i = 0; i < tempEncodedString.size(); ++i) {
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