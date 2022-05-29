#include	"bin_search_tree.h"
#include    "bintree.c"

int getBalance(BinTreeNode *n)
{
    if (n == NULL)
        return 0;
    return height(n->pLeftChild) - height(n->pRightChild);
}

BinTreeNode *rightRotate(BinTreeNode *y, BinTree *tree)
{
    BinTreeNode *x = y->pLeftChild;
    BinTreeNode *t = x->pRightChild;
    x -> pRightChild = y;
    y -> pLeftChild = t;
    y->height = height(y);
    x->height = height(x);
    if(t)
        t->parent = y;
    x->parent = y->parent;
    y->parent = x;
    if(tree->pRootNode->key == y->key)
        tree->pRootNode = x;
    return x;
}

/*
  y
 x
  t

 x
  y
 t 
*/

BinTreeNode *leftRotate(BinTreeNode *x, BinTree *tree)
{
    BinTreeNode *y = x->pRightChild;
    BinTreeNode *t = y->pLeftChild;
    y->pLeftChild = x;
    x->pRightChild = t;
    x->height = height(x);
    y->height = height(y);
    if (t)
        t->parent = x;
    y->parent = x->parent;
    x->parent = y;
    if(tree->pRootNode->key == x->key)
        tree->pRootNode = y;
    return y;
}

/*
  x
   y
  t

  y
 x
  t 
*/

BinTree* makeBinSearchTree(BinTreeNode rootNode)
{
    BinTree *newTree;

    newTree = malloc(sizeof(BinTree));
    newTree->pRootNode = calloc(1, sizeof(BinTreeNode));
    newTree->pRootNode->key = rootNode.key;
    newTree->pRootNode->data = rootNode.data;
    return(newTree);
}

BinTreeNode	*searchBinTreeNode(BinTree *tree, int key)
{
	BinTreeNode	* result = tree->pRootNode;
	while(result != NULL)
	{
		if (key == result->key)
			break;
		else if (key < result->key)
			result = result ->pLeftChild;
		else
			result = result ->pRightChild;
	}
	return result;
}
//https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
BinTreeNode *insertUtiRecurssive(BinTreeNode *root, BinTreeNode element, BinTree *tree, BinTreeNode *parent)
{
    if(!root)
    {
        BinTreeNode *tmp = calloc(1, sizeof(BinTreeNode));
        tmp->data = element.data;
        tmp->key = element.key;
        tmp->parent = parent;
        return (tmp);
    }
    if (element.key < root->key)
        root->pLeftChild = insertUtiRecurssive(root->pLeftChild, element, tree, root);
    else
        root->pRightChild = insertUtiRecurssive(root->pRightChild, element, tree, root);
    root->height = height(root);
    int balance = getBalance(root);
    // Left Left Case
    if (balance > 1 && element.key < root->pLeftChild->key)
        return rightRotate(root, tree);
    // Right Right Case
    if (balance < -1 && element.key > root->pRightChild->key)
        return leftRotate(root, tree);
    // Left Right Case
    if (balance > 1 && element.key > root->pLeftChild->key)
    {
        root->pLeftChild =  leftRotate(root->pLeftChild, tree);
        return rightRotate(root, tree);
    }
    // Right Left Case
    if (balance < -1 && element.key < root->pRightChild->key)
    {
        root->pRightChild = rightRotate(root->pRightChild, tree);
        return leftRotate(root, tree);
    }
    return root;
}

BinTreeNode *insertBinSearchTree(BinTree *tree, BinTreeNode element)
{
    if (!searchBinTreeNode(tree, element.key))
        return (insertUtiRecurssive(tree->pRootNode, element, tree, NULL));
    else
        return (NULL);
}

static BinTreeNode* find_minimum_search(BinTreeNode* pNode)
{
    while (pNode ->pLeftChild)
		pNode = pNode->pLeftChild;
    return (pNode);
}

void deleteBinSearchTreeNode(BinTreeNode* pNode, BinTree *tree)
{
    if (!pNode)
        ;
        //zero
    else if (!pNode->pLeftChild && !pNode->pRightChild)
    {
        if (pNode == tree->pRootNode)
            tree->pRootNode = NULL;
        else if (pNode->parent->pLeftChild == pNode)
            pNode->parent->pLeftChild = NULL;
        else if (pNode->parent->pRightChild == pNode)
            pNode->parent->pRightChild = NULL;
        free(pNode);
    }
        //two
    else if (pNode->pLeftChild && pNode->pRightChild)
    {
        BinTreeNode *t = find_minimum_search(pNode->pRightChild);
        pNode->key = t->key;
        if(t != pNode->pRightChild)
        {
            t->parent->pLeftChild = NULL;
            free(t);
        }
        else
        {
            free(t);
            pNode->pRightChild = NULL;
        }
    }
        //one
    else
    {
        BinTreeNode* next = pNode->pLeftChild ? pNode->pLeftChild : pNode->pRightChild;
        if (pNode->parent == NULL)
            tree->pRootNode->key = next->key;
        else
            pNode->key = next->key;
        pNode->pLeftChild = NULL;
        pNode->pRightChild = NULL;
        free(next);
    }
}

//stack
void preOrder2B(BinTreeNode *root)
{
    BinTreeNode *s = NULL;
    int         done = 1;
      while(done)
      {
          if(root)
          {
            printf("%d ",root->key);
            root->parent = s;
            s = root; // push
            root = root->pLeftChild;
          }
          else
          {
              if(s)
              {
                root = s;
                s = s->parent; // pop
                root = root->pRightChild;
              }
              else
                done = 0;
          }
      }
      printf("\n");
}

//iterator
void inOrderB(BinTreeNode* root)
{
    if (!root)
        return;
    int i = 0;
    while (root)
    {
        if (root->pLeftChild == NULL)
        {
            printf("%d ", root->key);
            root = root->pRightChild;
        }
        else
        {
            BinTreeNode *pre = root->pLeftChild;
            while (pre->pRightChild && pre->pRightChild != root)
                pre = pre->pRightChild;
            if (!pre->pRightChild)
            {
                pre->pRightChild = root;
                root = root->pLeftChild;
            }
            else
            {
                pre->pRightChild = NULL;
                printf("%d ", root->key);
                root = root->pRightChild;
            }
        }
        if ((i++ + 31) % 32 == 0)
            printf("\n");
    }
    printf("\n");
}

//stack
void postOrder2B(BinTreeNode *root)
{
      BinTreeNode *s = NULL;
      do
      {
          while(root) // go to left
          {
            if(root->pRightChild)
            {
                root->pRightChild->parent = s;
                s = root->pRightChild;
            } // set as root->pRightChild as parent of root
            root->parent = s; 
            s = root; // push
            root = root->pLeftChild;
          }
          root = s;
          s = s->parent; // pop
          if (root->pRightChild && s == root->pRightChild) // if (root has right child)
          {
              root->parent = s->parent;
              s = root; // push
              root = root->pRightChild;
          }
          else
          {
              printf("%d ", root->key);
              root = NULL;
          }
      }while(s);
      printf("\n");
}

/*
int main()
{
    BinTreeNode root;
    root.data = 0;
    root.next = NULL;
    root.parent = NULL;
    root.visited = 0;
    root.pRightChild = NULL;
    root.pLeftChild = NULL;
    BinTree *tree;
    root.key = 1;
    tree = makeBinSearchTree(root);
    root.key = 2;
    insertBinSearchTree(tree, root);
    root.key = 3;
    insertBinSearchTree(tree, root);
    root.key = 4;
    insertBinSearchTree(tree, root);
    root.key = 5;
    insertBinSearchTree(tree, root);
    root.key = 6;
    insertBinSearchTree(tree, root);
    root.key = 7;
    insertBinSearchTree(tree, root);
    root.key = 8;
    insertBinSearchTree(tree, root);
    root.key = 9;
    insertBinSearchTree(tree, root);
    root.key = 10;
    insertBinSearchTree(tree, root);
    root.key = 11;
    insertBinSearchTree(tree, root);
    root.key = 12;
    insertBinSearchTree(tree, root);
    deleteBinSearchTreeNode(tree->pRootNode->pLeftChild, tree);
    deleteBinSearchTreeNode(tree->pRootNode, tree);
    deleteBinSearchTreeNode(searchBinTreeNode(tree, 12), tree);
    deleteBinSearchTreeNode(searchBinTreeNode(tree, 6), tree);
    deleteBinSearchTreeNode(searchBinTreeNode(tree, 11), tree);
    levelorder(tree->pRootNode);
    preOrder2B(tree->pRootNode);
    inOrderB(tree->pRootNode);
    postOrder2B(tree->pRootNode);
    deleteBinTree2(&tree);
    root.key = 50;
    tree = makeBinSearchTree(root);
    root.key = 30;
    insertBinSearchTree(tree, root);
    root.key = 20;
    insertBinSearchTree(tree, root);
    root.key = 40;
    insertBinSearchTree(tree, root);
    root.key = 70;
    insertBinSearchTree(tree, root);
    root.key = 60;
    insertBinSearchTree(tree, root);
    root.key = 80;
    insertBinSearchTree(tree, root);
    printf("levelorder : ");levelorder(tree->pRootNode);
    printf("preorder : ");preOrder2B(tree->pRootNode);
    printf("inorder : ");inOrderB(tree->pRootNode);
    printf("postorder : ");postOrder2B(tree->pRootNode);
    deleteBinTree2(&tree);
    printf("=======================\n");
    system("leaks a.out");
    return (0);
}
*/