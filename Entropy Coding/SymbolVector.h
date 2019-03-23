#ifndef SYMBOLVECTOR_H
#define SYMBOLVECTOR_H

#include<vector>
#include<fstream>
#include<string>
using std::vector;
using std::ifstream;
using std::string;

typedef struct Symbol {
	Symbol() : value('\0'), count(0), relativeFreq(0) {}
	Symbol(unsigned char v, int c, float f, bool h) :
		value(v), count(c), relativeFreq(f), isHead(h) {}
	unsigned char value;	// what the symbol is
	int count;				// the number of occurrence in the file
	float relativeFreq;		// the global relative frequency
	bool isHead;			// whether it is a "head" Symbol in the symbol vector
}*Sym;

class SymbolVector
{
protected:
	ifstream inFile;				// read data file
	vector<Sym> symbol_in_data;		// store unique symbols in the file
	vector<Sym> sortedSymbolDescend;// store the sorted symbols (in freq. descending order)
	vector<Sym> sortedSymbolAscend;	// store the sorted symbols (in freq. ascending order)
	vector<unsigned char> rawData;	// store the raw data
	void computeFreq() {
		for (int i = 1; i < symbol_in_data.size(); ++i)
			symbol_in_data[i]->relativeFreq = symbol_in_data[i]->count / float(this->getNumTotal());
	}
public:
	SymbolVector() { symbol_in_data.push_back(new Symbol('\0', 0, 0, true)); }
	int getNumUnique();
	int getNumTotal();
	void loadRawData(string fileName);
	void printFile();
	void findUnique();
	void listUnique();
	float computeEnt();
	void sortSymbolDescend();
	void sortSymbolAscend();
	void listSortedDescend();
	void listSortedAscend();
};



#endif	// SYMBOLVECTOR_H
