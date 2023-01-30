#ifndef AKINATOR_H
#define AKINATOR_H

#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/stat.h>

#include "stack.h"
#include "tree.h"

enum graphviz
{
    CREATE_NODE = 0,
    LINK_NODE   = 1,
};

#define MAX_CHAR 30

#define FillArray(X)                                                                                      \
        for(int i = (size##X) - 1; i >= 0; i--) {path##X[i] = (char *)calloc(MAX_CHAR * 2, sizeof(char)); \
        strcpy(path##X[i], StackPop(&(stk##X), &err_code));}                                              \
        for(int i = 0; i < (size##X); i++)                                                                \
        {                                                                                                 \
            if(i + 1 != (size##X))                                                                        \
            {if(strcmp((path##X)[i + 1], not_) == 0)                                                      \
            {                                                                                             \
                strcat((path##X)[i + 1], (path##X)[i]);                                                   \
                strcpy(path##X[i], path##X[i + 1]);                                                       \
                free(path##X[i+1]); path##X[i+1] = NULL;                                                  \
            }}                                                                                            \
        }

struct Akinator_Info
{
    char *buffer;
    Tree *AkinatorTree;
    int lines_total;
};

#define DEB(...) printf(__VA_ARGS__)

Akinator_Info *GetAkinatorStruct(char *buffer);

char *ReadToBuffer(const char *filename, int size);

int CountSymbols(const char *filename);

char *GetString(const char *buffer);

void GraphDump(Akinator_Info *Akinator);

void PlayAkinator();

void SaveTree(Node *node);

void Guess(Akinator_Info *Akinator);

void Describe(Akinator_Info *Akinator);

void Compare(Akinator_Info *Akinator);

Node *FindCharacter(Node *node, char * character, Stack *stk);




#endif// AKINATOR_H

//{root{left{left_left}{left_right}}{right}}