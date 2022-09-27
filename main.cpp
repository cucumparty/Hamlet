#include "file.h"

int main()
{
    FILE *in_file = NULL;
    FILE *out_file = NULL;

    struct Constructor text_ctor; 

    if((in_file = fopen("hamlet_text.txt", "r")) == NULL)
    {
        fprintf(stdout, "The file can't be opened.\n");
        return EXIT_FAILURE;
    }

    int n_pointers = Text_Construct(in_file, &text_ctor);   
    
    if(fclose(in_file) != 0)
        fprintf(stderr, "The file can't be closed.\n");                

    if((out_file = fopen("output_text.txt", "w+")) == NULL)
    {
        fprintf(stdout, "The file can't be opened.\n");
        return EXIT_FAILURE;
    }
    
    Alphabet_sort(out_file, text_ctor.text, n_pointers);

    Rhyme_sort(out_file, text_ctor.text, n_pointers);
    
    Print_direct_text(out_file, text_ctor.buf, text_ctor.n_symb);

    if(fclose(out_file) != 0)
        fprintf(stderr, "The file can't be closed.\n");
}