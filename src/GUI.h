typedef struct tagBITMAP              /* the structure for a bitmap. */
{
    unsigned int width;
    unsigned int height;
    unsigned char *data;
} BITMAP;
BITMAP BITMAP1;
void init_dbl_buffer(void);
void update_screen(void);
void setpixel (BITMAP *bmp, int x, int y, unsigned char color);
void drawrect(BITMAP *bmp, unsigned short x, unsigned short y,
                     unsigned short x2, unsigned short y2,
                     unsigned char color);
unsigned char *dbl_buffer;

