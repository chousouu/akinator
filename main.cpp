#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    Tree *Akinator = FillTree(buffer, -1, NULL);


    printf("Ak.root = %s\n", Akinator->root->data);
    printf("Ak.root->left = %s\n", (Akinator->root)->left->data);

    InOrder(Akinator->root);

    TreeDtor(Akinator);
    
    free(buffer);

    return 0;
}