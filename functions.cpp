#include "file.h"

int Text_Construct(FILE* in_file, struct Constructor* text_ctor)
{
    assert(in_file != NULL);
    assert(text_ctor != NULL);

    fstat (fileno (in_file), &(text_ctor->buffer));

    text_ctor->n_symb = (unsigned int)text_ctor->buffer.st_size; 

    text_ctor->buf = (char*)calloc(text_ctor->n_symb + 1, sizeof(char));
    fread(text_ctor->buf, sizeof(char), text_ctor->n_symb, in_file);
    text_ctor->buf[text_ctor->n_symb] = '\0'; 

    int n_pointers = Count_strings(text_ctor->buf, text_ctor->n_symb, '\n');

    text_ctor->text = (struct String_struct*)calloc((size_t)n_pointers + 1, sizeof(struct String_struct)); 

    Build_struct(text_ctor->buf, text_ctor->text, text_ctor->n_symb, '\n', '\0');

    return n_pointers;
}

int Count_strings(char buf[], unsigned int n_symb, char symb)
{
    assert (buf != NULL);
    int counter = 0;
    
    for(unsigned int i = 0; i < n_symb + 1; i++)
    {
        if(buf[i] == symb)
            counter ++;
    }
    return counter;
}

void Build_struct(char buf[], struct String_struct text[], 
                  unsigned int n_symb, char old_symb, char new_symb)
{
    assert(buf  != NULL);
    assert(text != NULL);
    
    int prev = 1;
    
    text[0].pointer = buf;
    
    for(unsigned int i = 0; i < n_symb; i++)
    {
        if(buf[i] == old_symb)
        {
            buf[i] = new_symb;

            text[prev].pointer = &(buf[i + 1]);
            text[prev - 1].length  = (int)(&(buf[i]) - text[prev - 1].pointer);
            prev++;
        }
    }
    text[prev - 1].length = (int)(&(buf[n_symb]) - text[prev - 1].pointer);
}

void Print_direct_text(FILE* out_file, char buf[], unsigned int n_symb)
{
    assert(buf      != NULL);
    assert(out_file != NULL);

    fprintf(out_file, "Direct sorting:\n\n");

    for(unsigned int i = 0; i < n_symb; i++)
    {
        if(buf[i] == '\0')
            buf[i] = '\n';
        fprintf(out_file, "%c", buf[i]);
    }
    
}

void Alphabet_sort(FILE* out_file, struct String_struct text[], int n_pointers)
{
    assert(out_file != NULL);

    qsort(text, (size_t)(n_pointers + 1), sizeof(text[0]), &Qsort_Comparator);

    fprintf(out_file, "Alphabet sorting:\n\n");

    for(int i = 0; i < n_pointers + 1; i++)
    {
        fprintf(out_file, "%s\n", text[i].pointer);
    }
    fprintf(out_file, "\n");
}

int Qsort_Comparator(const void* a, const void* b)
{
    assert(a != 0);
    assert(b != 0);
    
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

    fprintf(out_file, "Rhyme sorting:\n\n");

    for(int i = 0; i < n_pointers + 1; i++)
    {
        fprintf(out_file, "%s\n", text[i].pointer);
    }
    fprintf(out_file, "\n");
}

void My_sort(struct String_struct text[], int n_pointers)
{
    char* s1 = NULL;
    char* s2 = NULL;

    for(int b_sort = 0; b_sort < n_pointers; b_sort++)
    {
        for(int i = n_pointers; i > b_sort; i--)
        {
            s1 = text[i].pointer     + text[i].length     - 1;
            s2 = text[i - 1].pointer + text[i - 1].length - 1;

            while(s1 > (text[i].pointer - 1) || s2 > (text[i - 1].pointer - 1))
            {
                while(isalpha(*s1) == 0)
                {
                    if(s1 != text[i].pointer)
                        s1--;
                    else    
                        break;
                }
                while(isalpha(*s2) == 0)
                {
                    if(s2 != text[i - 1].pointer)
                        s2--;
                    else
                        break;
                }

                if(*s1 == *s2)
                {
                    if(s2 != text[i - 1].pointer && s1 != text[i].pointer)
                    {
                        s1--;
                        s2--;
                    }
                    else
                        break;
                } 
                else if(*s1 < *s2)
                {
                    char* temp          = text[i].pointer;
                    text[i].pointer     = text[i - 1].pointer;
                    text[i - 1].pointer = temp;

                    int len            = text[i].length;
                    text[i].length     = text[i - 1].length;
                    text[i - 1].length = len;
                    break;
                }
                else if(*s1 > *s2)
                    break;
                else
                    break;
            }

            if((text[i].length < text[i - 1].length) && 
                (s1 == (text[i].pointer - 1) || s2 == (text[i - 1].pointer - 1)))
            {
                char* temp_1        = text[i].pointer;
                text[i].pointer     = text[i - 1].pointer;
                text[i - 1].pointer = temp_1;

                int len_1          = text[i].length;
                text[i].length     = text[i - 1].length;
                text[i - 1].length = len_1;
            }                    
        }
    }
}

void Text_Destruct(struct Constructor* text_ctor)
{
    free(text_ctor->buf);
    free(text_ctor->text);

    text_ctor->n_symb = (unsigned int)(-7777);
}