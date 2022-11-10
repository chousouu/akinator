#include "tree.h"
#include "akinator.h"

int main()
{

Tree *tree = CreateTree(5);

AddNode(tree->root, 4, LEFT_NODE);
AddNode(tree->root, 6, RIGHT_NODE);

AddNode(tree->root->left, 2, LEFT_NODE);
AddNode(tree->root->left, 3, LEFT_NODE);

InOrder(tree->root);

TreeDtor(tree);

}