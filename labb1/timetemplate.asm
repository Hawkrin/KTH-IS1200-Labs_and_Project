  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop
	
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
delay:  
	li $t1, 4 #våran konstant
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
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1

	move $s0, $a0 
	move $s1, $a1 
	
	#första nibble
	andi $t0, $s1, 0xf000 #Maskar sista nibble i klockslaget, alltså första siffran i minuten => 23:49 => 2
	srl $a0, $t0, 0x0c #Shiftar svaret med 3 nibbles för att ha talet i positionen 0 -> 3 för att hexasc ska kunna plocka upp den. 
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 0($s0)
	#end	

	#andra nibble
	andi $t0, $s1, 0xf00 
	srl $a0, $t0, 0x8 
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 1($s0)
	#end
	
	#Lägger till semicolon
	li $t1, 0x3a 
	sb $t1, 2($s0)
	#end
	
	# Tredje nibble
	andi $t0, $s1, 0xf0
	srl $a0, $t0, 0x4 
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 3($s0)
	#end
	
	# fjärde nibble
	andi $a0, $s1, 0xf 
	jal hexasc
	nop
	move $t1, $v0
	sb $t1, 4($s0)
	#end
	
	POP $s1
	POP $s0
	POP $ra

	jr $ra
	nop
	

	
	
	
	
	

	
