#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    char needed[] = "insane linking methods";

    Tree *Akinator = CreateTree(needed);

    FillTree(buffer, -1, Akinator->root);

    // printf("%s\n", NULL);

    // InOrder(akinator->root);

    // TreeDtor(akinator);

    return 0;
}