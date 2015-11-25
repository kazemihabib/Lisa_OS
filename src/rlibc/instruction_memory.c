
#ifndef stdio.h
#include "stdio.h"
#endif


#include "instruction_memory.h"
#ifndef registers.h
#include "registers.h"
#endif

#ifndef controller.h
#include "controller.h"
#endif


void la(char *reg, char *param)
{
//printf("register in la : %s, param in la : %s\n", reg, param);
	data_head = data_first;
	while ( data_head != NULL )
	{
		if ( strcmp(data_head->label, param) == 0 )
		{
//puts("in label == param if");
			if ( data_head->string != NULL )
			{
//puts("in first if");
//printf("data_head->string : %s\n", (char)data_head->string);
//printf("reg : %s\n",reg); 
				regManager(reg, (int)data_head->string);
				return;	
			}
			else
			{
//puts("getting register name 2");
				regManager(reg,(int) &data_head->word);
				return;
			}
			/*this part can be use instead of the above one with a little improvments*/
			//switch (size)        //add more support for other datatypes here 
			//{
			//case sizeof(word) :
			//		regManager(reg, data_head->word);
			//		return;
			//case sizeof(char):
			//	regManager(reg, (int)data_head->string);   // control if this castng makes any trouble 
			//	return;	
			//default:
			//	data_head = data_head->next;
			//}
		}
		else
//puts("in else");
		{
			data_head = data_head->next;
		}
	}

}

void addu(char *dest, int reg1,int reg2)
{	
	
	//unsigned int sum;
	int sum;
//	printf("%d, %d\n", reg1, reg2);
	//getch();
	//sum = (unsigned int) reg1 + (unsigned int) reg2;
	sum = reg1 + reg2;
	regManager( dest, (int) sum);
	return;
}

void slt(char *dest, int reg1,int reg2)
{	
	int boolValue;
	boolValue = (registers[reg1]<registers[reg2]);
	regManager( dest, boolValue );
	return;
}



void lw(char *dest, char *data)
{
	data_head = data_first;
	while ( data_head != NULL )
	{
		if ( strcmp(data_head->label, data) == 0 )
		{
			regManager(dest, data_head->word);
			return;
		}
		else
		{
			data_head = data_head->next;
		}
	}
	return;	
}
//edited
void lb(char *dest, char *data)
{
	data_head = data_first;
	while ( data_head != NULL )
	{
		if ( strcmp(data_head->label, data) == 0 )
		{
			regManager(dest, data_head->byte);       //check if it needs any casting to char in the second argument[done]
			return;
		}
		else
		{
			data_head = data_head->next;
		}
	}
	return;	
}

void sw(char*dest, char *data)
{
	int reg = registerNames(dest);
	data_head = data_first;
	while ( data_head != NULL )
	{
		if ( strcmp(data_head->label, data) == 0 )
		{
			data_head->word = registers[reg];
			return;
		}
		else
		{
			data_head = data_head->next;
		}
	}
	return;
}


//edited
void sb(char*dest, char *data)
{
	int reg = registerNames(dest);
	data_head = data_first;
	while ( data_head != NULL )
	{
		if ( strcmp(data_head->label, data) == 0 )
		{
			data_head->byte = registers[reg];
			return;
		}
		else
		{
			data_head = data_head->next;
		}
	}
	return;
}

int j(char *dest)
{	
	char tmp[20];
	strcpy(tmp,dest);
	text_head = text_first;
	
	while ( text_head != NULL )
	{
		if ( text_head->label != NULL && strcmp(text_head->label, tmp) == 0 )
		{

			return 0;
		}
		else
		{
			text_head = text_head->next;
		}
	}
	return 0;
}

int bne( char *adress1, char *adress2, char *dest )
{
	int arg1 = registerNames( adress1 ), arg2 = registerNames( adress2 );
	if ( registers[arg1] != registers[arg2] )
	{
		j(dest);
		return 0;
	}
	return 1;                //pick it up if makes any issue/**/**/
}
void jal ( char *function )
{
	//struct text *jumpAdress = text_head;
	//int a;
	char *strp;// = (char *) malloc (STRING_MAX * sizeof(char));
	if ( strcmp( function, "printf" ) == 0 )
	{
		strp = (char  *) registers[4];
		printf( strp, registers[5], registers[6], registers[7] );
	}
	else if ( strcmp( function, "scanf" ) == 0)
	{
		strp = (char  *) registers[4];
		scanf( strp, registers[5] );
	}
	//text_head = jumpAdress;
}

/*Copy contents of register s to register t, i.e. R[t] = R[s].
*/
void move(char *dest, char *reg)
{
	int register_number = registerNames(reg);
	regManager(dest, registers[register_number]);
}
 
/*Load immediate into to register s, i.e. R[s] = immed*/
void li(char *dest, int imm)
{
	regManager(dest, imm);
}





/*Adds a register and a sign-extended immediate value and stores the result in a register (with overflow)
*/
void addi(char *dest, int reg1, int imm)
{
	int sum;
	sum = reg1 + imm;
	regManager(dest, sum);
	return;
}

/*ADDIU -- Add immediate unsigned (no overflow)
Adds a register and a sign-extended immediate value and stores the result in a register

*/
void addiu(char *dest, int reg1, int imm)
{
	unsigned int sum;
	sum = reg1 + imm;
	regManager(dest, (int)sum);
	return;
}

/*AND -- Bitwise and
Bitwise ands two registers and stores the result in a register
*/

void and(char *dest,int reg1,int reg2)
{
	regManager(dest, reg1&reg2);
	return;
}

/*ANDI -- Bitwise and immediate
Bitwise ands a register and an immediate value and stores the result in a register

*/
void andi(char *dest, int reg1, int imm)
{
	regManager(dest, reg1&imm);
	return;
}

/*BEQ -- Branch on equal
Branches if the two registers are equal
*/
int beq(char *adress1, char *adress2, char *dest)
{
	int arg1 = registerNames(adress1), arg2 = registerNames(adress2);
	if (registers[arg1] == registers[arg2])
	{
		j(dest);
		return 0;
	}
	return 1;                //pick it up if makes any issue/**/**/
}


/*BGEZ -- Branch on greater than or equal to zero
Branches if the register is greater than or equal to zero

*/

int bgez(char *adress1, char *dest)
{
	int arg1 = registerNames(adress1);
	if (registers[arg1]>=0)
	{
		j(dest);
		return 0;
	}
	return 1;                //pick it up if makes any issue/**/**/
}

/*BGEZAL -- Branch on greater than or equal to zero and link
Branches if the register is greater than or equal to zero and saves the return address in $31
*/
//int BGEZAL(char *adress1, char *dest)
//{
//	/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//	##################################
//	help me 
//	return adress??????what the *** */
//
//	if (!bgez(adress1, dest))
//	{
//
//	}
//}


/*BGTZ -- Branch on greater than zero
Branches if the register is greater than zero

*/
int  BGTZ(char *adress1, char *dest)
{
	int arg1 = registerNames(adress1);
	if (registers[arg1] >0)
	{
		j(dest);
		return 0;
	}
	return 1;                //pick it up if makes any issue/**/**/
}

/*BLEZ -- Branch on less than or equal to zero
Branches if the register is less than or equal to zero

*/

int blez(char *adress1, char *dest)
{
	int arg1 = registerNames(adress1);
	if (registers[arg1] <=0)
	{
		j(dest);
		return 1;
	}
	return 0;                //pick it up if makes any issue/**/**/
}


/*BLTZAL -- Branch on less than zero and link
Branches if the register is less than zero and saves the return address in $31
*/
/*
int  bitzal()
{

	/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	##################################
	help me
	return adress??????what the *** 
}
*/
/*BNE -- Branch on not equal*/
/*Branches if the two registers are not equal
*/
//int bne(char *adress1, char *adress2, char *dest)
//{
//	int arg1 = registerNames(adress1), arg2 = registerNames(adress2);
//	if (registers[arg1] != registers[arg2])
//	{
//		j(dest);
//		return 0;
//	}
//	return 1;                //pick it up if makes any issue/**/**/
//}

/*DIV -- Divide
Divides $s by $t and stores the quotient in $LO and the remainder in $HI

*/
/*%%%%%%%%%%%%%becuase of this function we should change regManager%%%%%%%%*/

void _div(int reg1, int reg2)
{
	/*lo as quotient and hi as remainder*/
	int quotient, remainder;

	quotient = registers[reg1] / registers[reg2];
	remainder = registers[reg1] % registers[reg2];

	regManager("lo", quotient);
	regManager("hi", remainder);

	return;
}




/*DIVU -- Divide unsigned
Divides $s by $t and stores the quotient in $LO and the remainder in $HI

*/
//void divu(int reg1, int reg2)
//{
//	/*lo as quotient and hi as remainder*/
//	unsigned int quotient, remainder;
//
//	quotient = reg1 / reg2;
//	remainder = reg1 % reg2;
//
//	regManager(lo, (int)quotient);
//	regManager(hi, (int)remainder);
//
//	return;
//}



/*J -- Jump
Jumps to the calculated address
*/
//int j(char *dest)
//{
//	int i = 0;
//	static counter = -1;
//	struct  data *next;
//
//	counter++;
//	//printf("  ct: \"%d\"  \n", counter);
//	text_head = text_first;
//	while (text_head != NULL)
//	{
//		printf("(lable:%s", text_head->label);
//		printf(" dest:%s)\n", dest);
//		if (text_head->label != NULL)
//		{
//			if (strcmp(text_head->label, dest) == 0)
//			{
//				/*next = text_head;
//				free(text_head);
//				text_head = next;*/
//				return 0;
//			}
//			else
//			{
//				/*next = text_head->next;
//				free(text_head);
//				text_head = next;*/
//
//				text_head = text_head->next;
//			}
//		}
//		else
//		{
//			/*next = text_head->next;
//			free(text_head);
//			text_head = next;*/
//
//			text_head = text_head->next;
//		}
//
//
//	}
//	return 0;
//}




/*JAL -- Jump and link
Jumps to the calculated address and stores the return address in $31
*/
/*#######%%%%%%%%%##### need more work %%%%%%%###############
########################################%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
//void jal(char *function)
//{
//	struct text *returnAdress = text_head;
//	//int a;
//	char *strp;// = (char *) malloc (STRING_MAX * sizeof(char));
//	if (strcmp(function, "printf") == 0)
//	{
//		strp = (char  *)registers[4];
//		printf(strp, registers[5], registers[6], registers[7]);
//	}
//	else if (strcmp(function, "scanf") == 0)
//	{
//		strp = (char  *)registers[4];
//		scanf(strp, registers[5]);
//	}
//	text_head = returnAdress;
//}

/*JR -- Jump register
Jump to the address contained in register $s

*/


/*LUI -- Load upper immediate
The immediate value is shifted left 16 bits and stored in the register. The lower 16 bits are zeroes.
*/

void lui(char *dest, int imm)
{
	int shifted;
	shifted = imm << 16;
	regManager(dest, shifted);
}


/*LW -- Load word
A word is loaded into a register from the specified address.
*/
//void lw(char *dest, char *data)
//{
//	data_head = data_first;
//	while (data_head != NULL)
//	{
//		if (strcmp(data_head->label, data) == 0)
//		{
//			regManager(dest, data_head->word);
//			return;
//		}
//		else
//		{
//			data_head = data_head->next;
//		}
//	}
//	return;
//}


/*MFHI -- Move from HI
The contents of register HI are moved to the specified register.
*/


void mfhi(char *dest)
{
	int hi = registerNames("hi");
	regManager(dest, registers[hi]);

}


/*MFLO -- Move from LO
The contents of register LO are moved to the specified register.
*/

void mflo(char *dest)
{
	int lo = registerNames("lo");
	regManager(dest, registers[lo]);

}


/*MULT -- Multiply
Multiplies $s by $t and stores the result in $LO.

*/




/*MULTU -- Multiply unsigned
Multiplies $s by $t and stores the result in $LO.

*/


/*NOOP -- no operation
Performs no operation.
*/
void noop()
{
	;
}

/*OR -- Bitwise or
Bitwise logical ors two registers and stores the result in a register

*/
void or(char *dest, int reg1, int reg2)
{
	regManager(dest, reg1&reg2);
}



/*ORI -- Bitwise or immediate
Bitwise ors a register and an immediate value and stores the result in a register
*/

void ori(char *dest, int reg, int imm)
{
	regManager(dest, reg&imm);
}


/*SLT -- Set on less than (signed)
If $s is less than $t, $d is set to one. It gets zero otherwise.
*/
//void slt(char *dest, int reg1, int reg2)
//{
//	int boolValue;
//	boolValue = (registers[reg1]<registers[reg2]);
//	regManager(dest, boolValue);
//	return;
//}

/*SLTI -- Set on less than immediate (signed)
If $s is less than immediate, $t is set to one. It gets zero otherwise.

*/

void slti(char *dest, int reg1, int imm)
{
	int boolValue;
	boolValue = (registers[reg1]<imm);
	regManager(dest, boolValue);
	return;
}


/*SLTIU -- Set on less than immediate unsigned
If $s is less than the unsigned immediate, $t is set to one. It gets zero otherwise.
*/

//void slti(char *dest, int reg1, int imm)
//{
//	int boolValue;

//	boolValue = (registers[reg1]<(unsigned int )imm);
//	regManager(dest, boolValue);
//	return;
//}

/*SLTU -- Set on less than unsigned
If $s is less than $t, $d is set to one. It gets zero otherwise.
*/
//void slt(char *dest, int reg1, int reg2)
//{
//	int boolValue;
//	boolValue = ((unsigned int)registers[reg1]<(unsigned int) registers[reg2]);
//	regManager(dest, boolValue);
//	return;
//}

/*SRA -- Shift right arithmetic
Shifts a register value right by the shift amount (shamt) and places the value in the destination register. The sign bit is shifted in.

*/



/*SRL -- Shift right logical
Shifts a register value right by the shift amount (shamt) and places the value in the destination register. Zeroes are shifted in.

*/


/*SRLV -- Shift right logical variable
Shifts a register value right by the amount specified in $s and places the value in the destination register. Zeroes are shifted in.

*/


/*SUB -- Subtract
Subtracts two registers and stores the result in a register
*/
void sub(char *dest, int reg1, int reg2)
{
	int sub;
	sub = reg1 - reg2;
	regManager(dest, sub);
	return;
}


/*SUBU -- Subtract unsigned
Subtracts two registers and stores the result in a register
*/
void subui(char *dest, char *reg1, int reg2)
{
	unsigned int sub;
	unsigned int tmp;
	tmp = registers[registerNames(reg1)];
	sub = (unsigned int)tmp - (unsigned int)reg2;
	regManager(dest, (int)sub);
	return;
}




/*SW -- Store word
The contents of $t is stored at the specified address.
*/



/*SYSCALL -- System call
Generates a software interrupt.
*/


/*XOR -- Bitwise exclusive or
Exclusive ors two registers and stores the result in a register
*/
void xor(char *dest, int  reg1, int reg2)
{
	regManager(dest, reg1^reg2);
}




/*XORI -- Bitwise exclusive or immediate
Bitwise exclusive ors a register and an immediate value and stores the result in a register
*/

void xori(char *dest, int reg1, int reg2 )
{
	regManager(dest, (unsigned int)reg1^(unsigned int)reg2);
}


char *asciiz( FILE *file_ptr )
{
	int i = 0;
	char c;
	char *string = (char *) malloc (STRING_MAX * sizeof(char) );
	while ( (c = fgetc(file_ptr)) != '"' );
	while ( (c = fgetc(file_ptr)) != '"' )
	{
		string[i++] = c;
	}
	string[i] = '\0';
	return string;
}
