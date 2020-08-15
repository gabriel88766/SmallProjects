; https://www.spoj.com/problems/BSCXOR/
; Input X and Y, two numbers: "X Y"
; Output X^Y
;
global _start
 
section .data
 
 
section .bss           ;Uninitialized data
   line resb 3
   resp resb 1
 
section .text
 
_start:

   read1:
   mov eax, 3
   mov ebx, 0
   mov ecx, line
   mov edx, 3
   int 80h
 
   movzx eax,  BYTE [line]
   movzx ebx,  BYTE [line+2]
   add eax,ebx
   mov edx,0
   mov ebx, 2
   div ebx
   add edx, '0'
   mov [resp], edx  
 
 
       write:
   mov ecx, resp
   mov eax, 4
   mov ebx, 1
   mov edx, 1
   int 80h 
 
 
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h       
 
