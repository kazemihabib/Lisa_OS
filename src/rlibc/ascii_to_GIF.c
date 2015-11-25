#include "stdio.h"
#define True 1
#define MAX_ART 25
#include "./../keyboard.h"
/*
void delay(void)
{
	int c = 1, d = 1;
 
	for ( c = 1 ; c <= 5555 ; c++ )
		for ( d = 1 ; d <= 999 ; d++ )
		{}
}
*/

void show_welcome_message_GIF(void)
{
	printf("Welcome To GIF Simulator\n\nwith this tiny app you will be able to create interesting gif-like arts\nthis app will support up to 25 ascii-files for now\nupgrades In future ^_^\n");
}

void GIF_simulator(void)
{
	show_welcome_message_GIF();
	int num, tmp, i, art_counter = 0;
	char c;
	char *file_names[MAX_ART];
	FILE *art;
	while (True)
	{
		printf( "How many ascii-art would you like to add ? " );
		scanf( "%d", &num );
		if ( num > MAX_ART ){ printf ( "your entered number is too big\n" ); goto try_again; }
		tmp = num;
		printf( "Please Enter your ART file names adresses:\n" );
		for ( i = 0; i < num; scanf("%s", file_names[i]), ++i );
		while ( True )
		{
			if ( kbhit() )
			{
				getch();
				goto try_again;
			}
			if ( art_counter++ == num ) art_counter = 0;
			art = fopen( file_names[art_counter], "r" );
			delay(7);
			monitor_clear();
			c = fgetc(art);
			while ( c != EOF )
			{
				if ( kbhit() )
				{
					getch();
					goto try_again;
				}
				putch(c = ( fgetc(art)) );
			}
			fclose( art );
		}
		try_again:
		art_counter = 0;
		printf( "would you like to try again(Y/N): " );
		scanf( "%c", &c );
		if ( c == 'Y' || c == 'y' ) continue;
		else if ( c == 'N' || c == 'n' ) return;
	}
}
