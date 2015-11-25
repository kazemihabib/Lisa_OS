#include "startmain.h"
#include "monitor.h"
#include "./rlibc/stdio.h"
#include "debug.h"
#include "./rlibc/loader.h"
#include "./rlibc/string.h"
#include "timer.h"
#define EXIT_SUCCESS 0
#define TRUE 1


int start_main()
{
char c;
/*welcom page*/
FILE *art;
art = fopen("lisaos.txt","r" );

			monitor_clear();
			c = fgetc(art);
			while ( c != EOF )
			{
				putch(c = ( fgetc(art)) );
			}
			fclose( art );
			delay(200);
			monitor_clear();

//end of welcom page
	shell();


}
