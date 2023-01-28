#include "akinator.h"
#include "stack.h"

static Tree *FillTree(const char *buffer, int *pos, Node *node, int *tree_size)
{
    if(*pos == -1)
    {
        char *needed = (char *)calloc(27, sizeof(char));

        strcpy(needed, "Akinator v.44 by yasinchik");
        
        Tree *ATree = CreateTree(needed);

        (*pos)++;
        (ATree->root)->left = CreateNode(NULL);

        FillTree(buffer, pos, (ATree->root)->left, tree_size);
        
        Node *temp_root = ATree->root;
        (ATree->root)->left->parent = NULL;
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

        node->left->parent = node;
        node->right->parent = node;

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

static void DumpNodes(FILE *graph, Node *node, int mode)
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
    else //if mode == LINK_NODE
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

//TODO: add system calls for opening graph dump
void GraphDump(Akinator_Info *Akinator)
{
    fclose(fopen("graph.txt", "w"));
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

    // system("dot graph.txt -T png -o dump.png");
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

static void FreeMe(Akinator_Info *Akinator)
{
    //ahh.. finally free...
    TreeDtor(Akinator->AkinatorTree);
    free(Akinator->buffer);
    free(Akinator);

    return;
}

static char GetChar()
{
    char letter = getchar();
    if(letter != '\n')
    {
        char ch = 0;
        while((ch = getchar()) != '\n')
        {
            continue;
        }
    }

    return letter;
}

void PlayAkinator()
{
    int size = CountSymbols("sheesh.txt");

    char *buffer = ReadToBuffer("sheesh.txt", size);

    Akinator_Info *Akinator = GetAkinatorStruct(buffer);
    
    char interaction = 0;

    printf("Welcome to Akinator!\n"
        "Press [p]lay/[s]ave/[d]ump/descr[i]ption/[c]ompare/[q]uit\n");

    while((interaction = GetChar()) != 'q')
    {
        switch(interaction)
        {
            case 'p':
                printf("Guess:\n");
                Guess(Akinator->AkinatorTree->root);
                break;
            case 's':
                // printf("SaveTree:\n");
                // SaveTree(); 
                break;
            case 'd':
                printf("GraphDump:\n");
                GraphDump(Akinator); 
                break;
            case 'i':
                // printf("Describe:\n");
                // Describe(Akinator, stk); 
                break;
            case 'c': 
                // printf("Compare:\n");
                // Compare(); 
                break;

            default:
                printf("Invalid input. Type p/s/d/i/c/q");
                break;
        }
        printf("Press [p]lay/[s]ave/[d]ump/descr[i]ption/[c]ompare/[q]uit\n");
    }

    FreeMe(Akinator);
    return;
}

// void Describe(Akinator_Info *Akinator, Stack *stk)
// {
//     //TODO: rewrite stack so it accepts pointers 
// }

//can be written with using stack and ->parent
void Guess(Node *node)
{
    char interaction = '!';
    Node *tmp_node = NULL; //potentional_answer_node
    char tmp_interaction = '!';

    while(node != NULL)
    {
        printf("%s?\n", node->data);
        
        tmp_node = node;
        tmp_interaction = interaction;
        
        interaction = GetChar();
        if(interaction == 'y')
        {
            node = node->left;
        }
        else if(interaction == 'n')
        {
            node = node->right;
        }
        else 
        {
            printf("Invalid input. Type y/n \n");
        }
    }

    if(interaction == 'n')
    {
        printf("What a pity! Do you want to add this person to database?\n");
        //TODO: add when invalid input 
        printf("y/n : ");
        if((interaction = GetChar()) == 'y')
        {
            char *guessed_person = (char *)calloc(MAX_CHAR, sizeof(char)); 
            char *difference = (char *)calloc(MAX_CHAR, sizeof(char)); 
            
            printf("Who was it?\n:");
            scanf("%s", guessed_person);

            printf("Whats the difference between \"%s\" and \"%s\"?\n:", tmp_node->data, guessed_person);
            scanf("%s", difference);

            Node *temp_node = NULL;

            if(tmp_interaction == 'y')
            {
                tmp_node->parent->left = CreateNode(difference);
                temp_node = tmp_node->parent->left;
            }
            else
            {
                tmp_node->parent->right = CreateNode(difference);
                temp_node = tmp_node->parent->right;
            }

            temp_node->left = CreateNode(guessed_person);
             
            temp_node->right = tmp_node;
            tmp_node->parent = temp_node;
        }        

    }

    printf("Thanks for playing!\n");
    
    return;
}