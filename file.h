//!@mainpage
//!This is a program to print a text in outfile:
//!1)by alphabet
//!2)by the rhyme
//!3)directly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

//!Structure with pointers to strings and the length of the string
struct String_struct{
    char* pointer;
    int   length;
};

//!Structure with structure with the type stat, array with the name buf, number of symbols in our file, structure with the type String_struct
struct Constructor{
    struct stat buffer;
    char* buf;
    unsigned int n_symb;
    struct String_struct* text;
};

//!Constants for Qsort_Comparator
enum Compare_Const{
    FIRST_BIGGER  = -1,
    EQUAL         =  0,
    SECOND_BIGGER =  1
};


//! Consructor of the text
//!
//! @param [in] in_file     The file, from where we take the text
//! @param [in] text_ctor   The pointer to the structure with the type Constructor
//!
//! @return Number of strings
int Text_Construct(FILE* in_file, struct Constructor* text_ctor);

//! Count the strings in the file
//!
//! @param [in] buf     Buffer with the text 
//! @param [in] n_symb  Number of symbols in the buffer
//! @param [in] symb    The symbol by which divide strings('\n')
//!
//! @return Number of strings
int Count_strings(char buf[], unsigned int n_symb, char symb);

//! Build the structure the type String_struct
//!
//! @param [in] buf         Buffer with the text
//! @param [in] text        The structure type String_struct 
//! @param [in] n_symb      Number of symbols in the buffer
//! @param [in] old_symb    The old symbol, that should be replaced('\n')
//! @param [in] new_symb    The new symbol, that will replace the old one('\0')
void Build_struct(char buf[], struct String_struct text[], 
                  unsigned int n_symb, char old_symb, char new_symb);

//! Print the text directly
//!
//! @param [in] out_file     The file, where the text should be written 
//! @param [in] buf          Buffer with the text
//! @param [in] n_symb      Number of symbols in the buffer
void Print_direct_text(FILE* out_file, char buf[], unsigned int n_symb);

//! The comparator for qsort-function
//!
//! @param [in] a   The pointer to the first structure
//! @param [in] b   The pointer to the second structure 
//!
//! @return  The constant from Compare_const to show which string is bigger
int Qsort_Comparator(const void* a, const void* b);

//! Print the text by alphabet
//!
//! @param [in] out_file     The file, where the text should be written 
//! @param [in] text         The structure type String_struct  
//! @param [in] n_pointers   Number of pointers(begin from zero)
void Alphabet_sort(FILE* out_file, struct String_struct text[], int n_pointers);

//! Print the text by rhyme
//!
//! @param [in] out_file     The file, where the text should be written 
//! @param [in] text         The structure type String_struct  
//! @param [in] n_pointers   Number of pointers(begin from zero)
void Rhyme_sort(FILE* out_file, struct String_struct text[], int n_pointers);

//! My bubble sort for Rhyme_sort
//!
//! @param [in] out_file     The file, where the text should be written 
//! @param [in] n_pointers   Number of pointers(begin from zero)
void My_sort(struct String_struct text[], int n_pointers);

//! Destructor of the text
//!
//! @param [in] text_ctor   The pointer to the structure with the type Constructor
void Text_Destruct(struct Constructor* text_ctor);