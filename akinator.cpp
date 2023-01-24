#include "akinator.h"

Tree *FillTree(char *buffer, int *pos, Node *node)
{
    if(*pos == -1) // 
    {
        char *needed = (char *)calloc(27, sizeof(char));

        strcpy(needed, "Akinator v.42 by yasinchik");
        Tree *Akinator = CreateTree(needed);

        (*pos)++;
        FillTree(buffer, pos, (Akinator->root)->left);
        
        return Akinator;
    }
    else
    {
        //ну эта хуйня
        // не записывает нормальные вещи в правых детей, 
        //надо как-то поз блять менять или вообще все переписывать
        while(buffer[*pos] != '{' && buffer[*pos] != '}')
        {
            (*pos)++;
        }

        if(buffer[*pos] == '{')
        {
            (*pos)++;
            node = CreateNode(buffer + *pos);
            printf("node ->Data : %s\n", node->data);
        }
        else if(buffer[*pos] == '}')
        {
            (*pos)++;
            return NULL; 
        }

        FillTree(buffer, pos, node->left);
        // printf("node->left %s\n",node->left->data );
        FillTree(buffer, pos, node->right);
    
        return NULL;    
    }
}

int CountSymbols(const char *filename)
{
    struct stat buff = {};
    stat(filename, &buff);

    return buff.st_size;
}

char *ReadToBuffer(const char *filename, int size)
{    
    FILE *fp = fopen(filename, "r");

    char *buffer = (char *)calloc(size + 1, sizeof(char));

    if(buffer == NULL)
    {
        printf("buffer = NULL (READTOBUFFER)\n");
    }

    fread(buffer, sizeof(char), size, fp);
    buffer[size] = '\0';
    
    fclose(fp);

    return buffer;
}