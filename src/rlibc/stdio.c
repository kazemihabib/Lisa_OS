#include "stdio.h"
#include "./../fs.h"
/*
* Written by Ahmad Siavashi(a.siavosh@yahoo.com), March 2015.
* All functions need enhancements; Current dummy versions help you start your work.
*/

/*copied from stdi.h*/
#include "stdlib.h"
#include "ctype.h"
#include "./../common.h"
/********************************************/
#include "string.h"
/*end of stdi.h */
// Currently 5 files can be opened simultaneously. Change MAX_OPEN_FILES in the header for more concurrency(if needed).
static FILE open_files[MAX_OPEN_FILES];
static int open_files_idx = 0;

extern u8int dflt_backColour;//declared in monitor.c
extern u8int dflt_foreColour;//declared in monitor.c

/* buffer for storing the getchar and ... inputs */
#define BUFSIZ 4096
char buffer[BUFSIZ] = {0};
static int End_index = 0, buffer_index = 0;

// Only read mode for now.
FILE * fopen(const char * filename, const char * mode)
{
	if(!strcmp(mode, "r"))
	{
		int i = 0;
		struct dirent *node = 0;
		while ( (node = readdir_fs(fs_root, i)) != 0)
		{
		    fs_node_t *fsnode = finddir_fs(fs_root, node->name);
			// If file.
		    if ((fsnode->flags&0x7) != FS_DIRECTORY)
		    {
		    	// If matched.
		    	if(!strcmp(filename, fsnode->name))
		    	{
		    		if(open_files_idx < MAX_OPEN_FILES)
		    		{
						open_files[open_files_idx].file = fsnode;
						open_files[open_files_idx].pos_indicator = 0;
						open_files[open_files_idx].err_indicator = 0;
						open_files[open_files_idx].eof_indicator = 0;
						// Return the file.
				    	return &open_files[open_files_idx++];
				    }
				    else
				    {
				    	return NULL;
				    }
		        }
		    }
		    i++;
		}
	}
    // Not found.
	return NULL;
}

// Something simple to work for now. Opening and Closing must be done in a LIFO way.
int fclose(FILE * stream)
{
	if(stream)
	{
		close_fs(stream->file);
		--open_files_idx;
		// On Success.
		return 0;
	}
	// On Failure.
	return EOF;
}

int fgetc(FILE * stream)
{
	int character;
	u32int sz = read_fs(stream->file, stream->pos_indicator, 1, (u8int *) &character);
	if(sz)
	{
		stream->pos_indicator++;
		/* To be implemented later. 
		  Set Stream Error Indicator
		   Set Stream EOF Indicator
		/***************************/
		return character;
	}
	// On Failure.
	return EOF;
}

long int ftell(FILE * stream)
{
	if(stream)
	{
		return stream->pos_indicator;
	}
	return -1L;
}

void rewind(FILE * stream)
{
	if(stream)
	{
		stream->pos_indicator = 0;
		stream->err_indicator = 0;
		stream->eof_indicator = 0;
	}
}


/*our functions for stdio.h*/

/* getting character input from the user */
int getchar(void)
{
	
	char c;
/* check if the buffer is empty */
	if ( End_index == 0 )
	{
		while ( (c = getch()) != '\n' && End_index < BUFSIZ) 
		{
			if(c)
			{
				if ( c == '\b' && End_index > 0 )
				{
					--End_index;
					putchar('\b');
					putchar(' ');
					putchar('\b');
					//putchar(End_index - 48);
				}
				else if(c!='\b')
				{
					putchar(c);
					buffer[End_index++] = c;
				}
			}
		}
		putchar('\n');
		
	}
/* check its in the end of the buffer */
	if ( buffer_index >= End_index )
	{
		buffer_index = 0;
		End_index = 0;
		return '\n';
	}
/* check if there is still things to read in the buffer */
	if ( End_index >= 0 && buffer_index < End_index )
	{
		return buffer[buffer_index++];
	}
	
}



/* flushing the buffer */
void fflush(void)
{    
	End_index = buffer_index = 0;  

//while ( getchar() != '\n' );
}



/* put a single character on the screen */
int putchar ( int ch )
{
	ch = (int)(unsigned char) ch;
	putch(ch);
	return ch;
}

/* put a single character on the screen support for colour */
int putchar_clr ( u8int backColour, u8int foreColour,int ch )
{
	ch = (int)(unsigned char) ch;
	putch_clr(backColour,foreColour,ch);
	return ch;
}


/* print's a string on the screen */
int puts ( const char * str )
{
	int i = 0;
	while ( (*str) != '\0' )
	{
		putchar(*(str++));
		++i;
	}
	putchar('\n');
	return i;
}


int putlong(long n, int width,u8int backColour, u8int foreColour)
{
	/*print integer and long values*/
	int lonretval;
	int i = 0;
	//char *str = (char *)malloc((i_len(n) + 1)*sizeof(char));
	char str[50];
	lonretval = i_len(n);
	lonretval += putwidth(width - i_len(n),backColour,foreColour);
	itoa(n, str);
	putstring(str, 0,backColour,foreColour);
	//free(str, i_len(n));
	return lonretval;
}

int putstring(const char *str, int width,u8int backColour, u8int foreColour)
{
	/*print string*/
	int i;
	int strreturn;
	strreturn = strlen(str);
	strreturn += putwidth(width - strlen(str),backColour,foreColour);
	for (i = 0; *str != 0; i++)
	{
		putchar_clr(backColour,foreColour,*str++);
	}

	return strreturn;
}

int putcharc(int c,int width,u8int backColour, u8int foreColour)
{

	int putcharcret = 1;
	putcharcret+= putwidth(width-1,backColour,foreColour);
	putchar_clr(backColour,foreColour,c);
	return putcharcret;
}


int putdouble(double dval, int precision, int width,u8int backColour, u8int foreColour)
{
	/*print double values*/
	int nextdig = 0;
	int pdreturn = precision;
	long long_part = (long)dval;
	pdreturn += i_len(long_part) + putwidth(width - (i_len(long_part) + precision + 1),backColour,foreColour) + 1; //+1 is for '.' in float numbe putwidth just return the length of blanck spaces
	putlong(long_part, 0,backColour,foreColour);
	dval = dval - long_part;
	putchar_clr(backColour,foreColour,'.');
	for (; precision > 0; precision--)
	{
		dval = (dval - nextdig) * 10;
		nextdig = (int)(dval);
		putlong(nextdig, 0,backColour,foreColour);
	}
	return (pdreturn);

}

int putwidth(int widlen,u8int backColour, u8int foreColour)
{
	int i;
	int ptwidret;
	for (i = 0; i < widlen; i++)
	{
		putchar_clr(backColour,foreColour,' ');
	}
	ptwidret = (widlen>0) ? widlen : 0;
	return ptwidret;
}


int scanf(const char *format, ...)
{
	int *argptr = (int*)&format + 1;
	char *frmptr = format;
	for (; *frmptr != '\0'; frmptr++)
	{
		if (*frmptr == '%')
		{
			++frmptr;
			scanfbuff(frmptr, *argptr++);

		}
	}
	return 0;
}

int scanfbuff(const char *frmptr, int *argptr)
{


	int c;
	int i = 0;

	int tempbuffread;		//temp for store the location of reading head(buffer_index )

	int int_value = 0;       //variable for convert ascii data in buffer to int
	char doublestr[50];       //array to copy the the double part of buffer in it
	char floatstr[50];       //array to copy the the float part of buffer in it


	int *int_var = argptr;  //pointer to the variable we should store the int values
	char *char_var = argptr; //pointer to the variable we should store the char values
	double *double_var = argptr;	//pointer to variable we should store the double data
	float *float_var = argptr;	//pointer to variable we should store the float data
	
	if (0 == End_index)
	{
	
		getchar();
		/*getchar returns and increments the buffer_index so we decrement it again*/
		buffer_index--;
	}
	

	//increment the buffer_index  to jump from spaces.
	while (isspace(buffer[buffer_index ]))
		buffer_index ++;

	switch (*frmptr)
	{
	case 'd':
		/*convert the int part of buff to int*/
		while (isdigit(buffer[buffer_index ]))
		{
			int_value *= 10;
			int_value += (buffer[buffer_index ++] - '0');
		}
		*int_var = int_value;
		
		break;

	case 'c':
		/*export the char part of buff*/
		*char_var = buffer[buffer_index ++];//store the char val of buffer in it's variable.
		
		break;

	case 'l':
		frmptr++;
		if (*frmptr == 'f')
		{
			tempbuffread = buffer_index ;
			while (isdigit(buffer[buffer_index ]) || '.' == buffer[buffer_index ])
			{
				doublestr[i++] = buffer[buffer_index ];
				buffer_index ++;
			}
			doublestr[i] = '\0';
			*double_var = atof(doublestr);
			i = 0;
			
		}
		break;
	case 'f':
			tempbuffread = buffer_index ;
			while (isdigit(buffer[buffer_index ]) || '.' == buffer[buffer_index ])
			{
				floatstr [i++] = buffer[buffer_index ];
				buffer_index ++;
			}
			floatstr[i] = '\0';
			*float_var = atof(floatstr);
		break;
	case 's':
		/*export the string part of buff*/
		while (!isspace(buffer[buffer_index ]) && buffer[buffer_index ] != 0)
		{
			*char_var++ = buffer[buffer_index ++];
		}
		

		*char_var = '\0';
		break;
	default:
		break;
	}


	if (buffer_index  >= End_index)
	{
		buffer_index  = 0;
		End_index = 0;
	}
	return 0;
}




int my_printf(u8int backColour, u8int foreColour,const char *format,void *argptr, ...)
{
	//void *argptr = (int*)&format + 1;
	int prtrtnval = 0;//print return value
	int width = 0;
	int precesion = 0;
	int prec;
	//argptr = (int*)argptr + 1;
	char *frmptr = format;
	for (; *frmptr != '\0'; frmptr++)
	{
		if (*frmptr == '%')
		{
			++frmptr;

			while (isdigit(*frmptr))
			{
				width *= 10;
				width += (*frmptr - '0');//width of the printable value
				frmptr++;
			}
			if (*frmptr == '.')
			{
				frmptr++;

				while (isdigit(*frmptr))
				{
					precesion *= 10;
					precesion += (*frmptr - '0');//precision of the double value
					frmptr++;
				}

			}
			switch (*frmptr)
			{
			case 'd':
				prtrtnval += putlong(*(int*)argptr, width,backColour,foreColour);
				argptr = ((int*)argptr + 1);
				width = 0;
				break;
			case 'c':
				prtrtnval+= putcharc(*(char*)argptr, width,backColour,foreColour);
				argptr = ((int*)argptr + 1);
				width = 0;
				break;

			case 's':
				prtrtnval += putstring(*(int*)argptr, width,backColour,foreColour);
				argptr = ((int*)argptr + 1);
				width = 0;
				break;

			case 'f':
				prec = (precesion > 0) ? precesion : 6;
				prtrtnval += putdouble(*(double*)argptr, prec, width,backColour,foreColour);
				argptr = ((double*)argptr + 1);
				width = 0;
				precesion = 0;
				break;

			default:
				putchar(*frmptr);
				break;
			}

		}
		else
		{
			putchar_clr(backColour,foreColour,*frmptr);
			prtrtnval++;
		}
	}

	return prtrtnval;//print return value

}

int printf(const char *format, ...)
{
	void *argptr = (int*)&format + 1;
	return my_printf(dflt_backColour,dflt_foreColour,format,argptr);
}


int printf_clr(u8int backColour, u8int foreColour,const char *format, ...)
{

	void *argptr = (int*)&format + 1;
	return my_printf(backColour,foreColour,format,argptr);
}


