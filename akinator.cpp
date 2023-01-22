#include "akinator.h"
// xz kak nazvat, no ne parser 
Akinator_Info *GetAkinatorStruct(char *buffer, int buffer_size)
{
    int total_lines = 0;
    int word_len = 0; 

    for(int i = 0; i < buffer_size; i++)
    {
        if(buffer[i] == '{')
        {
            total_lines++;
        }
    }

    // get total_lines, ptr of words,
    Option_info *text_info = (Option_info *)calloc(total_lines + 2, sizeof(Option_info));
    /////////////////////////////////////////////////////////////^
    char sep[10]="{}";
    int i = 0;

    text_info[i].text_ptr = strtok(buffer, sep);

    while (text_info[i].text_ptr != NULL)
    {
        i++;
        text_info[i].text_ptr = strtok(NULL, sep);
    }

    Akinator_Info *Akinator = (Akinator_Info *)calloc(1, sizeof(Akinator_Info));

    Akinator->buffer = buffer;
    Akinator->Strings = text_info;
    Akinator->lines_total = total_lines;

    return Akinator;
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