;Take 2 numbers and returns sum
; https://www.spoj.com/problems/TESTINT/

global _start
 
section .data
 
 
section .bss           
   numb resb 1
   sum  resb 3
section .text
 
 
_start:
    mov edi,0
    mov esi,0
getfirstnum:
    mov eax,3
    mov ebx,0
    mov ecx,numb
    mov edx,1
    int 80h
    movzx eax, BYTE[numb]
    cmp eax, '0'
    jl getsecondnum
    cmp eax, '9'
    jg getsecondnum
    imul edi,10
    add edi, eax
    sub edi, '0'
    jmp getfirstnum
getsecondnum:
    mov eax,3
    mov ebx,0
    mov ecx,numb
    mov edx,1
    int 80h
    movzx eax, BYTE[numb]
    cmp eax, '0'
    jl sumandprint
    cmp eax, '9'
    jg sumandprint
    imul esi,10
    add esi, eax
    sub esi, '0'
    jmp getsecondnum
sumandprint:    
    add esi,edi
    mov eax,esi
    xor edx,edx
    xor ecx,ecx
    mov ebx,10
loopconvert:
    xor edx,edx
    div ebx
    push edx
    inc ecx
    cmp eax,0
    jne loopconvert
    mov ebx,sum
    mov edx,ecx
gettostring:
    pop eax
    add eax,'0'
    mov BYTE [ebx],al
    inc ebx
    sub ecx,1
    jnz gettostring
print:
    mov eax,4
    mov ebx,1
    mov ecx,sum
    int 80h
;exit  
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h  
