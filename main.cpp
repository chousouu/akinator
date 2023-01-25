#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    int pos = -1;

    Tree *Akinator = FillTree(buffer, &pos, NULL);

    printf("Ak.root = %s\n", Akinator->root->data);
    printf("Ak.root->left = %p\n", (Akinator->root)->left);

    InOrder(Akinator->root);

    TreeDtor(Akinator);
    
    free(buffer);

    return 0;
}