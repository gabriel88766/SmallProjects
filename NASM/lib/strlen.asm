
;C = unsigned int strlen(const char *c); returns size of the string if it has a null character



section .data
    string db 'Hello',0
    is5s  db 'Is 5!',10
    isnot5s db 'Is not 5',10
section .bss
    
    
    
section .text

global _start

strlen: ;BEGIN:params: pointer to the string
        mov ebx, DWORD [esp+4]
        xor eax,eax
    strlencase0:
        cmp BYTE[ebx+eax],0
        je returnFromStrlen
    loopcasegt0:
        add eax,1
        cmp BYTE[ebx+eax],0
        jne loopcasegt0
    returnFromStrlen:
        ret
;END strlen

;-----------------------------------------------
;----------------TEST---------------------------
;-----------------------------------------------

_start:
    push string
    call strlen
    add esp,4
    cmp eax,5
    jne isnot5
    

is5:   
    mov eax, 4
    mov ebx,1
    mov ecx,is5s
    mov edx,6
    int 80h
    jmp exit

isnot5:
    mov eax,4
    mov ebx,1
    mov ecx,isnot5s
    mov edx,9
    int 80h

exit:
    mov		eax, 01h		; exit()
    xor		ebx, ebx		; errno
    int		80h
