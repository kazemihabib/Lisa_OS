#include "keyboard.h"


unsigned char kbdus[128] =
{
   0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    130,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    131,	/* Left Arrow */
    0,
    132,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    133,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    asm volatile("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}


char kbhit()
{
    unsigned char scancode;
    unsigned char zbuf;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

     //clear buffer
    if(scancode != 0) {
	zbuf = inportb(0x64);
    }

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else if(scancode != 0)
    {
        return kbdus[scancode];
    }

    return 0;
}



char getch()
{
    unsigned char scancode;
    unsigned char zbuf;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    // clear buffer
    if(scancode != 0) {
	zbuf = inportb(0x64);
        while(!(zbuf & 1 ))
	    zbuf = inportb(0x64);
    }

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else if(scancode != 0)
    {
        return kbdus[scancode];
    }

    return 0;
}




