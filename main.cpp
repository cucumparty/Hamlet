#include "file.h"

int main()
{
    FILE *in_file = NULL;
    struct stat buffer;
    FILE *out_file = NULL;


    if((in_file = fopen("hamlet_text.txt", "r")) == NULL)
    {
        fprintf(stdout, "The file can't be opened.\n");
        return EXIT_FAILURE;
    }
    
    fstat (fileno (in_file), &buffer);
    long long n_symb = buffer.st_size;

    char buf[n_symb + 1];
    fread(buf, sizeof(char), n_symb, in_file);  
    
    if(fclose(in_file) != 0)
        fprintf(stderr, "The file can't be closed.\n");


    int n_pointers = Count_strings(buf, n_symb, '\n');
    struct String_struct text[n_pointers + 1];

    Build_struct(buf, text, n_symb, '\n', '\0');


    if((out_file = fopen("output_text.txt", "w+")) == NULL)
    {
        fprintf(stdout, "The file can't be opened.\n");
        return EXIT_FAILURE;
    }

    Print_direct_text(out_file, buf, n_symb);

    if(fclose(out_file) != 0)
        fprintf(stderr, "The file can't be closed.\n");
}