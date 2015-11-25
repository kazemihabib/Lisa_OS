#include "string.h"
//ajdari
#include "stdio.h"



char* strcat (char *dest, const char *src)
{
  strcpy (dest + strlen (dest), src);
  return dest;
}

/*char *strncat(char *dest, const char *src, size_t n)
{
	strncpy(dest + strlen(dest), src, n);
	*(dest + strlen(dest)) = '\0';
	return dest;
}*/

char* strcpy (char *dest, const char *src)
{
  return memcpy (dest, src, strlen (src) + 1);
}

size_t strlen ( const char * str )
{
	size_t len = 0;
	while ( *(str++) != '\0' ) ++len;
	return len;
}
/*
int strcmp(char *str1, char *str2)
{
//to be removed
printf("in strcmp");
      int i = 0;
      int failed = 0;
      while(str1[i] != '\0' && str2[i] != '\0')
      {
          if(str1[i] != str2[i])
          {
              failed = 1;
              break;
          }
          i++;
      }
      // why did the loop exit?
      if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
          failed = 1;
//to be removed
	printf("\tthe strcmp result : %d\n", failed);
      return failed;
}

*/
int strcmp (const char *p1, const char *p2)
{
//printf("%s, %s\n", p1, p2);
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;
  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
	return c1 - c2;
    }
  while (c1 == c2);
  return c1 - c2;
}




void* memcpy(void* dstp, void* const srcp, unsigned long size)
{
	 
	char* dstpp = (char*) dstp;
	char* srcpp = (char*) srcp;
	while ( size != -1 )
	{
		*(dstpp++) = *(srcpp++);
		--size;
	}
	return dstp;
}




void* memccpy (void *dest, const void *src, int c, size_t n)
{
  const char *s = src;
  char *d = dest;
  const char x = c;
  size_t i = n;

  while (i --> 0)
    if ((*d++ = *s++) == x)
      return d;

  return NULL;
}



int strncmp (const char *s1, const char *s2, size_t n)
{
  unsigned char c1 = '\0';
  unsigned char c2 = '\0';

  if (n >= 4)
    {
      size_t n4 = n >> 2;
      do
	{
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\0' || c1 != c2)
	    return c1 - c2;
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\0' || c1 != c2)
	    return c1 - c2;
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\0' || c1 != c2)
	    return c1 - c2;
	  c1 = (unsigned char) *s1++;
	  c2 = (unsigned char) *s2++;
	  if (c1 == '\0' || c1 != c2)
	    return c1 - c2;
	} while (--n4 > 0);
      n &= 3;
    }

  while (n > 0)
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0' || c1 != c2)
	return c1 - c2;
      n--;
    }

  return c1 - c2;
}
