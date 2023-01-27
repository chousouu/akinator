#include "akinator.h"

static Tree *FillTree(const char *buffer, int *pos, Node *node, int *tree_size)
{
    if(*pos == -1)
    {
        char *needed = (char *)calloc(27, sizeof(char));

        strcpy(needed, "Akinator v.44 by yasinchik");
        
        Tree *ATree = CreateTree(needed);

        (*pos)++;
        (*tree_size)++;
        (ATree->root)->left = CreateNode(NULL);

        FillTree(buffer, pos, (ATree->root)->left, tree_size);
        
        Node *temp_root = ATree->root;
        ATree->root = (ATree->root)->left;
        
        free(needed);
        free(temp_root);

        return ATree;
    }
    else
    {
        if(buffer[*pos] == '\0')
        {
            return NULL;
        }

        if(buffer[*pos] == '{')
        {
            (*tree_size)++;
            (*pos)++;
            node->data = GetString(buffer + *pos);

//TODO: can be optimized by changing *pos in GetString()           
            while(buffer[*pos] != '{' && buffer[*pos] != '}')
            {
                (*pos)++;
            }
           
            if(buffer[*pos] == '}') 
            {
                (*pos)++;
                return NULL;   
            }
        }
        else if(buffer[*pos] == '}')
        {
            (*pos)++;
            return NULL; 
        }

        node->left  = CreateNode(NULL);
        node->right = CreateNode(NULL);

        FillTree(buffer, pos, node->left, tree_size);
        FillTree(buffer, pos, node->right, tree_size);

        (*pos)++;             

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

char *GetString(const char *buffer)
{
    int buffer_walker = 0;
    while(buffer[buffer_walker] != '{' && buffer[buffer_walker] != '}')
    {
        buffer_walker++;
    } 
    if(buffer_walker == 0) 
    {
        return NULL;
    }

    char *new_string = (char *)calloc(buffer_walker + 1, sizeof(char));
    strncpy(new_string, buffer, buffer_walker);

    return new_string;
}

void GraphDump(Akinator_Info *Akinator)
{
    FILE *graph = fopen("graph.txt", "a");

    if(graph == NULL)
    {
        printf("cannot open graph\n");
        return;
    }
    fprintf(graph, "digraph g {\n");

    fprintf(graph, 
                "fontname= \"Helvetica,Arial,sans-serif\"\n"
                "node [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                "edge [fontname=\"Helvetica,Arial,sans-serif\"]\n"
                "graph [rankdir = \"TB\"];\n"
                "node [fontsize = \"16\" shape = \"ellipse\"];\n"
                "edge [];\n"
            );

    DumpNodes(graph, Akinator->AkinatorTree->root, CREATE_NODE);
    DumpNodes(graph, Akinator->AkinatorTree->root, LINK_NODE);

    fprintf(graph, "}");

   fclose(graph);
}

void DumpNodes(FILE *graph, Node *node, int mode)
{
    if(mode == CREATE_NODE)
    {
        if(node == NULL || node->data == NULL)
        {
            return;
        }

        fprintf(graph, 
                    " \"node%s\" [\n"
                    "label = \"%s\" \n"
                    "shape = \"record\"\n"
                    "];\n",
                    node->data, node->data);

        DumpNodes(graph, node->left, mode);
        DumpNodes(graph, node->right, mode);
    }
    else 
    {
        if(node == NULL)
        {
            return;
        }
        if(node->left != NULL && node->left->data != NULL)
        {
            fprintf(graph, " \"node%s\" -> \"node%s\" [color = \"green\"]\n", node->data, node->left->data);
        }
        if(node->right != NULL && node->right->data != NULL)
        {
            fprintf(graph, " \"node%s\" -> \"node%s\"[color = \"red\"]\n", node->data, node->right->data);
        }
        DumpNodes(graph, node->left, mode);
        DumpNodes(graph, node->right, mode);
    }
}

Akinator_Info *GetAkinatorStruct(char *buffer)
{
    Akinator_Info *Akinator = (Akinator_Info *)calloc(1, sizeof(Akinator_Info));

    int pos = -1;
    int tree_size = 0;

    *Akinator = 
    {
        .buffer = buffer,
        .AkinatorTree = FillTree(buffer, &pos, NULL, &tree_size),
        .lines_total = tree_size,
    };

    DEB("Tree = %p\n buffer = %p\n lines = %d\n", 
    Akinator->AkinatorTree, Akinator->buffer, Akinator->lines_total);
    
    return Akinator;
}
