#ifndef AKINATOR_H
#define AKINATOR_H

#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/stat.h>

#include "tree.h"

struct Option_info
{
    char *text_ptr;
    int len; // is it needed?
};

struct Akinator_Info
{
    char *buffer;
    struct Option_info *Strings;
    int lines_total;
};

#define DEB(...) printf(__VA_ARGS__)

Akinator_Info *GetAkinatorStruct(char *buffer, int buffer_size);

char *ReadToBuffer(const char *filename, int size);

int CountSymbols(const char *filename);

#endif// AKINATOR_H