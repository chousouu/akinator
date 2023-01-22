#include "tree.h"
#include "akinator.h"

int main()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    Akinator_Info *akinator = GetAkinatorStruct(buffer, size);

    printf("lines total = %d:\n", akinator->lines_total);
    for(int i = 0; i < akinator->lines_total; i++)
    {
        printf("%d: %s\n", i, akinator->Strings[i].text_ptr);
    }


    // printf("%s\n", NULL);

    // InOrder(akinator->root);

    // TreeDtor(akinator);

    free(akinator->Strings);
    free(akinator);
    free(buffer);
    
    return 0;
}