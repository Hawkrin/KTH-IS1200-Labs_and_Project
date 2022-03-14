  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

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
delay:  
	
	li $t1, 10 #våran konstant
	move $t2, $a0 #int ms

	
	while:
		ble $t2, 0, exit #ms > 0;
		sub $t2, $t2, 1 #ms = ms - 1;
		li $t0, 0 #int i = 0;
		
		for:
			bge $t0, $t1, while #i < $t1
			addi $t0, $t0, 1 #i++
			nop
			
		j for
		nop
						
	j while
	nop
	
	exit:
		jr $ra
		nop
	
#$a0 contains the address of an area in memory	
#$a1 contans time-info. 16 least sig bits.
# 1010 1010 1010 1010
#":" = 0x3A
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1

	move $s0, $a0 # Address where well store printable time
	move $s1, $a1 # Address of mytime
		
	# Första byten
	andi $t0, $s1, 0xf000 
	srl $a0, $t0, 0x0c # Shiftar 12 bits åt höger
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 0($s0)
	
	# Andra byten
	andi $t0, $s1, 0xf00 
	srl $a0, $t0, 0x8 # Shiftar 8 bits åt höger
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 1($s0)
	
	# Lägger till semicolon
	li $t1, 0x3a 
	sb $t1, 2($s0)
	
	#Tredje byten
	andi $t0, $s1, 0xf0
	srl $a0, $t0, 0x4 # Shiftar 4 bits åt höger
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 3($s0)
	
	#Fjärde byten
	andi $a0, $s1, 0xf 
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 4($s0)
	
	#rensar alla stacks och hoppar tillbaks till main
	POP $s1
	POP $s0
	POP $ra
	
	jr $ra
	nop



