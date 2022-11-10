#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

const int LEFT_NODE = 0x32;
const int RIGHT_NODE = 0x64;

struct Node 
{
    elem_t data;
    Node *left;
    Node *right;
};

struct Tree
{
    Node *root;
    int size;
};

Tree *CreateTree(elem_t value);

Node *CreateNode(elem_t value);

Node *AddNode(struct Node *tree, elem_t value, int child);

void InOrder(struct Node *tree);

void NodeDtor(struct Node *node);

void TreeDtor(struct Tree *tree);
#endif// AKINATOR_H