
#ifndef registers.h
#include "registers.h"
#endif
#ifndef string.h
#include "string.h"
#endif
#ifndef stdlib.h
#include "stdlib.h"
#endif
#ifndef ctype.h
#include "ctype.h"
#endif
#ifndef stdio.h
#include "stdio.h"
#endif

int registers[34] = {0};            //mips cpu registers   ---> 33 and 32 for hi and lo

/* it will return 1 on succeed and 0 if failed */ /******************************/
int regManager(char regName[], int registerVal)
{
	int registerNumber = registerNames( regName );
	registers[registerNumber] = registerVal;
	return 1;
}


int registerNames ( char *regName )
{
	if ( strcmp(regName,"lo" ) == 0 )
		return 32;
	else if (strcmp(regName, "hi") == 0)
		return 33;

	++regName;
	if ( isalphnum(regName) )     // check this pointer out
	{
		
		if ( regName[0] == 't' )
		{
			switch (regName[1])
			{
			case '0' : return 8;
			case '1' : return 9;
			case '2' : return 10;
			case '3' : return 11;
			case '4' : return 12;
			case '5' : return 13;
			case '6' : return 14;
			case '7' : return 15;
			case '8' : return 24;
			case '9' : return 25;
			default:
				break;
			}
		}

		else if ( regName[0] == 'a' )
		{
			switch (regName[1])
			{
			case '0' : return 4;
			case '1' : return 5;
			case '2' : return 6;
			case '3' : return 7;
			default:
				break;
			}
		}
		else if ( regName[0] == 'v' )
		{
			switch (regName[1])
			{
			case '0' : return 2;
			case '1' : return 3;
			default:
				break;
			}
		}

		else if ( regName[0] == 's' )
		{
			switch (regName[1])
			{
			case '0' : return 16;
			case '1' : return 17;
			case '2' : return 18;
			case '3' : return 19;
			case '4' : return 20;
			case '5' : return 21;
			case '6' : return 22;
			case '7' : return 23;
			default :
				break;
			}
		}
		else if ( regName[0] == 'k' )
		{
			switch (regName[1])
			{
			case '0' : return 26;
			case '1' : return 27;
			default:
				break;
			}
		}
	}
	else if ( strcmp(regName, "gp") == 0 )
	{
		return 28;
	}
	else if ( strcmp(regName, "sp") == 0 )
	{
		return 29;
	}
	else if ( strcmp(regName, "fp") == 0 )
	{
		return 30;
	}
	else if ( strcmp(regName, "ra") == 0 )
	{
		return 31;
	}
	else
	{
		return atoi(regName);
	}
}
