#ifndef STDIO_H
#define STDIO_H
#include "./../common.h"
#include "./../fs.h"

#define EOF -1
#define NULL 0

#define MAX_OPEN_FILES 5

typedef int word;  
#define STRING_MAX 509

typedef unsigned char byte;

typedef struct
{
	fs_node_t * file;
	long pos_indicator;
	int err_indicator;
	int eof_indicator;
} FILE;


FILE * fopen(const char * filename, const char * mode);
int fclose(FILE * stream);
long int ftell(FILE * stream);
void rewind(FILE * stream);
int getchar(void);

void fflush(void);

int putchar ( int ch );

int puts ( const char * str );

int putchar_clr ( u8int backColour, u8int foreColour,int ch );

int scanf(const char *format, ...);

int scanfbuff(const char *frmptr, int *argptr);

int i_len(int n);

int putlong(long n, int width,u8int backColour, u8int foreColour);

int putstring(const char *str, int width,u8int backColour, u8int foreColour);

int putcharc(int c,int width,u8int backColour, u8int foreColour);

int putdouble(double dval, int precision, int width,u8int backColour, u8int foreColour);

int putwidth(int widlen,u8int backColour, u8int foreColour);

int my_printf(u8int backColour, u8int foreColour,const char *format,void *argptr, ...);

int printf(const char *format, ...);

int printf_clr(u8int backColour, u8int foreColour,const char *format, ...);



#endif
