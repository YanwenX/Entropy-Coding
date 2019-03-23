#ifndef BINARYTREE_H
#define BINARYTREE_H

// #include"SymbolVector.h"
#include<vector>
#include<bitset>
using std::vector;
using std::bitset;

typedef struct treeNode {
	int index;				// the index of the node in the tree
	unsigned char attribute;// the attribute (symbol) of the node
	float relativeFreq;
	bool isLeaf;			// whether the node is a leaf node
	treeNode* left_child;
	treeNode* right_child;
	treeNode* parent;
	treeNode(int idx, unsigned char att, float freq, treeNode* left, treeNode* right, treeNode* prt, bool l) :
		index(idx), attribute(att), relativeFreq(freq),
		left_child(left), right_child(right), parent(prt), isLeaf(l) {}
	treeNode(int idx, unsigned char att, float freq, treeNode* left, treeNode* right, treeNode* prt) :
		index(idx), attribute(att), relativeFreq(freq),
		left_child(left), right_child(right), parent(prt) {}
	treeNode(int idx, unsigned char att, treeNode* left, treeNode* right, treeNode* prt) :
		index(idx), attribute(att), left_child(left), right_child(right), parent(prt) {}
	treeNode(unsigned char att, float freq, treeNode* left, treeNode* right, treeNode* prt) :
		attribute(att), relativeFreq(freq), left_child(left), right_child(right), parent(prt) {}
	treeNode(unsigned char att, float freq, bool l) : attribute(att), relativeFreq(freq), isLeaf(l) {}
}*Node;

class BinaryTree
{
protected:
	vector<Node> nodeVector;	// binary tree stored in vector
	Node nodeList;				// binary tree stored in list
public:
	BinaryTree() { 
		// nodeVector.push_back(new treeNode(1, '\0', 1, 0, 0, 0));
		// nodeList = new treeNode(0, '\0', 1, 0, 0, 0);
	}
	void splitNode(int);
	void assignValue(int, unsigned char, float);
	int getLength();
	void getNode(int);
	void printTree();
	Node mergeNode(Node&, Node&);
};


#endif	// BINARYTREE_H