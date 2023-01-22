#include "akinator.h"
// xz kak nazvat, no ne parser 
Akinator_Info *GetAkinatorStruct(char *buffer, int buffer_size)
{
    int total_lines = 0;
    int word_len = 0; 

    char **save_addy_start_of_word = (char **)calloc(buffer_size, sizeof(char*));
    //if NULL ->return;

// TODO : add len of strings 

    // get total_lines, ptr of words,
    for(int i = 0; i < buffer_size; i++)
    {
        if(buffer[i] == '{')
        {
            save_addy_start_of_word[2 * total_lines] = word_len;
            save_addy_start_of_word[2 * total_lines + 1] = buffer + i + 1;
            word_len = 0;
            total_lines += 1;
        }
        if(buffer[i] != '{' && buffer[i] != '}')
        {
            word_len++;
        }
    }

    Option_info *text = (Option_info *)calloc(total_lines, sizeof(Option_info));
    for(int i = 0; i < total_lines; i++)
    {
        word_len = save_addy_start_of_word[i + 1] - save_addy_start_of_word[i];
        text[i].text_ptr = save_addy_start_of_word[i];
        text[i].len = 0;
    }


    Akinator_Info *Akinator = (Akinator_Info *)calloc(1, sizeof(Akinator_Info));

    Akinator->buffer = buffer;
    Akinator->Strings = text;
    Akinator->lines_total = total_lines;

    free(save_addy_start_of_word);

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