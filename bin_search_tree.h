#ifndef _BIN_SEARCH_TREE_
#define _BIN_SEARCH_TREE_

#include "bintree.h"

BinTreeNode	*searchBinTreeNode(BinTree *tree, int key);
BinTreeNode *insertBinSearchTree(BinTree *tree, BinTreeNode element);
void        deleteBinSearchTreeNode(BinTreeNode* pNode, BinTree *tree);

#endif





