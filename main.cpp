#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    Akinator_Info *Akinator = GetAkinatorStruct(buffer);    
// DEB("A.root = %p %s\n", Akinator->AkinatorTree->root, Akinator->AkinatorTree->root->data);
// DEB("1st elem;%p %s\n", (Akinator->AkinatorTree->root)->left, (Akinator->AkinatorTree->root)->left->data);
// DEB("2nd elem;%p %s\n", (Akinator->AkinatorTree->root)->left->left, (Akinator->AkinatorTree->root)->left->left->data);
// DEB("3rd elem;%p %s\n", (Akinator->AkinatorTree->root)->left->right, (Akinator->AkinatorTree->root)->left->right->data);
// DEB("4th elem;%p %s\n", (Akinator->AkinatorTree->root)->left->left->left, (Akinator->AkinatorTree->root)->left->left->left->data);
// DEB("5th elem;%p %s\n", (Akinator->AkinatorTree->root)->left->left->right, (Akinator->AkinatorTree->root)->left->left->right->data);
// DEB("6th elem;%p %s\n", (Akinator->AkinatorTree->root)->left->right, (Akinator->AkinatorTree->root)->left->right->data);


    DEB("======\nINORDER:\n");
    InOrder(Akinator->AkinatorTree->root);
    DEB("\n==============\n");


    TreeDtor(Akinator->AkinatorTree);

    free(Akinator);
    
    free(buffer);

    return 0;
}