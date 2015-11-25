//#ifndef execution.h
//#include "execution.h"
//#endif
#ifndef stdlib.h
#include "stdlib.h"
#endif
#ifndef ctype.h
#include "ctype.h"
#endif
#ifndef string.h
#include "string.h"
#endif
#ifndef registers.h
#include "registers.h"
#endif
#ifndef instruction_memory.h
#include "instruction_memory.h"
#endif
#ifndef controller.h
#include "controller.h"
#endif
//struct process
//{
//	char *label;
//	char *adress;
//	char *args[3];         // maximum arguments is 3 in MIPS
//	struct process *next;
//};
//struct process *process_first;
//struct process *process_head;


char *readWordFromMemory ( char **strpp )
{
	char *string = (char *) malloc( 20 * sizeof(char) );
	int  index = 0;
	int strpp_index = 0;
	while ( **strpp  != ' ' && **strpp != '\t' && **strpp != ',' && **strpp != ':' && **strpp != '\n'  && **strpp != '\r')  
	{
		string[index++] = **strpp;
		(*strpp)++;
	}
	string[index] = '\0';
	return (string);
}

//return 0 if failed and 1 if succed
int execInst( const char *struc, const char *args )
{
	int argIndex = 0, argsIndex = 0, param1 = -1, param2 = -1, index = 0;
	char arg[10] = {0};
	char *function = (char *)  malloc ( 20 * sizeof(char) );

	while ( isspace ( *args ) ) ++args;
	while ( *args != '\0' && *args != '\r' )
	{
		//make this part a new function with appropriate functionalaty   ************
		argIndex=0;
		while ( isspace ( *args ) )
			++args;
		if ( *(args) == '$' )  // add support for non $ signs like printf and scanf functions call [done]
		{
			while ( isspace ( *args ) ) ++args;
			while ( *(args) != ',' && *(args) != ' ' && *(args) != '\t' && *(args) != '\0' && *(args) != '\r' && *(args) != '\n') // add comment support
			{
				arg[argIndex++] = *args;
				args++;
			}
			arg[argIndex] = '\0';
			text_head->args[argsIndex] = (char *) malloc( sizeof( char ) * strlen(arg) + 1);
			strcpy(text_head->args[argsIndex++], arg);
		}
		else 
		{
			if ( isdigit(*args) )
			{
				if(param1 == -1)
				{
					param1 = atoi(args);
				}
				else if (param2 == -1)
				{
					param2 = atoi(args++);
				}
			}
			else if (isalpha(args[0]))
			{
				while (  *args != ',' && *args != '\0' && *args != '\r' && *args != '\n' )
				{
					function[index++] = *(args++);
				}
				function[index] = '\0';
			}
			else
			{
				++args;
				param1 = param2 = -1;
				index = 0;
			}
		}
	}

	if ( !strcmp( struc, "la" ) )
	{
		if  ( index != 0 )
		{
			la( text_head->args[0], function );   //check if the sazeof can be reduced[done]
		free(function,sizeof(20 * sizeof(char)));
			return 1;
		}
		else
		{
			la( text_head->args[0], text_head->args[1] );
			return 1;
		}
	}
	else if ( !strcmp ( struc, "addu" ) )   //done
	{
		if ( param1 != -1 )
		{
			addu( text_head->args[0], registers[atoi(text_head->args[1] + 1)], param1 );
			return 1;
		}
		else
		{
			addu( text_head->args[0], registers[atoi(text_head->args[1] + 1)], registers[atoi(text_head->args[2] + 1)] );
			return 1;
		}
	}
	else if ( !strcmp ( struc, "slt" ))
	{
		slt( text_head->args[0], atoi(text_head->args[1] + 1), atoi(text_head->args[2] + 1)) ;
		return 1;
	}
	else if ( !strcmp ( struc, "lw" ) )
	{
		lw( text_head->args[0], function );
		free(function,sizeof(20 * sizeof(char)));
		return 1;
	}
	else if ( !strcmp ( struc, "sw" ) )  //[done]
	{
		sw ( text_head->args[0], function );
		free(function,sizeof(20 * sizeof(char)));
		return 1;
	}
	else if ( !strcmp ( struc, "j" ) )
	{
		return j( text_head->args[0] );
	}
	else if ( !strcmp ( struc, "bne" ) )
	{
		return bne ( text_head->args[0], text_head->args[1], text_head->args[2] );
	}
	else if ( !strcmp ( struc, "jal" ) )
	{
		jal( function );
		free(function,sizeof(20 * sizeof(char)));
		return 1;
	}
	else                    /********if the program crashed disable this else (change it to return a null***********/
		return 1;
	index = 0;
}

void comment ( FILE *file_ptr )
{
	int c;
	while ( (c = fgetc(file_ptr)) != '\n' );
}
//it returns 1 on succes and zero on failure
int isInstruction( char **strpp )
{
	char *tmp = (char *) malloc ( 20 * sizeof(char) );
	tmp = readWordFromMemory(&(*strpp));
	if ( execInst( tmp, *strpp ) )         //return te result of this
	{                                       // return boolean if it could run the instruction
		free(tmp,20 * sizeof(char));
		return 1;
	}
	else
	{
		free(tmp,20 * sizeof(char));
		return 0;
	}
}

