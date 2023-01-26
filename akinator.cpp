#include "akinator.h"

Tree *FillTree(char *buffer, int *pos, Node *node)
{
    if(*pos == -1)
    {
        char *needed = (char *)calloc(27, sizeof(char));

        strcpy(needed, "Akinator v.42 by yasinchik");
        Tree *Akinator = CreateTree(needed);
        DEB("root = %p\n", Akinator->root);
        (*pos)++;
        (Akinator->root)->left = CreateNode(NULL);
        FillTree(buffer, pos, (Akinator->root)->left);
        
        return Akinator;
    }
    else
    {
        if(buffer[*pos] == '\0')
        {
            return NULL;
        }

        while(buffer[*pos] != '{' && buffer[*pos] != '}')
        {
            (*pos)++;
        }

        if(buffer[*pos] == '{')
        {
            (*pos)++;
            DEB("node = %p\n", node);
            node->data = (buffer + *pos);
            DEB("created node = %p\n", node);
            // node = CreateNode(strtok(buffer + *pos, "{}"));
            printf("node ->Data : %s\n", node->data);
        }
        else if(buffer[*pos] == '}')
        {
            // DEB("pos %d (\"%c\")\n", *pos, buffer[*pos]);
            return NULL; 
        }
        node->left = CreateNode(NULL);
        FillTree(buffer, pos, node->left);
        node->right = CreateNode(NULL);
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