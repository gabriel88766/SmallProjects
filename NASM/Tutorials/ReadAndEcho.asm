; This program can read and write up to 15 characters
; https://www.tutorialspoint.com/assembly_programming/assembly_system_calls.htm for more details.

global _start
 
section .data
 
 
section .bss           
   echo resb 15
 
section .text
 
 
_start:

   read:
	   mov eax, 3      ;code for sys_read
	   mov ebx, 0      ;code for stdin
	   mov ecx, echo   ;pointer to address the message will be stored
	   mov edx, 15     ;read up to 15 characters
	   int 80h
 
   write:
	   mov eax, 4     ;code for sys_write
	   mov ebx, 1     ;code for stdout
	   mov ecx, echo  ;const pointer address to write something
	   mov edx, 15    ;write up to 15 characters
	   int 80h 
  
;exit  
	mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h   
