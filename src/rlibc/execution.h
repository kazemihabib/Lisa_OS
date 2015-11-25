#ifndef stdio.h
#include "stdio.h"
#endif



void comment ( FILE *file_ptr );
int isInstruction( char **strpp );
int execInst( const char *struc, const char *args );
char *readWordFromMemory ( char **strpp );
