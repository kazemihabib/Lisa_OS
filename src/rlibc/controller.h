typedef int word;


#ifndef ctype.h
#include "ctype.h"
#endif

#ifndef stdio.h
#include "stdio.h"
#endif
#ifndef stdlib.h
#include "stdlib.h"
#endif
#ifndef string.h
#include "string.h"
#endif
struct data;
struct text;

/* add more datatype support to the structure */
struct data
{
	char *label;   //is a pointer to start of a string
	char *type;
	char *string;
	word word;     //data of type word
	int byte;
	struct data * next;
};
struct data *data_first;
struct data *data_head;

struct text
{
	char *line;
	char *label;
	char *args[3];
	struct text *adress;
	int isMain;
	struct text *next;
};
struct text *text_first;
struct text *text_head;
void getDataSegment ( FILE *file_ptr );
void getTextSegment ( FILE *file_ptr );
char *readWordFromFile ( FILE *file_ptr, char c , char *string);
void move_to_memory(FILE *file_ptr);
