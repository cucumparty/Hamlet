#include "file.h"

int Count_strings(char buf[], long long n_symb, char symb)
{
    assert (buf != NULL);

    int i = 0;
    int counter = 0;
    
    for(i = 0; i < n_symb + 1; i++)
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
    
    for(i = 0; i < n_symb; i++)
    {
        if(buf[i] == old_symb)
        {
            buf[i] = new_symb;

            text[x].pointer = &(buf[i + 1]);
            text[x - 1].length  = &(buf[i]) - text[x - 1].pointer;
            x++;
        }
    }
    text[x - 1].length = &(buf[i]) - text[x - 1].pointer;
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

void Alphabet_sort(FILE* out_file, struct String_struct text[], int n_pointers)
{
    assert(out_file != NULL);

    qsort(text, n_pointers + 1, sizeof(text[0]), &Qsort_Comparator);

    int i = 0;
    for(i = 0; i < n_pointers + 1; i++)
    {
        fprintf(out_file, "%s\n", text[i].pointer);
    }
}

int Qsort_Comparator(const void* a, const void* b)
{
    const char* s1 = ((String_struct*)a)->pointer;
    const char* s2 = ((String_struct*)b)->pointer;
    int s1_len     = ((String_struct*)a)->length;
    int s2_len     = ((String_struct*)b)->length;

    while(*s1 != '\0' || *s2 != '\0')
    {
        while(isalpha(*s1) == 0)
            s1++;
        while(isalpha(*s2) == 0)
            s2++;

        if(*s1 == *s2)
        {
            s1++;
            s2++;
        }
        else if(*s1 < *s2)
            return FIRST_BIGGER;
        else
            return SECOND_BIGGER;
    }
    if(s1_len > s2_len)
        return SECOND_BIGGER;
    else
        return FIRST_BIGGER; 
}

void Rhyme_sort(FILE* out_file, struct String_struct text[], int n_pointers)
{
    assert(out_file != NULL);

    My_sort(text, n_pointers);

    int i = 0;
    for(i = 0; i < n_pointers + 1; i++)
    {
        fprintf(out_file, "%s\n", text[i].pointer);
    }
}

void My_sort(struct String_struct text[], int n_pointers)
{
    int i = 0;
    int x = 0;
    char* s1 = NULL;
    char* s2 = NULL;

    for(x = 0; x < n_pointers; x++)
    {
        for(i = n_pointers; i > x; i--)
        {
            s1 = text[i].pointer + text[i].length - 1;
            s2 = text[i - 1].pointer + text[i - 1].length - 1;

            while(s1 > (text[i].pointer - 1) || s2 > (text[i - 1].pointer - 1))
            {
                while(isalpha(*s1) == 0)
                    s1--;
                while(isalpha(*s2) == 0)
                    s2--;

                if(*s1 == *s2)
                {
                    s1--;
                    s2--;
                } 

                if(*s1 < *s2)
                {
                    char* temp = text[i].pointer;
                    text[i].pointer = text[i - 1].pointer;
                    text[i - 1].pointer = temp;

                    int len = text[i].length;
                    text[i].length = text[i - 1].length;
                    text[i - 1].length = len;
                    break;
                }
                if(*s1 > *s2)
                    break;
            }

            if((text[i].length < text[i - 1].length) && 
                (s1 == (text[i].pointer - 1) || s2 == (text[i - 1].pointer - 1)))
            {
                char* temp_1 = text[i].pointer;
                text[i].pointer = text[i - 1].pointer;
                text[i - 1].pointer = temp_1;

                int len_1 = text[i].length;
                text[i].length = text[i - 1].length;
                text[i - 1].length = len_1;
            }                    

        }
    }

}