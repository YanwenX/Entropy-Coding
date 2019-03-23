#include"BinaryTree.h"
#include<iostream>
using std::cout;
using std::endl;

void BinaryTree::splitNode(int n)
{
	for (int i = nodeVector.size() + 1; i <= 2 * n + 1; ++i) {
		nodeVector.push_back(new treeNode(i, '\0', 0, 0, 0));
	}
	for (int i = 0; i <= n - 1; ++i) {
		nodeVector[i]->left_child = nodeVector[2 * i + 1];
		nodeVector[i]->right_child = nodeVector[2 * i + 2];
	}
}

void BinaryTree::assignValue(int n, unsigned char att, float freq)
{
	nodeVector[n - 1]->attribute = att;
	nodeVector[n - 1]->relativeFreq = freq;
}

int BinaryTree::getLength()
{
	return nodeVector.size();
}

void BinaryTree::getNode(int n)
{
	cout << nodeVector[n - 1]->index << '\t' << nodeVector[n - 1]->attribute <<
		'\t' << nodeVector[n - 1]->relativeFreq << endl;
}

void BinaryTree::printTree()
{
	for (int i = 0; i < nodeVector.size(); ++i) {
		if (nodeVector[i]->attribute != '\0') {
			cout << nodeVector[i]->index << '\t' << nodeVector[i]->attribute
				<< '\t' << nodeVector[i]->relativeFreq << endl;
		}
	}
}

Node BinaryTree::mergeNode(Node& node_a, Node& node_b)
{
	Node newParent = new treeNode(0, '\0', node_a->relativeFreq + node_b->relativeFreq,
		node_a, node_b, 0, false);
	node_a->parent = newParent;
	node_b->parent = newParent;
	return newParent;
}