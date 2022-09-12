#include "file.h"

int Count_strings(char buf[], long long n_symb, char symb)
{
    assert (buf != NULL);

    int i = 0;
    int counter = 0;
    
    for(i = 0; i < n_symb; i++)
    {
        if(buf[i] == symb)
            counter ++;
    }
    return counter;
}

void Build_struct(char buf[], struct String_struct text[], 
                  long long n_symb, char old_symb, char new_symb)
{
    assert(buf  != NULL);
    assert(text != NULL);
    
    int i = 0;
    int x = 1;
    
    text[0].pointer = buf;
    char* prev_pointer = buf;
    
    for(i = 0; i < n_symb; i++)
    {
        if(buf[i] == old_symb)
        {
            buf[i] = new_symb;

            text[x].pointer = &(buf[i + 1]);
            text[x].length  = &(buf[i + 1]) - prev_pointer;
            x++;
            prev_pointer = &(buf[i]);
        }
    }
}

void Print_direct_text(FILE* out_file, char buf[], long long n_symb)
{
    assert(buf      != NULL);
    assert(out_file != NULL);

    int i = 0;
    for(i = 0; i < n_symb; i++)
    {
        if(buf[i] == '\0')
            buf[i] = '\n';
        fprintf(out_file, "%c", buf[i]);
    }
    
}

