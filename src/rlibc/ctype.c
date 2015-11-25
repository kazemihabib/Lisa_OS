
int isdigit(int c)

{

	/*return 1 for 0 1 2 3 4 5 6 7 8 9

	return 0 for other*/

	if (c >= '0' &&  c <= '9')

		return 1;

	return 0;

}



int isalpha(int c)

{

	/*check if digits,lowercase and uppercase*/

	if (islower(c) || isupper(c))

		return 1;

	return 0;

}

int isalnum(int c)

{

	/*check wether the passed character is alphanumeric*/

	if (isalpha(c) || isdigit(c))

		return 1;

	return 0;

}

/* checks if a string consisting both digits and alphabet | i needed it :D xD */
int isalphnum(const char *sp)
{
//printf("in alphnum : %s", sp);
	int digit = 0, alpha = 0;
	while ( *sp != '\0' )
	{
		if ( isdigit(*(sp)) )
		{
			digit = 1;
			++sp;
		}
		else if ( isalpha(*(sp)) )
		{
			alpha = 1;
			++sp;
		}
		if ( alpha == 1 && digit == 1 )
			return 1;
	}
	return 0;
}


int iscntrl(int c)
{

	/*check if control character*/

	if (c == 0 || c >= 7 && c <= 13)

		return 1;

	return 0;

}



int islower(int c)

{

	/*check if c lowercase*/

	if (c >= 'a'&& c <= 'z')

		return 1;

	return 0;

}

int isupper(int c)

{

	/*check if c uppercase*/

	if (c >= 'A'&&c <= 'Z')

		return 1;

	return 0;

}

int isspace(int c)

{

	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f')
		return 1;
	return 0;

}



int isxdigit(int c)

{

	/* check for 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f */

	if (c >= '0'&& c <= '9' || c >= 'a'&&c <= 'f' || c >= 'A'&&c <= 'F')

		return 1;

	return 0;

}





int ispunct(int c)

{

	/*check for! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~ */

	int i;

	char a[32] = { '#', '$', '%', '&', '\\','(',')','*','+',',','-','.','/',':',';','<','=','>','?','@','[',']','^','_','`','{', '|', '}', '~' };

	for (i = 0; i <30; i++)

	if (a[i] == c)

		return 1;

	return 0;

}

int isgraph(int c)

{

	/*check for Alphanumeric characters and Punctuation characters.*/

	if (isalpha(c) || ispunct(c))

		return 1;

	return 0;

}



int tolower(int c)

{

	/*conver uppercase to lowercase if it's not uppercase return it with out

	any change*/

	if (isupper(c))

		return(c - ('A' - 'a'));

	return c;

}



int toupper(int c)

{

	/*convert lowercase to uppercase if it's not lowercase return with out

	any change */

	if (islower(c))

		return (c + ('A' - 'a'));

	return c;

}


