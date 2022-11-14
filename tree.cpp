#include "tree.h"

Tree *CreateTree(elem_t value)
{
    Tree *tree = (Tree *)calloc(1, sizeof(Tree));

    if(tree == NULL)
    {
        printf("ERROR CREATETREE\n");
    }
    
    tree->size = 0;
    
    tree->root = CreateNode(value);

    tree->size = 1;

    return tree;
}

Node *CreateNode(elem_t value)
{
    Node *node_ptr = (Node *)calloc(1, sizeof(Node));

    if(node_ptr == NULL) 
    {
        printf("Error create node\n");
        return NULL;
    }

    node_ptr->data = value;
    node_ptr->left  = NULL;
    node_ptr->right = NULL;

    return node_ptr;
}

//net tree->size++; ???? nuzhen lix

Node *AddNode(struct Node *tree, elem_t value, int child)
{
    Node *new_node = CreateNode(value);

    if(child == LEFT_NODE)
    {
        if(tree->left != NULL)
        {
            new_node->left = tree->left;
        }

        tree->left = new_node;
    }
    else if(child == RIGHT_NODE)
    {
        if(tree->right != NULL)
        {
            new_node->right = tree->right;
        }

        tree->right = new_node;
    }

    return new_node;
}

void InOrder(struct Node *tree)
{
    if(!tree) return;

    if(tree->left)
    {
        InOrder(tree->left);
    }
    printf("%s ", tree->data);
    if(tree->right)
    {
        InOrder(tree->right);
    }

    return;
}

void NodeDtor(struct Node *node)
{
    if(node->left)
    {
        NodeDtor(node->left);
    }
    if(node->right)
    {
        NodeDtor(node->right);   
    }
    free(node);
}

void TreeDtor(struct Tree *tree)
{
    NodeDtor(tree->root);
    tree->size = 0;
    free(tree);

    return;
}