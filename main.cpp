#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    Akinator_Info *Akinator = GetAkinatorStruct(buffer);    

    DEB("==============\nINORDER:\n");
    InOrder(Akinator->AkinatorTree->root);
    DEB("\n==============\n");

    GraphDump(Akinator);

    //dot graph.txt -T png -o dump.png

    TreeDtor(Akinator->AkinatorTree);

    free(Akinator);
    
    free(buffer);

    return 0;
}