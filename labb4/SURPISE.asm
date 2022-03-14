# n = $a0
# result = $v0
# product = $a1
# i = $a2
# j = $a3
# k = $v1


addi $a0, $0, 8        # n
addi $v0, $0, 1        # result = 1
addi $v1, $a0, 1    	# k = n + 1
addi $a2, $0, 1            # i = 1
    
loop:
     beq $a2, $v1, done        # i != n

    mul $v0, $v0, $a2        # result = result * i

    addi $a2, $a2, 1        # i++

    beq $0, $0, loop        # jump back to top loop

done:    
    add  $0,$0,$0      # NOP