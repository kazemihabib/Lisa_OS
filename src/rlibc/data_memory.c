#include "data_memory.h"
#ifndef instruction_memory.h
#include "instruction_memory.h"
#endif
#ifndef controller.h
#include "controller.h"
#endif
#include "stdlib.h"
typedef int word;
char *getWord ( FILE *file_ptr )
{
//printf("in getword\n");
	char *string = (char *) malloc( 20 * sizeof(char) ), c;
	int index = 0;
	while ( ( c = fgetc(file_ptr) ) != ' ' && c != '\t' && c != ',' && c != ':' && c != '\n' && c != '\r' )  
	{
		string[index++] = c;
	}
	string[index] = '\0';
//printf("%d\n", *string);
	return (string);
}

/* return 1 on succes and 0 on failure [fix this]*/
/* add more support for data types*/
void save_data_to_memory( char *typeName, FILE *file_ptr )
{
	int index = 0;
	char c, byte_ascii;
	char *ip = (char *) malloc ( 16 * sizeof(char) );    //see if its right
	//word word_value;
	/*datatypes table*/
	char type1[] = "word",
		type2[] = "long",   //not sure if its a datatype of MIPS
		type3[] = "byte ",
		type4[] = "halfword",
		type5[] = "space",
		type6[] = "asciiz",
		type7[] = "ascii";

	if ( !strcmp(typeName, type6) )   //type 6 = asciiz
	{
		data_head->string = asciiz(file_ptr); // write a asciiz function to return a pointer to data_first of the string [done]
		data_head->type = typeName;
	}
	else if ( !strcmp(typeName, type1) )
	{
		c = fgetc(file_ptr);
		while (isspace(c))
		{
			c = fgetc(file_ptr);
		}
		while ( isdigit(c) )
		{
			ip[index++] = c;
			c = fgetc(file_ptr);
		}
		ip[index] = '\0';
		data_head->word = (word) atoi(ip);  //its better to be casted to word datatype for readability
		data_head->type = typeName;
	}
	else if ( !strcmp(typeName, type3) )  //type3 = byte
	{
		c = fgetc(file_ptr);
		while (isspace(c))
		{
			c = fgetc(file_ptr);
		}
		byte_ascii = fgetc(file_ptr);         //considered that after ' is a character could raise an error if there was no ' at the end
		while ( (c = fgetc(file_ptr)) != '\n' && c != '\r' && c != '\0' );
		data_head->byte = byte_ascii;  
		data_head->type = typeName;
	}
	free(ip, sizeof(char) * 16);
}

