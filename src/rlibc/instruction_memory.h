#ifndef stdio.h
#include "stdio.h"
#endif
char *asciiz( FILE *file_ptr );
void jal ( char *function );
int bne( char *adress1, char *adress2, char *dest );
int j(char *dest);
void sw(char*dest, char *data);
void lw(char *dest, char *data);
void slt(char *dest, int reg1,int reg2);
void addu(char *dest, int reg1,int reg2);
void la(char *reg, char *param);
