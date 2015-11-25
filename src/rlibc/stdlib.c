#include "ctype.h"
#include "stdlib.h"
#define DATA_SEG_SIZE  8388608 // 8megabyte for heap
char data_seg[DATA_SEG_SIZE];
char* heap_top = data_seg;
char* stack_top = data_seg + DATA_SEG_SIZE - 1;

//an structure to hold the free block of data
struct block_meta
{
	long size;
	struct block_meta *next;
	void* block_ptr;
}*first = NULL;


void deleteNode(struct block_meta *head, const struct block_meta *n);
void* findFree(int size);

int atoi (const char * str)
{
	/*convert asci to int*/
	int val = 0, sign = 1;
	while ( *str != '\0' )
	{
		if ( isspace(*str) ) ++str;
		if ( *str == '-' ) 
		{
				sign = -1 ;
				++str;
		}
		if ( isdigit(*str) )
		{
			val = val * 10 + (*(str++) - '0' );
		}
		else
			return val * sign ;
	}
	return val * sign ;
}
int itoa(int c, char *str)
{
	/*convert int to asci*/
	int rem, i,sign;//rem for remaining
	char *s = str;
	sign = 1;
	if(0==c)
	{
		*s++='0';
		*s='\0';
		return 0;
	}

	if (c<0)
	{
		c = -c;
		sign = -1;

	}

	while(c>0)
	{
		rem = c % 10;
		*s++ = rem + '0';
		c /= 10;
	}
	if (sign == -1)
		*s++ = '-';//add 'sign' at the end because of strrev
	*s = '\0';

	strrev(str);//reverse the array 
	return 0;
}

char *strrev(char *str)
{
	/*reverse an array*/
	int i, j, temp;
	for (i = 0; str[i] != '\0'; i++);//i=index(end of array)
	i--;//index begins from 0
	for (j = 0; j < i; j++, i--)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
	}
	return str;
}

double atof(char s[])
{
	/*convert ascii float numbers to float*/
	double val = 0;
	int i, power = 1, sign = 1;
	// skip whitespace
	for (i = 0; isspace(s[i]); ++i);
	//check for a sign
	if (s[i] == '-'){
		sign = -1;
		++i;
	}
	else if (s[i] == '+'){
		sign = 1;
		++i;
	}
	for (; isspace(s[i]); ++i);//skip whitespaces after sign

	// find the real part digits
	for (; isdigit(s[i]); ++i)
		val = val * 10 + (s[i] - '0');
	if (s[i] == '.')
		++i;
	// find after floating point value
	for (; isdigit(s[i]); ++i){
		power *= 10;
		val = val * 10 + (s[i] - '0');
	}
	val = (sign * val) / power;
	return val;
}
/*new version will develope soon:D the precision of this is version is low*/
void ftoa(double c, char s[],int flength)
{
	/*convert float number to ascii*/ 
	/*flength : the length of decimal part.*/

	int i_part, f_part_int;
	int i, length_i;
	double f_part;

	i_part = (int)c;				//take apart the integer part 
	f_part = c - (i_part);			//decimal part of the given number
	for (i = 0; i < flength; i++)
	{
		/*example: 0.563 ->5.63 ->56.3->563.0 */
		f_part *= 10;		
	}
	f_part_int = (int)f_part;	//cast f_part to long type.
	length_i = i_len(i_part);	//length of integer part
	itoa(i_part, s);			//convert ineger part to array.
	s[length_i] = '.';			//add . to arry.
	itoa(f_part_int, s + length_i+1);	//convert float part to a and concatenate it with integer part
}

int i_len(int c)
{
	/*calculate the the number the length an integer number */
	int i = 0;
	if(0==c)
	{
		return 1;
	}
	while (c != 0)
	{
		i++;
		c /= 10;
	}
	
	return i;
}


//search for a free sport fit the requested size in the freespot linked list
void* findFree(int size)
{
//printf("requested size is : %d\n", size);

	struct block_meta * head = first;
	struct block_meta * current;
	while ( head != NULL )
	{
//printf("is the same : %d, %d\n", size, head->size);
		if ( head->size == size )
		{

//printf("%d Granted\n", size);
			current = head;
			head = first;
			deleteNode(head, current);
			return current->block_ptr;
		}
		else
			head = head->next;
	}
	return NULL;
}

//release memory
void free(void* ptr, int size)
{
	struct block_meta * head = first;
//printf("%d is free now \n", size);
	if(head == NULL)
	{
		first = (struct block_meta *) malloc(sizeof(struct block_meta));
		head = first;
	}
	else if(head->next == NULL)
	{
		head->next = (struct block_meta *) malloc(sizeof(struct block_meta));
		head = head->next;
	}
	head->size = size;
//printf("head->size : %d\n", size);
	head->block_ptr = ptr;
	head->next = NULL;
}


//my_malloc function
void* malloc(int size) 
{
//printf("%d is requested\n", size);
	if ( findFree(size) )
		return findFree(size);
	else if ( heap_top >= stack_top )
		return NULL;
//printf("%d is allocated\n", size);
	heap_top += (size);
	return (heap_top - (size));
}

void deleteNode(struct block_meta *head, const struct block_meta *n)
{
	struct block_meta * prev = head;
    // When node to be deleted is head(first) node
    if(head == n)
    {
        if(head->next == NULL)
        {
            first = NULL;
            return;
        }
	first = head->next;
	free(head, sizeof(struct block_meta));
 
        /* Copy the data of next node to head */
//        head->size = head->next->size;
 
        // store address of next node
  //      n = head->next;
 
        // Remove the link of next node
//        head->next = head->next->next;
 
        return;
    }
 
 
    // When not first node, follow the normal deletion process
 
    // find the previous node
    while(prev->next != NULL && prev->next != n)
        prev = prev->next;
 
    // Check if node really exists in Linked List
    if(prev->next == NULL)
    {
        //printf("\n Given node is not present in Linked List");
        return;
    }
 
    // Remove node from Linked List
    prev->next = prev->next->next;
    free(head->next, sizeof(struct block_meta));
    return; 
}


