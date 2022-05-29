#ifndef _BIN_TREE_
#define _BIN_TREE_

#include <stdio.h>
#include <stdlib.h>

typedef struct BinTreeNodeType
{
	char data;
	int	key;
	int visited; //dummy data
	int height;

	struct BinTreeNodeType* pLeftChild;
	struct BinTreeNodeType* pRightChild;
	struct BinTreeNodeType* next; // for queue
	struct BinTreeNodeType* parent; // for delete node and stack
} BinTreeNode;

typedef struct BinTreeType
{
	struct BinTreeNodeType* pRootNode;
} BinTree;

BinTree* makeBinTree(BinTreeNode rootNode);
BinTreeNode* getRootNodeBT(BinTree* pBinTree);
BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element);
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element);
BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode);
BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode);
void preOrderTraversalBinTree(BinTreeNode *root);
void deleteBinTree(BinTree** pBinTree);
void deleteBinTreeNode(BinTreeNode* pNode, BinTree *root);
void  deleteAllNode(BinTreeNode *root);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif