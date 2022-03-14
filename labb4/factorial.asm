# n = $a0
# result = $v0
# product = $a1
# i = $a2
# j = $a3
# k = $v1


addi $a0, $0, 8        # n
addi $v0, $0, 1        # return register
addi $v1, $a0, 1       # k = n + 1
addi $a2, $0, 1        # i = 1

loop:    
	 beq $a2, $v1, done    	# i != k
    	 addi $a2, $a2, 1    	# i++
    	 addi $a1, $0, 0        # product
    
    	 addi $a3,$0, 1        	# j = 1
    
    
    mul:    
    
    	beq $a3, $a2, out    	# j != i
        addi $a3, $a3, 1    	# j++
        add $a1, $a1, $v0    	# product += result
        beq $0, $0, mul        	# jump back to mul
            
out:   
	addi $v0, $a1, 0        # result = product
    	beq $0, $0, loop        # jump back to top loop
    	
    
done:   
	beq $0, $0, done        # NOP
	
