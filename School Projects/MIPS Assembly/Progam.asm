# Author : Matt Phillips
# Date : 4-15-13
# Info : This progam opens a menu to demonstrate various operations on up to 3 arrays
#
#######################  DATA  #############################
			.data
		#declare the various string variables for the program
greeting: 	.asciiz "Greetings! What would you like to do?\n"
promptNum:	.asciiz "Enter a number: \n"
newArray:	.asciiz "The new array looks like: \n"
printValue:     .asciiz "Value at position "
printValue2:	.asciiz " is : "
newLine:	.asciiz "\n"
arrayChoice:    .asciiz "Which array would you like to choose, 1 or 2? (you may only PRINT array 3)\n"
badChoice:	.asciiz "Bad selection! Please make a valid choice.\n"
exitMessage:	.asciiz "Farewell, have fun!\n"
option1:	.asciiz " 1: Initialize an array. (1 or 2)\n"
option2:	.asciiz " 2: Print an array.( 1 2 or 3)\n"
option3:	.asciiz " 3: Add the arrays.(1 + 2 into 3)\n"
option4:	.asciiz " 4: Multiply the arrays.(1 x 2 into 3)\n"
option5:	.asciiz " 5: Divide the arrays. (integer division, 1/2 into 3)\n"
option6:	.asciiz " 6: Sort an array - Ascending. (1 or 2)\n"
option7:	.asciiz " 7: Sort an array - Descending. (1 or 2)\n"
option8:	.asciiz " 8: Search an array for an element. (1 or 2)\n"
option9:	.asciiz " 9: Exit. \n" 	

		# declare temporary variables
choice: 	.word 0
var1:		.word 0	
var2:		.word 0
var3:		.word 0

		# declare 2 arrays of 10 elements each (40 bytes = 4 bytes * 10 spaces)
		.align 2 # aligns the array to be consistent with the address of 4 byte words		
array1: 	.space 40 
array2:		.space 40
array3:		.space 40				
			
			
			
#######################  TEXT  #############################
			.text
#######################  MAIN  #############################
			main:
li $v0, 4	
la $a0, greeting # print greeting
syscall

printMenu:
	li $v0, 4
	la $a0, option1 #print option 1
	syscall
	
	li $v0, 4
	la $a0, option2 #print option 2
	syscall
	
	li $v0, 4
	la $a0, option3 #print option 3
	syscall
	
	li $v0, 4
	la $a0, option4 #print option 4
	syscall
	
	li $v0, 4
	la $a0, option5 #print option 5
	syscall
	
	li $v0, 4
	la $a0, option6 #print option 6
	syscall

	li $v0, 4
	la $a0, option7 #print option 7
	syscall
	
	li $v0, 4
	la $a0, option8 #print option 8
	syscall
	
	li $v0, 4
	la $a0, option9 #print option 9
	syscall
	
	li $v0, 5
	syscall

	sw $v0, choice	#store user input from $v0 into choice
	lw $t0, choice	# load choice into register $t0 for use (not necessary)
	
		#determine which branch to take
	beq $t0, 1, choice1 
	beq $t0, 2, choice2
	beq $t0, 3, choice3
	beq $t0, 4, choice4
	beq $t0, 5, choice5
	beq $t0, 6, choice6
	beq $t0, 7, choice7
	beq $t0, 8, choice8
	beq $t0, 9, exit
	
	li $v0, 4
	la $a0, badChoice
	syscall
	j printMenu
#######################  Menu Option 1  #############################
			# initialize an array
			choice1:
		li $t1, 0 #initialize a counter for the array
		
		li $v0, 4
		la $a0, arrayChoice # print arrayChoice
		syscall
		
		li $v0, 5	# get array choice from user
		syscall
		
		sw $v0, var1
		lw $t0, var1
		
		beq $t0, 1, arr1opt1 # array 1 was chosen
		beq $t0, 2, arr2opt1 # array 2 was chosen
	
		li $v0, 4	# if selection was bad
		la $a0, badChoice
		syscall
		j choice1
				
		arr1opt1:
		la $s0, array1
		j choice1for
		
		arr2opt1:
		la $s0, array2
		
		choice1for: 
			blt $t1, 10, choice1forBody
			j printMenu # jump back to main menu
		choice1forBody:
			li $v0, 4
			la $a0, promptNum
			syscall
			
			li $v0, 5
			syscall
			
			sw $v0, var1
			lw $t0, var1
			
			sw $t0, ($s0)
			
			addi $t1, $t1, 1
			addi $s0, $s0, 4
			j choice1for#restart loop
#######################  Menu Option 2  #############################
			# print an array
			choice2:
		li $t1, 0 #initialize a counter for the array
		
		li $v0, 4
		la $a0, arrayChoice # print arrayChoice
		syscall
		
		li $v0, 5	# get array choice from user
		syscall
		
		sw $v0, var1
		lw $t0, var1
		
		beq $t0, 1, arr1opt2 # array 1 was chosen
		beq $t0, 2, arr2opt2 # array 2 was chosen
		beq $t0, 3, arr3opt3 # array 3 was chosen
		
		li $v0, 4	# if selection was bad
		la $a0, badChoice
		syscall
		j choice2
				
		arr1opt2:
		la $s0, array1		
		j choice2for
		
		arr2opt2:
		la $s0, array2
		j choice2for
		
		arr3opt3:
		la $s0, array3
		
		choice2for:
			blt $t1, 10, choice2forBody
			j printMenu # jump back to main menu
		choice2forBody:
			
			li $v0, 4
			la $a0, printValue 
			syscall
			
			sw $t1, var2 # store counter in var2 to print
			
			li $v0, 1
			lw $a0, var2
			syscall
			
			li $v0, 4
			la $a0, printValue2
			syscall
			
			li $v0, 1
			lw $a0, ($s0)
			syscall
			
			li $v0, 4
			la $a0, newLine
			syscall						
			
			addi $t1, $t1, 1
			addi $s0, $s0, 4
			
			j choice2for#restart loop
#######################  Menu Option 3  #############################
			# add the arrays
			choice3:
	li $t1, 0
	li $t9, 0
	la $s0, array1
	la $s1, array2
	la $s2, array3
choice3addFor:
	blt $t1, 10, choice3addForBody
	la $s0, array3	
	j choice3printFor
choice3addForBody:
	lw $t2, ($s0) #get the current element of the first array
	lw $t3, ($s1) #get the current element of the second array
	
	add $t4, $t2, $t3 #add the values
	sw $t4, ($s2)	#store into the current element of the 3rd array
	
	addi $t1, $t1, 1 #increment counter and all array positions
	addi $s0, $s0, 4
	addi $s1, $s1, 4
	addi $s2, $s2, 4
	
	j choice3addFor #restart loop
	
		choice3printFor:
			blt $t9, 10, choice3printForBody
			j printMenu # jump back to main menu
		choice3printForBody:
			li $v0, 4
			la $a0, newArray
			syscall
			
			li $v0, 4
			la $a0, printValue 
			syscall
			
			sw $t1, var2 # store counter in var2 to print
			
			li $v0, 1
			lw $a0, var2
			syscall
			
			li $v0, 4
			la $a0, printValue2
			syscall
			
			li $v0, 1
			lw $a0, ($s0)
			syscall
			
			li $v0, 4
			la $a0, newLine
			syscall						
			
			addi $t9, $t9, 1
			addi $s0, $s0, 4
			
			j choice3printFor
#######################  Menu Option 4  #############################
			# multiply the arrays
			choice4:
	li $t1, 0
	li $t9, 0
	la $s0, array1
	la $s1, array2
	la $s2, array3
	choice4multFor:
	blt $t1, 10, choice4multForBody
	la $s0, array3
	j choice4printFor
	choice4multForBody:
	
	lw $t2, ($s0)
	lw $t3,	($s1)
	
	mul $t4, $t2, $t3
	sw $t4, ($s2)
	
	addi $t1, $t1, 1
	addi $s0, $s0, 4
	addi $s1, $s1, 4
	addi $s2, $s2, 4
	j choice4multFor
		choice4printFor:
			blt $t9, 10, choice4printForBody
			j printMenu # jump back to main menu
		choice4printForBody:
			li $v0, 4
			la $a0, newArray
			syscall
			
			li $v0, 4
			la $a0, printValue 
			syscall
			
			sw $t1, var2 # store counter in var2 to print
			
			li $v0, 1
			lw $a0, var2
			syscall
			
			li $v0, 4
			la $a0, printValue2
			syscall
			
			li $v0, 1
			lw $a0, ($s0)
			syscall
			
			li $v0, 4
			la $a0, newLine
			syscall						
			
			addi $t9, $t9, 1
			addi $s0, $s0, 4
			
			j choice4printFor
#######################  Menu Option 5  #############################
			#divide the arrays
			choice5:
	li $t1, 0
	li $t9, 0
	la $s0, array1
	la $s1, array2
	la $s2, array3
	choice5multFor:
	blt $t1, 10, choice5multForBody
	la $s0, array3
	j choice5printFor
	choice5multForBody:
	
	lw $t2, ($s0)
	lw $t3,	($s1) 
	div $t4, $t2, $t3
	sw $t4, ($s2)
	
	addi $t1, $t1, 1
	addi $s0, $s0, 4
	addi $s1, $s1, 4
	addi $s2, $s2, 4
	j choice5multFor
		choice5printFor:
			blt $t9, 10, choice5printForBody
			j printMenu # jump back to main menu
		choice5printForBody:
			li $v0, 4
			la $a0, newArray
			syscall
			
			li $v0, 4
			la $a0, printValue 
			syscall
			
			sw $t1, var2 # store counter in var2 to print
			
			li $v0, 1
			lw $a0, var2
			syscall
			
			li $v0, 4
			la $a0, printValue2
			syscall
			
			li $v0, 1
			lw $a0, ($s0)
			syscall
			
			li $v0, 4
			la $a0, newLine
			syscall						
			
			addi $t9, $t9, 1
			addi $s0, $s0, 4
			
			j choice5printFor
#######################  Menu Option 6  #############################
			#Sort the arrays - ascending
			choice6:
#######################  Menu Option 7  #############################
			#Sort the arrays - descrnding
			choice7:
#######################  Menu Option 8  #############################
			#search an array
			choice8:			
#######################  Menu Option 9  #############################
			exit:
li $v0, 4
la $a0, exitMessage # print exit
syscall

li $v0, 10 #10 is the function to exit	
syscall
						
