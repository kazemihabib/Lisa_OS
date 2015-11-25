#include "stdio.h"
#undef NULL
#include "stdlib.h"
#undef NULL
#include "string.h"
#undef NULL
#include "GUI.h"
#define NULL 0
unsigned char *VGB = (unsigned char *)0xA0000000L;

typedef struct tagRECT
{
    long x1;
    long y1;
    long x2;
    long y2;
} RECT;

void init_dbl_buffer(void)
{
    dbl_buffer = (unsigned char *) malloc (640 * 480);
    if (dbl_buffer == NULL)
    {
	printf("Not enough memory for double buffer.\n");
	getchar();
	/*exit(1);*/
	return;
    }
}

void update_screen(void)
{
    #ifdef VERTICAL_RETRACE
      while ((inportb(0x3DA) & 0x08));
      while (!(inportb(0x3DA) & 0x08));
    #endif
    memcpy(VGB, dbl_buffer, (unsigned int)(640 * 480));
}

void setpixel (BITMAP *bmp, int x, int y, unsigned char color)
{
    bmp->data[y * bmp->width + x];
}

/* Draws a filled in rectangle IN A BITMAP. To fill a full bitmap call as
drawrect (&bmp, 0, 0, bmp.width, bmp.height, color); */
void drawrect(BITMAP *bmp, unsigned short x, unsigned short y,
                     unsigned short x2, unsigned short y2,
                     unsigned char color)
{
    unsigned short tx, ty, screen_offset = 1, bitmap_offset = 1;
	for (ty = y; ty < bmp->height; ty++)
    {
	memcpy(&dbl_buffer[screen_offset], &bmp->data[bitmap_offset], bmp->width);

	bitmap_offset += bmp->width;
	screen_offset += 640;
    }
}

