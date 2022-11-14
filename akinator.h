#ifndef AKINATOR_H
#define AKINATOR_H

#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/stat.h>

#include "tree.h"


#define DEB(...) printf(__VA_ARGS__)


void CreateQuestion(Node *destination, char *buffer, int index, int buffer_size);

char *ReadToBuffer(const char *filename, int size);

int CountSymbols(const char *filename);

Tree* BufferParser(char *buffer, int buffer_size);


#endif// AKINATOR_H