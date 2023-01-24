#include "akinator.h"
/*
 Akinator_Info *GetAkinatorStruct(char *buffer, int buffer_size)
// {
//     int total_lines = 0;
//     int word_len = 0; 

//     for(int i = 0; i < buffer_size; i++)
//     {
//         if(buffer[i] == '{')
//         {
//             total_lines++;
//         }
//     }


//     // get total_lines, ptr of words,
//     Option_info *text_info = (Option_info *)calloc(total_lines, sizeof(Option_info));

//     Akinator_Info *Akinator = (Akinator_Info *)calloc(1, sizeof(Akinator_Info));

//     Akinator->buffer = buffer;
//     Akinator->Strings = text_info;
//     Akinator->lines_total = total_lines;

//     return Akinator;
// }
*/
Tree *FillTree(char *buffer, int pos, Node *node)
{
    if(pos == -1) //call func with -1 in main 
    {
        char *needed = (char *)calloc(4, sizeof(char));
        strcpy(needed, "pls");

        Tree *Akinator = CreateTree(needed);

        FillTree(buffer, 0, (Akinator->root)->left);
        
        return Akinator;
    }
    else
    {
        while(buffer[pos] != '{' && buffer[pos] != '}')
        {
            pos++;
        }

        if(buffer[pos] == '{')
        {
            pos++;
            node = CreateNode(buffer + pos);
        }
        else if(buffer[pos] == '}')
        {
            pos++;
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