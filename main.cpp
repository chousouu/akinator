#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    Tree *tree = BufferParser(buffer, size);

    InOrder(tree->root);

    TreeDtor(tree);

}