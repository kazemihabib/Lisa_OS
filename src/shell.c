#include "shell.h"

NODE * input_history=NULL;

void shell()
{
	char str[100], count, **argv;
	int i, arglen;
	//argv = (char **)malloc(sizeof(char *)* 1);
	count = 0;

	while (1)
	{
		char c;
		arglen = 0;
		argv = NULL;
		printf("user@LISA >> ");
		count = shell_input(str);
		if (count)
		{
			argv=tokenize(str,&arglen);
				
			if (argv == NULL)
				{
				//printf("argv = nuLL\n");
				continue;
				}

			/*change for and back color*/
			if(!strcmp(argv[0],"color"))
			{
				//printf("strcmp(argv[0],color)\n");
				chng_color(arglen,argv);
			}
			/*scrolling the page*/
			else if(!strcmp(argv[0],"roll"))
			{
				roll();
			}
			
			else if(!strcmp(argv[0],"cls"))
			{
				monitor_clear();
			}
			else if(!strcmp(argv[0],"mips"))
			{
				run_mips(arglen,argv);
			}
			else if(!strcmp(argv[0],"about"))
			{
				printf("LISA OS v0.001\n");
				printf("mohammad.siav@hotmail.com\nhabibkazemi@outlook.com\n");
			}
			else if(!strcmp(argv[0],"ls"))
				ls();
			else if(!strcmp(argv[0],"help"))
				help();
			else if(!strcmp(argv[0],"ws"))
				chng_ws();
			else if(!strcmp(argv[0],"gif"))
				GIF_simulator(); //in ascii_to_GIF.c
			/*The command is not recognized*/
			else 
			{
				printf("%s is not recognized as a command.\n",str);
			}
			

		}
		if (argv != NULL)
			{
			//printf("argv !=NULL\n");
			//free(argv,arglen*sizeof(char *)+1);
			}
	}	
}

void help()
{
	printf("color\t\t\tChange background and foreground color.\n");
	printf("ls   \t\t\tDisplay the files in the directory.\n");	
	printf("cls  \t\t\tClear screen.\n");
	printf("about\t\t\tAbout.\n");
	printf("roll \t\t\tScrolling the page.\n");
}
void ls()
{
	fs_dump(0);
}
void chng_color(int arglen,char **argv)
{
	int fore_clr,back_clr;

	if(arglen==1)
	{
		reset_clr();
	}
	else if(arglen==2)
	{
		if(!strcmp(argv[1],"help"))
			color_help();
		else
			{
			//just change the fore color
			fore_clr=atoi(argv[1]);
			if(fore_clr>15 || fore_clr<0 ||!isdigit(*argv[1]))
				color_help();
			else
				chng_fore_clr(fore_clr);
			if(dflt_foreColour==dflt_backColour)
				reset_clr();
			}		
	}
   else if(arglen==3)
   {
			fore_clr=atoi(argv[1]);
			back_clr=atoi(argv[2]);
			if(fore_clr>15 || fore_clr<0 || back_clr>15 || back_clr<0 || !isdigit(*argv[1]) || !isdigit(*argv[2]))
				color_help();
			else
			{
				chng_fore_clr(fore_clr);
				chng_back_clr(back_clr);
			}
			if(dflt_foreColour==dflt_backColour)
				reset_clr();
	}
	
	else 
		color_help();
}
/*0:black, 1:blue, 2:green, 3:cyan, 4:red, 5:magenta, 6:brown, 7:light grey, 8:dark grey, 9:light blue, 10:light green, 11:light cyan, 12:light red, 13:light magneta, 14: light brown, 15: white. */
void color_help()
{	
	printf_clr(4,15,"----------------------------------------------------\n\n");
	printf("color command help:\n");
	printf("color [fore color] [back color]\n");
	printf("color ---->reset to default colors\n");
	printf_clr(1,15,"----------------------------------------------------\n\n");
	printf_clr(0,15,"0:black ");
	printf_clr(1,15,"1:blue ");
	printf_clr(2,15,"2:green ");
	printf_clr(3,15,"3:cycan ");
	printf_clr(4,15,"4:red ");
	printf_clr(5,15,"5:magenta ");
	printf_clr(6,15,"6:brown ");
	printf_clr(7,15,"7:light grey ");
	printf_clr(8,15,"8:dark grey ");
	printf_clr(9,15,"9:light blue ");
	printf_clr(10,15,"10:light green ");
	printf_clr(11,15,"11:light cyvan ");
	printf_clr(12,15,"12:light red ");
	printf_clr(13,15,"13:light magenta ");
	printf_clr(14,0,"14:light brown ");
	printf_clr(15,0,"15:white\n");
	//printf("0:black, 1:blue, 2:green, 3:cyan, 4:red, 5:magenta, 6:brown, 7:light grey, 8:dark grey, 9:light blue, 10:light green, 11:light 		cyan, 12:light red, 13:light magneta, 14: light brown, 15: white.\n");
}
	
void reset_clr()
{
	chng_fore_clr(15/*white*/);
	chng_back_clr(0/*black*/);
}
	
void roll()
{
	char command;
	int scrolled,i;
	scrolled=0;
	printf("k->up and j->down and q->quit\n");
	while((command=getch())!='q')
	{

		if(command=='k')
			{
				scroll_up();
				scrolled++;
			}
		if(command=='j')
			{			
				scroll_down();
				scrolled--;
			}
	}	
	reset_scroll();
	
}

void run_mips(int arglen,char **argv)
{
	if(arglen==1)
	{
		printf("too few arguments!\n");
	}
	else if(arglen>2)
		printf("too many arguments!\n");
	else 
		loader(argv[1]);

}
/*Gets input for using in shell*/
/*Enter is delimeter*/
/*return : length of input*/
int shell_input(char *str)
{
	NODE *hist_node;
	char temp[1000];
	unsigned char  c;//because arrow keys value are ecceeds char type
	int char_counter,get_from_hist;
	get_from_hist=char_counter=0;//char_counter for copy to str and printed_lenght to prevent deleting others printed data.


	while((c=getch())!='\n')
	{
		if(!c)//c is 0
			continue;
		if ( c == '\b')
		{	//just remove one char so I didn't use this function:clear_my_input(char_counter)
			if(char_counter)
			{
			
				putchar('\b');
				putchar(' ');
				putchar('\b');
				char_counter--;
			}
		}
		else if(c<129)
		{
			//c is ascii 
			putchar(c);
			str[char_counter++] = c;	
		
		}
		else
		{
			//c is arrow key value
			switch(c)
			{	
				case 130:
					//up key pressed
					if(get_from_hist==0)
					{
						//store the command that I  entered
						str[char_counter]=0;
						strcpy(temp,str);
					}

					hist_node=get(input_history,get_from_hist);

					if(hist_node)
					{
						//check his_node not is not null

						clear_my_input(char_counter);
						strcpy(str,hist_node->data);
						get_from_hist++;
						char_counter=strlen(str);
						printf("%s",str);
					}
					break;
				case 131:
				
		       	 	break;
				case 132:
				
					break;
				case 133	:
					//down key pressd
				
					if(get_from_hist>0)
					{
						get_from_hist--;
						//check his_node not is not null
						hist_node=get(input_history,get_from_hist);
						clear_my_input(char_counter);
						strcpy(str,hist_node->data);
						char_counter=strlen(str);
						printf("%s",str);
					}
					else
					{
						//there is no another data in history so show my own input
						strcpy(str,temp);
						clear_my_input(char_counter);
						char_counter=strlen(str);
						printf("%s",str);
					}
					break;
			}
		//get the release code
		c=getch();

		}//end of switch

	}//end of while
	putchar('\n');
	str[char_counter] = '\0';
	remove_end_spaces(str);//remove the whitespaces at the end of str.
	//printf("the str: %s\n",str);

	hist_node=get(input_history,0);
	if(strcmp(hist_node->data,str))
	{

		//if str was not as same as first data of linkedlist
		input_history=add_head(input_history,str);
		//printf("datas:");
		//print(input_history);
	}
	
	return strlen(str);

}//end of function

void remove_end_spaces(char *str)
{
	int i;
	i=strlen(str)-1;
	while(isspace(str[i]))
		i--;
	str[i+1]=0;
}
	
	

void clear_my_input(int char_counter)
{
	while(char_counter--)
	{
		putch('\b');	
		putch(' ');
		putch('\b');
	}
}
/*stores each tokens in vector*/
/*white spaces are our delimeter*/
/*return :argument_vector and return NULL for no value(like just white space)*/

char **tokenize(char *str, int *argv_len)
{
	int str_index, temp_index;
	int *size;
	char temp[100], **argv;

	argv = NULL;
	str_index = *argv_len = temp_index = 0;

	/*jump whitespaces*/
	while (isspace(str[str_index])||str[str_index]==8)
{

	 str_index++;
}

	while (str[str_index] != '\0')
	{

		if (!isspace(str[str_index]))
		{
			temp[temp_index++] = str[str_index++];
		}
		else//we reached whitespace
		{
			temp[temp_index] = 0;
			if (argv == NULL)
				argv=initialize_vector(argv_len, temp);
			else
				argv=insert_vector(argv, argv_len,temp);
			temp_index = 0;

			/*jump whitespaces*/
			while (isspace(str[str_index])) str_index++;
		}
	}
	/*after reaching end of line*/
	
	temp[temp_index] = 0;
	/*if there was not any valid data at the end*/
	if ((temp[0]) == 0)
		{
		return argv;
		}
	/*if there was valid data at the end*/
	if (argv == NULL)
		argv = initialize_vector(argv_len, temp);
	else
		argv = insert_vector(argv, argv_len, temp);
	return argv;
}

/*insert data to an initialized vector*/
/*return head of vector*/
char **insert_vector(char **head, int *size, char *str)
{
	char **new_head;
	int i = 0;
	if (head == NULL)
		return NULL;
	*size = *size + 1;
	new_head = (char **)malloc(sizeof(char *)*(*size+1));
	for (i = 0; i < (*size)-1; i++)
	{
		new_head[i] = (char *)malloc(sizeof(char )*(strlen(head[i])+1));
		strcpy(new_head[i], head[i]);
	}
	new_head[i] = (char *)malloc(sizeof(char )*(strlen(str)+1));

	strcpy(new_head[i], str);
	//printf("free(head,((*size)-1)*sizeof(char *)+1);\n");
	//free(head,((*size))*sizeof(char *));
	return new_head;
}
/*initialize new vector*/
/*return head of vector*/
char ** initialize_vector(int *argv_len,char *temp)
{
	*argv_len = 1;
	char **head;
	head = (char **)malloc(sizeof(char *)*2);
	head[0] = (char *)malloc(sizeof(char)* (strlen(temp)+1));
	strcpy(head[0], temp);
	return head;

}

NODE *get_new_node(char *item)
{
	/*makes a new node*/
	NODE *new_node;
	new_node = (NODE *)malloc(sizeof(NODE));
	strcpy(new_node->data,item);
	new_node->next = NULL;
	return new_node;
}

NODE * add_head(NODE * head,char * item)
{
	/*add a node to begin of linked list*/
	NODE *new;
	if (head == NULL)
		return get_new_node(item);
	new =get_new_node(item);
	new->next=head;
	head = new;
	return head;
}
NODE * get(NODE * head, int index)
{
	/*return the node in that index*/
	int i = 0;
	while (head != NULL)
	{
		if (i == index)
		{
			return head;
		}
		i++;
		head = head->next;
	}
	return NULL;
}


void print(NODE * head)
{
	if (head == NULL)
		printf("no item\n");
	while (head != NULL)
	{
		printf("%s\t", head->data);
		printf("%d\t",strlen(head->data));
		head = head->next;
	}
	putchar('\n');
}


