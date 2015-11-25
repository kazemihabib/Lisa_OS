#define STRING_MAX 509


#include "controller.h"
#ifndef data_memory.h
#include "data_memory.h"
#endif
//#ifndef registers.h
//#include "registers.h"
//#endif
#ifndef execution.h
#include "execution.h"
#endif
void getDataSegment ( FILE *file_ptr )
{
	char *tmp, *labels;
	int index = 0;
	char c;
	labels = (char *) malloc ( 20 * sizeof(char) );
	while ( c = fgetc(file_ptr) )   // perhaps != EOF
	{

		if ( data_head == NULL )
		{
			data_first = ( struct data *) malloc ( sizeof( struct data ) );
			data_head = data_first;
			data_head->next = NULL;
			data_head->label = NULL;
			data_head->string = NULL;
			data_head->type = NULL;
		}
		else if ( data_head->next == NULL && data_head->label != NULL && data_head->type != NULL )   //change head->word to head->type[done]
		{
			data_head->next = ( struct data *) malloc ( sizeof ( struct data ) );
			data_head = data_head->next;
			data_head->next = NULL;
			data_head->label = NULL;
			data_head->string = NULL;
			data_head->type = NULL;
		}
		while ( isspace(c) || c == '\n' || c == '\r' )
		{
			c = fgetc(file_ptr);
		}

		if ( c == '#' )    // check for comment ( see if it works good )
		{
			comment(file_ptr);
		}
		else if ( c == '.' )
		{
			tmp = getWord(file_ptr);
			if ( !strcmp(tmp, "text") )
			{
				getTextSegment(file_ptr); //switch to text mode
				return;
			}
			else  //its a data type to be allocate
			{
				save_data_to_memory(tmp, file_ptr);
			}
		}
		else           // its a label
		{
			while  ( c != ':' )
			{
				while ( isspace(c) )
				{
					c = fgetc(file_ptr);
				}
				labels[index++] = c;
				c = fgetc(file_ptr);
			}
			labels[index] = '\0';
			data_head->label = (char *) malloc ( STRING_MAX * sizeof(char) );
			strcpy(data_head->label, labels);
			index = 0;
		}
	}
free(labels, sizeof(char) * 20);
free(labels, 20 * sizeof(char));
fclose("fib.txt");
}

void getTextSegment ( FILE *file_ptr )
{
	char * tmp_adress;    //to free the line_ptr memory
	int line_index = 0;
	char tmp[STRING_MAX] = {0};
	char *line_ptr;
	text_head = text_first;
	if ( !text_head )
	{
		text_first = ( struct text *) malloc ( sizeof( struct text ) );
		text_head = text_first;
		text_head->label = NULL;
		text_head->adress = NULL;
		text_head->next = NULL;
		text_head->line = NULL;
	}
	else if ( !text_head->next )
	{
		text_head->next = ( struct text *) malloc ( sizeof( struct text ) );
		text_head = text_head->next;
		text_head->label = NULL;
		text_head->adress = NULL;
		text_head->next = NULL;
		text_head->line = NULL;
	}
	move_to_memory(file_ptr);          /* transfer the text segment to the memory */
	text_head = text_first;
	while ( text_head != NULL)
	{
		line_ptr = (char *) malloc (STRING_MAX * sizeof(char));     
		tmp_adress = line_ptr;
		
		if ( text_head->line != NULL )
		{
			strcpy(line_ptr, text_head->line);
			while ( isspace( line_ptr[line_index] ) )
				line_index++;
		}
		else
		{
			line_ptr = NULL;
			line_index = 0;
		}
		if ( line_ptr && line_ptr[line_index] == '.' )
		{
			++line_index;
			if ( !strcmp( readWordFromMemory(&line_ptr), "ent" ) );
			else if ( !strcmp(readWordFromMemory(&line_ptr), "end") )
			{
				while ( line_ptr[line_index] != '\0' ) ++line_index;
				
				return;
			}
		}
		if ( line_ptr && isInstruction(&line_ptr) ) // check here if the instruction .end stop the progam . /**********************/
		{
			text_head = text_head->next;//text_head = text_head->next;    // define this function which return 0 if failed and 1 on success and has a ** arg saves the adress of that
			line_index = 0;
			continue;
		}
		else if(!text_head->next)
		{
			text_head = text_head->next;
			line_index = 0;
			
		}
		
	}

}
char *readWordFromFile ( FILE *file_ptr, char c , char *string)
{

	int index = 0;
	while ( c != ' ' && c != '\t' && c != ',' && c != ':' && c != '\n' )  
	{
		string[index++] = c;
		c = fgetc(file_ptr);
	}
	string[index] = NULL;
	while ( isspace(c) )
	{
		c = fgetc(file_ptr);
	}
	if ( c == ':' )
	{
		if ( text_head->label != NULL )
		{
			text_head->next = ( struct text *) malloc ( sizeof(struct text) );
			text_head = text_head->next;
			text_head->next = NULL;
			text_head->adress = NULL;
			text_head->label = NULL;
		}
		if ( text_head->label == NULL )     /* it can be deleted */
		{
			text_head->label = string;

			return string;
		}
	}

	return (string);
}


//edited : free added 
void move_to_memory(FILE *file_ptr)
{
	int index = 0;
	char c;
	char *string;
	char *tmp;
	//char *line;
	while ( isspace ( c = fgetc(file_ptr) ) );
	while ( c != EOF )
	{
tmp = (char *) malloc ( STRING_MAX * sizeof(char) );
		string = (char *) malloc( 20 * sizeof(char) );
		index = 0;
		while ( isspace(c) && c != EOF)
		{

			c = fgetc(file_ptr);
		}
		while ( c != ':' && c != '\n' )
		{
			if ( c == EOF ) return;
			string[index++] = c;
			c = fgetc(file_ptr);
		}
		string[index] = NULL;
		if ( c == ':' )
		{
			text_head->label = (char *) malloc ( STRING_MAX * sizeof(char) );
			strcpy(text_head->label, string);
			if ( strcmp ( string, "main" ) == 0 ) 
			{
				text_head->isMain = 1;
			}
		}
		else if ( c == '\n' )
		{
			if ( text_head->line == NULL )
			{
				text_head->line = (char *) malloc ( STRING_MAX * sizeof(char) );
				strcpy(text_head->line, string);
				if ( text_head->adress == NULL && text_head->label != NULL)
				{
					text_head->adress = ( struct text *) text_head;
					text_head->next = ( struct text *) malloc ( sizeof(struct text) );
					text_head = text_head->next;
					text_head->next = NULL;
					text_head->adress = NULL;
					text_head->label = NULL;
					text_head->line = NULL;
				}
				else
				{
					text_head->next = ( struct text *) malloc ( sizeof(struct text) );
					text_head = text_head->next;
					text_head->next = NULL;
					text_head->adress = NULL;
					text_head->label = NULL;
					text_head->line = NULL;
				}
			}
		}
		c = fgetc(file_ptr);

		free(tmp,sizeof(STRING_MAX * sizeof(char)));
		free(tmp,sizeof( 20 * sizeof(char) ));

	}

fclose("fib.text");
//puts("moved to memory");
}
