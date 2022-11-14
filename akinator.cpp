#include "akinator.h"
// xz kak nazvat, no ne parser 
Tree* BufferParser(char *buffer, int buffer_size)
{
    char arg[30] = "";
    int arg_length = 0;
    int i = 0;
    // for(int z = 0; z < buffer_size; z++)
    // {
    //     printf("%d '%c' ", z, buffer[z]);
    // }

    printf("==================\n");

    int counter = 0;

    for(; i < buffer_size; i++)
    {    
        if(buffer[i] == '{') 
        {
            i++;
            while(buffer[i] != '}' && buffer[i] != '{')
            {
                if(!(buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t'))
                {
                    arg[counter++] = buffer[i];
                }
                i++;
            }
            DEB("arg root = %s\n", arg);
            break;
        }
    }

    Tree *tree = CreateTree(arg);

    CreateQuestion(tree->root, buffer, i, buffer_size);

    return tree;
}

void CreateQuestion(Node *destination, char *buffer, int index, int buffer_size)
{
    destination->left  = CreateNode (NULL);
    destination->right = CreateNode (NULL);

    char arg[50] = "";
    int arg_length = 0;

    int counter = 0;

    for(; index < buffer_size; index++)
    {    
        if(buffer[index] == '{') 
        {
            index++;
            
            if(buffer[index] == '}') return;

            while(buffer[index] != '}' && buffer[index] != '{')
            {
                if(!(buffer[index] == ' ' || buffer[index] == '\n' || buffer[index] == '\t'))
                {
                    arg[counter++] = buffer[index];
                }
                index++;
            }
            DEB("arg root = %s\n", arg);
            break;
        }
    }
    DEB("dest->data = %s\n", arg);
    
    destination->data = arg;
    
    CreateQuestion(destination->left, buffer, index, buffer_size);
    CreateQuestion(destination->right, buffer, index, buffer_size);

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