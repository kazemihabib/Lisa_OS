
#define size_t unsigned int
#ifndef NULL
#define NULL '\0'
#endif
//int strcmp(char *str1, char *str2);
int strcmp (const char *p1, const char *p2);

void* memcpy(void* dstp, void* const srcp, unsigned long size);

void* memccpy (void *dest, const void *src, int c, size_t n);

int strncmp (const char *s1, const char *s2, size_t n);

char* strcat (char *dest, const char *src);

/*char *stncat(char *dest, const char *src, size_t n);*/

char* strcpy (char *dest, const char *src);

size_t strlen ( const char * str );
