#include "common.h"

/********************************
*
* Just something to work for now
*
*********************************/
static u32int heap[1000];
void * allocp = &heap;

u32int kmalloc(u32int sz)
{
	u32int * addr = (u32int *) allocp;
	allocp += sz;
    return (u32int) addr;
}

