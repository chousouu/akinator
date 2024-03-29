#include "akinator.h"

char not_[] = "not ";

static Tree *FillTree(char **buffer, Node *node, int *tree_size)
{
    if(**buffer == '\0')
    {
        return NULL;
    }

    if(**buffer == '{')
    {
        (*tree_size)++;
        (*buffer)++;
        node->data = GetString(*buffer);
    
        while(**buffer != '{' && **buffer != '}')
        {
            (*buffer)++;
        }
        
        if(**buffer == '}') 
        {
            (*buffer)++;
            return NULL;   
        }
    }
    else if(**buffer == '}')
    {
        (*buffer)++;
        return NULL; 
    }

    node->left  = CreateNode(NULL);
    node->right = CreateNode(NULL);

    node->left->parent = node;
    node->right->parent = node;

    FillTree(buffer,node->left, tree_size);
    FillTree(buffer,node->right, tree_size);

    (*buffer)++;             

    return NULL;    
}

static Tree *GetTree(char *buffer, int *tree_size)
{
    Tree *ATree = CreateTree(NULL);
    
    FillTree(&buffer, ATree->root, tree_size);

    return ATree;
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

    system("dot graph.txt -T png -o dump.png");
}

Akinator_Info *GetAkinatorStruct(char *buffer)
{
    Akinator_Info *Akinator = (Akinator_Info *)calloc(1, sizeof(Akinator_Info));

    int tree_size = 0;

    *Akinator = 
    {
        .buffer = buffer,
        .AkinatorTree = GetTree(buffer, &tree_size),
        .lines_total = tree_size,
    };

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
                Guess(Akinator);
                break;
            case 's':
            {                
                printf("SaveTree:\n");
                fclose(fopen("new_tree.txt", "w"));
                FILE *new_tree = fopen("new_tree.txt", "a");
                
                SaveTree(Akinator->AkinatorTree->root, new_tree); 
                
                fclose(new_tree);

                break;
            }
            case 'd':
                printf("GraphDump:\n");
                GraphDump(Akinator); 
                break;
            case 'i':
                printf("Describe:\n");
                Describe(Akinator); 
                break;
            case 'c': 
                printf("Compare:\n");
                Compare(Akinator); 
                break;

            default:
                printf("Invalid input. Type p/s/d/i/c/q\n");
                break;
        }
        printf("Press [p]lay/[s]ave/[d]ump/descr[i]ption/[c]ompare/[q]uit\n");
    }

    FreeMe(Akinator);
    return;
}

Node *FindCharacter(Node *node, char * character, Stack *stk)
{
    StackPush(stk, node->data);

    if(strcmp(node->data, character) == 0)
    {
        return node;
    }

    if(node->left != NULL)
    {
        Node *result = FindCharacter(node->left, character, stk);
        if(result) return result;
    }

    int err_code = 0;
    
    if(node->right != NULL)
    {
        StackPush(stk, not_);
        Node *result = FindCharacter(node->right, character, stk);
        if(result != NULL) 
        {
            return result;
        }
        else 
        {
            StackPop(stk, &err_code);
        }
    }

    StackPop(stk, &err_code);

    return NULL;
}

void SaveTree(Node *node, FILE *new_tree)
{
    fprintf(new_tree, "{");
    
    if(node) {fprintf(new_tree, "%s", node->data);}
    
    if(node->left == NULL && node->right == NULL) {fprintf(new_tree, "}"); return;}
    
    SaveTree(node->left, new_tree);
    SaveTree(node->right, new_tree);
    
    fprintf(new_tree, "}");
}

void Compare(Akinator_Info *Akinator)
{
    int err_code = 0;

    Stack stk1 = {};
    StackCtor(&stk1, 10);
    char *character1 = (char *)calloc(MAX_CHAR, sizeof(char));

    Stack stk2 = {};
    StackCtor(&stk2, 10);
    char *character2 = (char *)calloc(MAX_CHAR, sizeof(char));

    printf("Who do you want to compare?\n");

    printf("Character1 : ");
    scanf("%[^\n]", character1); getchar();

    printf("Character2 : ");
    scanf("%[^\n]", character2); getchar();

    Node *node1 = FindCharacter(Akinator->AkinatorTree->root, character1, &stk1);
    StackPop(&stk1, &err_code); // removing from stack char's name
    
    Node *node2 = FindCharacter(Akinator->AkinatorTree->root, character2, &stk2);
    StackPop(&stk2, &err_code); // removing from stack char's name

    if(node1 == NULL || node2 == NULL) 
    {
        printf("Unknown Object\n");
    }
    else 
    {
        printf("Whats the difference between \"%s\" and \"%s\"?\n", node1->data, node2->data);
        printf("===========================\n");

        int size1 = stk1.size;
        int size2 = stk2.size;

        char **path1 = (char**)calloc(size1, sizeof(char*));
        char **path2 = (char**)calloc(size2, sizeof(char*));

        FillArray(1);
        FillArray(2);

        for(int i = 0; i < size1 && i < size2; i++)
        {
            if(path1[i] != NULL && path2[i] != NULL)
            {
                if(strcmp(path1[i], path2[i]) == 0)
                {
                    printf("They are both %s\n", path1[i]);
                }
                else
                {
                    printf(" \"%s\" is %s, but ", node1->data, path1[i]);
                    printf(" \"%s\" is %s\n", node2->data, path2[i]);
                }
            }
        }
        printf("===========================\n");

        for(int i = 0; i < size1; i++)
        {
            if(path1[i]) free(path1[i]);        
        }
        for(int i = 0; i < size2; i++)
        {
            if(path2[i]) free(path2[i]);        
        }
        free(path1);
        free(path2);
    }

    free(character1);
    StackDtor(&stk1);

    free(character2);
    StackDtor(&stk2);

    return;
}

void Describe(Akinator_Info *Akinator)
{
    Stack stk = {};
    StackCtor(&stk, 10);
    int err_code = 0;

    char *character = (char *)calloc(MAX_CHAR, sizeof(char));

    printf("What character's description you want to hear?\n");

    scanf("%[^\n]", character);
    getchar(); // skips '\n'

    Node *dest = FindCharacter(Akinator->AkinatorTree->root, character, &stk);
    
    if(dest == NULL)
    {
        printf("Unknown object\n");
    }
    else
    {
        printf("%s -> ", StackPop(&stk, &err_code));
        for(int i = stk.size; i >= 1; i--)
        {
            printf("%s ", StackPop(&stk, &err_code));
        }
        printf("\n");
    }

    StackDtor(&stk);
    free(character);
    return;
}

void Guess(Akinator_Info *Akinator)
{
    char interaction = '!';
    Node *potentional_answer_node = NULL;
    char tmp_interaction = '!';
    
    Node *node = Akinator->AkinatorTree->root;

    while(node != NULL)
    {
        printf("%s?\n", node->data);
        
        potentional_answer_node = node;
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
            scanf("%[^\n]", guessed_person); getchar();

            printf("Whats the difference between \"%s\" and \"%s\"?\n:", potentional_answer_node->data, guessed_person);
            scanf("%[^\n]", difference); getchar(); // skips '\n' left after scanf

            Node *temp_node = NULL;

            if(tmp_interaction == 'y')
            {
                potentional_answer_node->parent->left = CreateNode(difference);
                temp_node = potentional_answer_node->parent->left;
            }
            else
            {
                potentional_answer_node->parent->right = CreateNode(difference);
                temp_node = potentional_answer_node->parent->right;
            }

            temp_node->left = CreateNode(guessed_person);
             
            temp_node->right = potentional_answer_node;
            potentional_answer_node->parent = temp_node;
        }        
    }

    printf("Thanks for playing!\n");
    
    return;
}