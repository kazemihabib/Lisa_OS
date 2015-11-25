#include "./rlibc/stdio.h"
#include "./rlibc/stdlib.h"
#include "./rlibc/string.h"
#include "./rlibc/ctype.h"
#include "./rlibc/ctype.h"
#include "./rlibc/ascii_to_GIF.h"
#include "debug.h"
#include "monitor.h"
#include "keyboard.h"


typedef struct node{
	char  data[1000];
	struct node *next;
} NODE;

int shell_input(char *str);
void shell();
char **tokenize(char *str,int *size);
char **insert_vector(char **head, int *size, char *str);
char ** initialize_vector( int *argv_len,char *str);
void chng_color(int arglen,char **argv);
void reset_clr();
void roll();
void cls();
void run_mips(int arglen,char **argv);
void color_help();
void ls();
void help();
void clear_my_input(int char_counter);
void remove_end_spaces(char *str);
u8int dflt_foreColour;
u8int dflt_backColour;



/*linked list*/





void print(NODE * head);
void freelinklist(NODE *head);
NODE * get(NODE * head, int index);
NODE * add_head(NODE * head, char * item);
NODE *get_new_node(char * item);



