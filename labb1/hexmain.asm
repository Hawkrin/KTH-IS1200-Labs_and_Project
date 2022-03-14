  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,0		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #

.globl hexasc

hexasc:
	and $t0, $a0, 15 #kopierar dom 4 sista bitarna till t0.
	
	ble 	$t0, 9, numbers
	bge	$t0, 10, letters
	
numbers:
	
	addi $v0, $t0, 48

	jr	$ra

letters:

	addi $v0, $t0, 55

	jr	$ra
