#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

struct String_struct{
    char* pointer;
    int   length;
};

enum Compare_Comst{
    FIRST_BIGGER  = -1,
    EQUAL         =  0,
    SECOND_BIGGER =  1
};

int Count_strings(char buf[], long long n_symb, char symb);

void Build_struct(char buf[], struct String_struct text[], 
                  long long n_symb, char old_symb, char new_symb);

void Print_direct_text(FILE* out_file, char buf[], long long n_symb);

int Qsort_Comparator(const void* a, const void* b);

void Alphabet_sort(FILE* out_file, struct String_struct text[], int n_pointers);

void Rhyme_sort(FILE* out_file, struct String_struct text[], int n_pointers);

void My_sort(struct String_struct text[], int n_pointers);