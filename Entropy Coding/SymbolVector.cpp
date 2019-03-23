#include"SymbolVector.h"
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
using std::noskipws;
using std::cout;
using std::endl;
using std::sort;
using std::ios;

bool compareByCountDescend(const Sym &sym_a, const Sym &sym_b)
{
	return (sym_a->count > sym_b->count);
}

bool compareByCountAscend(const Sym &sym_a, const Sym &sym_b)
{
	return (sym_a->count < sym_b->count);
}

void SymbolVector::loadRawData(string fileName)
{
	inFile.open(fileName, ios::binary);
	unsigned char temp;
	while (inFile >> noskipws >> temp) {
		rawData.push_back(temp);
	}
	inFile.close();
}

void SymbolVector::printFile()
{
	for (int i = 0; i < rawData.size(); ++i)
		cout << rawData[i];
	cout << endl;
}

void SymbolVector::findUnique()
{
	for (long i = 0; i < rawData.size(); ++i) {
		int j;
		// bool existSymbol = false;
		for (j = 0; j < symbol_in_data.size(); ++j) {
			if (symbol_in_data[j]->value == rawData[i] && !symbol_in_data[j]->isHead) {
				++symbol_in_data[j]->count;
				// existSymbol = true;
				break;
			}
		}
		if (j == symbol_in_data.size()) {
			symbol_in_data.push_back(new Symbol(rawData[i], 1, 0, false));
			// symbol_in_data[j]->value = rawData[i];
			// symbol_in_data[j]->count = 1;
		}
	}

	computeFreq();
}

void SymbolVector::listUnique()
{
	for (int i = 1; i < symbol_in_data.size(); ++i) {
		cout << symbol_in_data[i]->value << '\t'
			<< symbol_in_data[i]->count << '\t'
			<< symbol_in_data[i]->relativeFreq << endl;
	}
}

int SymbolVector::getNumUnique()
{
	return symbol_in_data.size() - 1;
}

int SymbolVector::getNumTotal()
{
	return rawData.size();
}

float SymbolVector::computeEnt()
{
	float entropy = 0;
	for (int i = 1; i < symbol_in_data.size(); ++i) {
		entropy -= symbol_in_data[i]->relativeFreq * log2(symbol_in_data[i]->relativeFreq);
	}
	return entropy;
}

void SymbolVector::sortSymbolDescend()
{
	sortedSymbolDescend.assign(symbol_in_data.begin(), symbol_in_data.end());
	sort(sortedSymbolDescend.begin() + 1, sortedSymbolDescend.end(), compareByCountDescend);
}

void SymbolVector::sortSymbolAscend()
{
	sortedSymbolAscend.assign(symbol_in_data.begin(), symbol_in_data.end());
	sort(sortedSymbolAscend.begin() + 1, sortedSymbolAscend.end(), compareByCountAscend);
}

void SymbolVector::listSortedDescend()
{
	for (int i = 1; i < sortedSymbolDescend.size(); ++i) {
		cout << sortedSymbolDescend[i]->value << '\t'
			<< sortedSymbolDescend[i]->count << '\t'
			<< sortedSymbolDescend[i]->relativeFreq << endl;
	}
}

void SymbolVector::listSortedAscend()
{
	for (int i = 1; i < sortedSymbolAscend.size(); ++i) {
		cout << sortedSymbolAscend[i]->value << '\t'
			<< sortedSymbolAscend[i]->count << '\t'
			<< sortedSymbolAscend[i]->relativeFreq << endl;
	}
}