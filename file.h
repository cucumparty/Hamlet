#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct String_struct{
    char* pointer;
    int   length;
};

int Count_strings(char buf[], long long n_symb, char symb);

void Build_struct(char buf[], struct String_struct text[], 
                  long long n_symb, char old_symb, char new_symb);

void Print_direct_text(FILE* out_file, char buf[], long long n_symb);
