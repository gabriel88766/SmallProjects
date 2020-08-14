;this file can can convert a 'signed' number (32 bits) to string
;Input: pointer to array, int n
;_start: output example "-16777216"
; C : int itoa(char* dest, int value,int base); return = length of string. dest = string (It's different of the C version)

section .data
    
section .bss
    result resb 33
    
section .text
    global _start

int32tostring: ;BEGIN: params: int base, pointer to v[N](This function doesn't care about the size nor if the array is correctly initialized ), integer 32 bits
    	push ebp
    	mov ebp,esp
    	sub esp, 1; is negative?
    	mov BYTE [ebp-1],0; assume false
    	xor ecx,ecx
    	mov eax, DWORD [ebp+12] ;value
    	mov ebx, DWORD [ebp+16] ;base
    	cmp ebx,10
	jne divloop; if base is not 0 then we don't need to care about if number is negative or not
    	mov edx, eax
        and edx, 0x80000000; if is base 10 and  the number is not negative, jump!
        jz divloop
    isnegativeL1:
        mov BYTE[ebp-1],1
        neg eax; x -> -x
	
    divloop: ; take all remainders and stores on the stack
        xor edx, edx; div is made with divisor DX:AX and after this, DX = remainder, AX = quotient
        div ebx
        push edx
    	add ecx,1
    	cmp eax, 0
    	jne divloop
    
        mov ebx, DWORD [ebp+8]; dest
        movzx eax, BYTE[ebp-1]
        cmp eax,0
        jz ispositive
    isnegativeL2:
        mov BYTE [ebx],'-'
        add ebx,1
        
    ispositive: 
        mov eax, ecx; length is the returned value
        mov edx, DWORD [ebp+16]; base
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
    
    	mov BYTE[ebx], 0; null character
    
endint32tostring:    
    	mov esp,ebp
    	pop ebp
    	ret
;END FUNCTION 

_start:
	; Simple example
    mov eax, 0xFF000000 ; -16777216
    mov ecx, result
	push 10  ;base
	push eax ;value
	push ecx ;address
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
