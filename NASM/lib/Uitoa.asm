;this file can can convert a 'unsigned' number (32 bits) to string
;Input: pointer to array, int n
;_start: output example "16777216"

section .data
    
section .bss
    result resb 32
    
section .text
    global _start

Uint32tostring: ;params: int base, pointer to v[N](This function doesn't care about the size nor if the array is correctly initialized ), unsigned integer 32 bits
    	push ebp
    	mov ebp,esp
    	xor ecx,ecx
    	mov eax, DWORD [ebp+16]
    	mov ebx, DWORD [ebp+8]
	
    divloop: ; take all remainders and stores on the stack
        xor edx, edx; div is made with divisor DX:AX and after this, DX = remainder, AX = quotient
        div ebx
        push edx
    	add ecx,1
    	cmp eax, 0
    	jne divloop
    
        cmp ebx,10 ; The following 2 moves doesn't affect any flags
        mov ebx, DWORD [ebp+12]	 
        mov eax, ecx; length is the returned value
        jle basele10
        
        
    baseg10: ;IF base is greater than 10
        pop edx
        cmp edx,10
        jl ifdigitnotge10
        add edx, 39; letters in ASCII, a=10 and a=48+39+10
    ifdigitnotge10:
        add edx, '0' ; ASCII value
        mov BYTE[ebx], dl
        add ebx, 1
        sub ecx, 1
        jnz baseg10
        
        jmp endUint32tostring
        
    basele10: ;IF base is less than or equal 10 (less instructions)
        pop edx
        add edx, '0' ; ASCII value
        mov BYTE[ebx], dl
        add ebx, 1
        sub ecx, 1
        jnz basele10
    
endUint32tostring:    
    	mov esp,ebp
    	pop ebp
    	ret
	
_start:
	; Simple example
    mov eax, 0x01000000 ;16777216
    mov ecx, result
	push eax
	push ecx
	push 10
	call Uint32tostring
	add esp, 12
	
	;prints the number in that base
	mov edx, eax
	mov eax, 4
	mov ebx, 1
	mov ecx, result
	int 80h

exit:
	mov		eax, 01h		; exit()
	xor		ebx, ebx		; errno
	int		80h
