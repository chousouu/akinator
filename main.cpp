#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");


    
    
    printf("size = %d\n", size);




    char *buffer = ReadToBuffer("sheesh.txt", size);
    
    int pos = -1;

    Tree *Akinator = FillTree(buffer, &pos, NULL);

    printf("Ak.root = %s\n", Akinator->root->data);
    printf("Ak.root->left = %p\n", (Akinator->root)->left);

    printf("======\nINORDER:\n");
    InOrder(Akinator->root);
    printf("\n==============\n");


    free(Akinator->root->data);
    TreeDtor(Akinator);

    
    free(buffer);

    return 0;
}