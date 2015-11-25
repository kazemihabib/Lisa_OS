// monitor.c -- Defines functions for writing to the monitor.
//             heavily based on Bran's kernel development tutorials,
//             but rewritten for JamesM's kernel tutorials.

#include "monitor.h"

#define BUFFSIZ 100*25*80
#define NO 0
#define YES 1
/*the first workstation variables */
u16int video_buffer[BUFFSIZ];

// The VGA framebuffer starts at 0xB8000.
u16int *video_memory = (u16int *)0xB8000;
// Stores the cursor position.
u8int cursor_x = 0;
u8int cursor_y = 0;

u8int buff_cursor_x=0;
u8int buff_cursor_y=0; 

static u8int finish_cursor=0;

//store the default colours
u8int dflt_backColour = 0;
u8int dflt_foreColour = 15;


/*end of first workstation variable*/

/*the second workstation variables*/



	u16int second_video_memory[25*80];
	u16int second_video_buffer[BUFFSIZ];
	u8int second_cursor_x ;
	u8int second_cursor_y ;

	u8int second_buff_cursor_x;
	u8int second_buff_cursor_y; 

	static u8int second_finish_cursor;

	u8int second_dflt_backColour;
	u8int second_dflt_foreColour;
	int second_ws_init=0;

/*end of second workstation variables*/


// Updates the hardware cursor.
static void move_cursor()
{
    //habib: this function just changes the cursor shape location on the screen.
    // The screen is 80 characters wide...
    u16int cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

static void scroll_buff()
{

    // Get a space character with the default colour attributes.
    u8int attributeByte = (dflt_backColour  << 4) | (dflt_foreColour & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(buff_cursor_y >=BUFFSIZ/80)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i <	BUFFSIZ-80; i++)
        {
            video_buffer[i] = video_buffer[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = BUFFSIZ-80; i < BUFFSIZ; i++)
        {
            video_buffer[i] = blank;
        }
        // The cursor should now be on the last line.
        buff_cursor_y=(BUFFSIZ/80)-1;
		finish_cursor=(BUFFSIZ/80)-1;
    }
	
}


// Scrolls the text on the screen up by one line.
static void scroll()
{

    // Get a space character with the default colour attributes.
    u8int attributeByte = (dflt_backColour  << 4) | (dflt_foreColour & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(cursor_y >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            video_memory[i] = blank;
        }
        // The cursor should now be on the last line.
        cursor_y = 24;
    }
}

/*this version of monitor_put support colour*/
void monitor_put_clr(char c, u8int backColour, u8int foreColour)
{
	//if(finish_cursor==buff_cursor_y)
	//{
		// The attribute byte is made up of two nibbles - the lower being the 
		// foreground colour, and the upper the background colour.
		u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
		// The attribute byte is the top 8 bits of the word we have to send to the
		// VGA board.
		u16int attribute = attributeByte << 8;
		u16int *location;

		// Handle a backspace, by moving the cursor back one space
		if (c == 0x08 && cursor_x)
		{
		    cursor_x--;
			buff_cursor_x--;
		}
		
		// Handle a tab by increasing the cursor's X, but only to a point
		// where it is divisible by 8.
		else if (c == 0x09)
		{
		    cursor_x = (cursor_x+8) & ~(8-1);
			buff_cursor_x=(buff_cursor_x+8) & ~(8-1);
		}

		// Handle carriage return
		else if (c == '\r')
		{
		    cursor_x = 0;
			buff_cursor_x=0;
		}


		// Handle newline by moving cursor back to left and increasing the row
		else if (c == '\n')
		{
		    cursor_x = 0;
		    cursor_y++;
			buff_cursor_x=0;
			buff_cursor_y++;

			finish_cursor++;
		}
		// Handle any other printable character.
		else if(c >= ' ')
		{
		    location = video_memory + (cursor_y*80 + cursor_x);
		    *location = c | attribute;
		    cursor_x++;

			location = video_buffer + (buff_cursor_y*80 + buff_cursor_x);
		    *location = c | attribute;
		    buff_cursor_x++;
		}

		// Check if we need to insert a new line because we have reached the end
		// of the screen.
		if (cursor_x >= 80)
		{
		    cursor_x = 0;
		    cursor_y ++;
	
			buff_cursor_x = 0;
		    buff_cursor_y ++;

			finish_cursor++;
		
		}

		// Scroll the screen if needed.
		scroll();
		//scroll the buffer if needed.
		scroll_buff();
		// Move the hardware cursor.
		move_cursor();
	//}
}

// Writes a single character out to the screen.
void monitor_put(char c)
{
	monitor_put_clr(c, dflt_backColour, dflt_foreColour);
}



void putch(char c) {
	monitor_put(c);
}

void putch_clr(u8int backColour, u8int foreColour,char c)
{
	monitor_put_clr(c, backColour, foreColour);
}

// Clears the video_buffer, by copying lots of spaces to the vedo_buffer.
void 	video_buff_clear()
{
    // Make an attribute byte for the default colours
    u8int attributeByte = (dflt_backColour << 4) | (dflt_foreColour & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 80*0; i < BUFFSIZ; i++)
    {
	     video_buffer[i] = blank;
    }

    buff_cursor_x = 0;
    buff_cursor_y = 0;
	
	finish_cursor=0;
}

// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
    // Make an attribute byte for the default colours
    u8int attributeByte = (dflt_backColour << 4) | (dflt_foreColour & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        video_memory[i] = blank;
    }
	
	video_buff_clear();

    // Move the hardware cursor back to the start.
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(char *c)
{
    int i = 0;
    while (c[i])
    {
        monitor_put(c[i++]);
    }
}

void monitor_write_hex(u32int n)
{
    s32int tmp;

    monitor_write("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            monitor_put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            monitor_put( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        monitor_put (tmp-0xA+'a');
    }
    else
    {
        monitor_put (tmp+'0');
    }

}

void monitor_write_dec(u32int n)
{

    if (n == 0)
    {
        monitor_put('0');
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    monitor_write(c2);

}
void chng_back_clr(u8int backColour)
{
	// Make an attribute byte for the default colours
	dflt_backColour =backColour;
	
    u8int attributeByte = (dflt_backColour << 4) | (0 & 0x0F);
    int i;
    for (i = 0; i < 80*25; i++)
    {
	/*just change the background part*/
        /*0xfff:0000 1111 11111111*/
	      /*back fore   ascii*/
	/*attributeByte << 8: ???? 0000 00000000*/
	video_memory[i] = (video_memory[i]& 0xFFF) | (attributeByte << 8);
    }
	
	//change the video_buff backColour
	 for (i = 0; i < BUFFSIZ; i++)
    {
	/*just change the background part*/
        /*0xfff:0000 1111 11111111*/
	      /*back fore   ascii*/
	/*attributeByte << 8: ???? 0000 00000000*/
	video_buffer[i] = (video_buffer[i]& 0xFFF) | (attributeByte << 8);
    }
		


}

void chng_fore_clr(u8int foreColour)
{
	dflt_foreColour=foreColour;
	// Make an attribute byte for the default colours
	
    u8int attributeByte = (0 /*black*/ << 4) | (foreColour/*black*/ & 0x0F);
    int i;
    for (i = 0; i < 80*25; i++)
    {
	/*just change the fore part*/
        /*0xF0FF:1111 0000 11111111*/
	      /*back  fore   ascii*/
	/*attributeByte << 8: 0000 ???? 00000000*/
	video_memory[i] = (video_memory[i]& 0xF0FF) | (attributeByte << 8);
    } 
    //change video buffer fore colour
    for (i = 0; i < BUFFSIZ; i++)
    {
	/*just change the fore part*/
        /*0xF0FF:1111 0000 11111111*/
	      /*back  fore   ascii*/
	/*attributeByte << 8: 0000 ???? 00000000*/
	video_buffer[i] = (video_buffer[i]& 0xF0FF) | (attributeByte << 8);
    }
}


void move_forward(void)
{
	cursor_x++;
	scroll();
	scroll_buff();
	move_cursor();
}

// Scrolls up the text on the screen up by one line.
void scroll_up()
{		/*for not confusing see this example*/
		/*0  1  2 
		  3  4  5
		  6  7  8
			
		  9  10 11 */
		u8int start_cursor;
		int i;
		int j;
		if(finish_cursor >=25  )
		{

			finish_cursor--;
			start_cursor=finish_cursor-24;  //export to screen starts from here.

				// Move the current text chunk that makes up the screen
				// back in the buffer by a line
				for (j=0*80,i =start_cursor*80;j<25*80, i < (finish_cursor+1)*80;j++, i++)
				{
				    video_memory[j] =video_buffer[i];
				}

				

			
		}
	
}


// Scrolls up the text on the screen down by one line.
void scroll_down()
{		/*for not confusing see this example*/
		/*0  1  2 
		  3  4  5
		  6  7  8
			
		  9  10 11 */
		u8int start_cursor;
		int i;
		int j;
		if(finish_cursor < buff_cursor_y  )
		{

			finish_cursor++;
			start_cursor=finish_cursor-24;  //export to screen starts from here.

				// Move the current text chunk that makes up the screen
				// back in the buffer by a line
				for (j=0*80,i =start_cursor*80;j<25*80, i < (finish_cursor+1)*80;j++, i++)
				{
				    video_memory[j] =video_buffer[i];
				}

				

			
		}
	
}

void reset_scroll()
{
	int up,down,i;
			if(finish_cursor < buff_cursor_y)
			{
				down=buff_cursor_y-finish_cursor;
				for(i=0;i<down;i++)
					scroll_down();
			}
}

void init_second_ws()
{
	
	int i;
	u8int attributeByte = (0 << 4) | (15 & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    for (i = 0; i < 80*25; i++)
    {
        second_video_memory[i] = blank;
    }

	for(i=0;i<BUFFSIZ;i++)
	{
		second_video_buffer[i]=blank;
	}

	second_cursor_x=0;
	second_cursor_y=0;

	second_buff_cursor_x=0;
	second_buff_cursor_y=0;

	second_finish_cursor=0;

	second_dflt_backColour=0;
	second_dflt_foreColour=15;
	second_ws_init=1;
}
void chng_ws()
{
	int i;
/*copy to temp*/
	if(!second_ws_init)
		init_second_ws();

	
	u16int temp_video_memory[25*80];
	u16int temp_video_buffer[BUFFSIZ];
	u8int temp_cursor_x =cursor_x;
	u8int temp_cursor_y =cursor_y;
	u8int temp_buff_cursor_x=buff_cursor_x;
	u8int temp_buff_cursor_y=buff_cursor_y;
	u8int temp_finish_cursor=finish_cursor;
	u8int temp_dflt_backColour=dflt_backColour;
	u8int temp_dflt_foreColour=dflt_foreColour;
	for(i=0;i<25*80;i++)
	{
		temp_video_memory[i]=video_memory[i];
	}
	
	for(i=0;i<BUFFSIZ;i++)
	{
		temp_video_buffer[i]=video_buffer[i];
	}

/*end copy to temp*/

//monitor_clear();
/*copy the second ws to main ws*/

for(i=0;i<25*80;i++)
	{
		video_memory[i]=second_video_memory[i];
	}

for(i=0;i<BUFFSIZ;i++)
	{
		video_buffer[i]=second_video_buffer[i];
	}

cursor_x = second_cursor_x;
cursor_y = second_cursor_y;

buff_cursor_x=second_buff_cursor_x;
buff_cursor_y=second_buff_cursor_y; 

finish_cursor=second_finish_cursor;

dflt_backColour = second_dflt_backColour;
dflt_foreColour = second_dflt_foreColour;
/*end of copy the second ws to main ws*/

/*copy temp to second ws*/

for(i=0;i<25*80;i++)
	{
		second_video_memory[i]=temp_video_memory[i];
	}

for(i=0;i<BUFFSIZ;i++)
	{
		second_video_buffer[i]=temp_video_buffer[i];
	}

second_cursor_x = temp_cursor_x;
second_cursor_y = temp_cursor_y;

second_buff_cursor_x=temp_buff_cursor_x;
second_buff_cursor_y=temp_buff_cursor_y; 

second_finish_cursor=temp_finish_cursor;

second_dflt_backColour = temp_dflt_backColour;
second_dflt_foreColour = temp_dflt_foreColour;
/*end of copy temp to second ws*/



}
	



