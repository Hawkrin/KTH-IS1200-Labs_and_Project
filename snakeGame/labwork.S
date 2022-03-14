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

.global hexasc
hexasc:
	andi	$t0, $a0, 0xf

	slti	$t1,$a0,10		# checks if $t0 < 9
	bne		$t1,$zero,low	# if $t0 <= t0, goes to low
	
	slti	$t1,$a0,16		# checks if $t0 < 15
	bne		$t1,$zero,high	# if $t0 <= t0, goes to high

	low:
		addi	$v0,$t0, 0x30
		jr $ra
		nop
	high:
		addi	$v0,$t0, 0x37
		jr $ra
		nop
  
.global delay
delay:  
	li $t1, 2000 #våran konstant
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
# 23:15, ":" = 0x3A
.global time2string
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1

	move $s0, $a0 # Address where well store printable time
	move $s1, $a1 # Address of mytime
		
	#ADD CHECK FOR RESET?
	
	andi $t0, $s1, 0xf000 # Get first digit
	srl $a0, $t0, 0x0c # Shift right by 12
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 0($s0)
	
	andi $t0, $s1, 0xf00 # Get second digit
	srl $a0, $t0, 0x8 # Shift right by 8
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 1($s0)
	
	li $t1, 0x3a # Load :
	sb $t1, 2($s0)
	
	andi $t0, $s1, 0xf0 # Get third digit
	srl $a0, $t0, 0x4 # Shift right by 4
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 3($s0)
	
	andi $a0, $s1, 0xf # Get last digit, no shift needed
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 4($s0)
	
	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop
	

	
	
	
	
