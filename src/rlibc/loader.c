#ifndef controller.h
#include "controller.h"
#endif
#ifndef data_memory.h
#include "data_memory.h"
#endif
#ifndef execution.h
#include "execution.h"
#endif

#include "string.h"

#include "loader.h"

#include "registers.h"

void loader(const char *programName)
{
//printf("salam");
	FILE *file_ptr;
	char c;
	char *dataSegment;
	//fclose(file_ptr);
	file_ptr = fopen(programName, "r");
	reset();
	while ( (c = fgetc(file_ptr)) != EOF )
	{
		// '=' is a binary operator and returns the value of assignment.
		while ( isspace( ( c = fgetc(file_ptr) ) ) );

		if ( c == '.' )
		{
			
			dataSegment = getWord(file_ptr);   // most return a pointer

			if ( !strcmp(dataSegment, "data") )
			{
				getDataSegment(file_ptr);
				putchar('\n');//print new line after printing datas.
				return;

			}
			else if ( !strcmp(dataSegment, "text") )
			{
				getTextSegment(file_ptr);
				return;
			}
			else if ( !strcmp(dataSegment, "end") )  // end of main ( add to read main )
			{
				return;
			}
		}
		else if ( c == '#' )
		{

			comment(file_ptr);
		}
	}

}

void reset(void)
{
	int i;
	for ( i = 0; i < 32; registers[i] = 0, i++);
	text_first = NULL;
	data_first = NULL;
	data_head = NULL;
	text_head = NULL;
}
