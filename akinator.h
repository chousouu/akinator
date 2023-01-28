#ifndef AKINATOR_H
#define AKINATOR_H

#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/stat.h>

#include "tree.h"

enum graphviz
{
    CREATE_NODE = 0,
    LINK_NODE   = 1,
};

#define MAX_CHAR 30

struct Option_info
{
    char *text_ptr;
    int len; // is it needed?
};

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

void Guess(Node *node);

#endif// AKINATOR_H

//{root{left{left_left}{left_right}}{right}}