	.data
i:
	.word	85
j:
	.word 20
MSG:
	.asciiz "the result is : %d"
	
	.text
	.ent	main
main:
	la $4,MSG
	lw $28,i
	lw $27,j
	addu $5,$27,$28
	jal	printf
	.end	main
	
