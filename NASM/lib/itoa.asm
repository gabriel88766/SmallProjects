;this file can can convert a 'signed' number (32 bits) to string
;Input: pointer to array, int n
;_start: output example "-16777216"

section .data
    
section .bss
    result resb 32
    
section .text
    global _start

int32tostring: ;params: int base, pointer to v[N](This function doesn't care about the size nor if the array is correctly initialized ), integer 32 bits
    	push ebp
    	mov ebp,esp
    	sub esp, 1; is negative?
    	mov BYTE [ebp-1],0; assume false
    	xor ecx,ecx
    	mov eax, DWORD [ebp+16] ;number
    	mov ebx, DWORD [ebp+8] ;base
    	
    	mov edx, eax
        or edx, 0x8000000; if number is not negative, jump!
        jz divloop
    isnegativeL1:
        mov BYTE[ebp-1],1
        neg eax
   
	
    divloop: ; take all remainders and stores on the stack
        xor edx, edx; div is made with divisor DX:AX and after this, DX = remainder, AX = quotient
        div ebx
        push edx
    	add ecx,1
    	cmp eax, 0
    	jne divloop
    
        mov ebx, DWORD [ebp+12]
        movzx eax, BYTE[ebp-1]
        cmp eax,0
        jz ispositive
    isnegativeL2:
        add ecx,1
        mov BYTE [ebx],'-'
        add ebx,1
        
    ispositive: 
        mov eax, ecx; length is the returned value
        mov edx, DWORD [ebp+8]; base
        cmp edx, 10
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
        
        jmp endint32tostring
        
    basele10: ;IF base is less than or equal 10 (less instructions)
        pop edx
        add edx, '0' ; ASCII value
        mov BYTE[ebx], dl
        add ebx, 1
        sub ecx, 1
        jnz basele10
    
endint32tostring:    
    	mov esp,ebp
    	pop ebp
    	ret
	
_start:
	; Simple example
    mov eax, 0xFF000000 ; -16777216
    mov ecx, result
	push eax
	push ecx
	push 10
	call int32tostring
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
