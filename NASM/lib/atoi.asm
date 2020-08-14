;C : int atoi(const char *c); returns an equivalent integer
;example input and output:  {"15s6",15}, {"  -235", -235} , {" -21 56",-21}, { "af6", 0 }
section .data
    example db '-16777211'
section .bss
    lastdigit resb 1
section .text

global _start

atoi: ;Params: string , take a string and converts do an integer
    mov ebx, DWORD [esp+4]
    xor ecx,ecx; boolean to "is negative"
    mov edi,10
    xor eax,eax
    trim:
        cmp BYTE [ebx],32
        jne whatIsTheSign
        add ebx,1
        jmp trim
    whatIsTheSign:
        cmp BYTE [ebx], '-'
        je isNegative
        jmp atoiExtracting
    isNegative:
        mov ecx, 1; boolean to "is negative"
        add ebx,1
    atoiExtracting:
        movzx esi, BYTE[ebx]
        cmp esi, '0'
        jl isNegativeL2
        cmp esi, '9'
        jg isNegativeL2
        sub esi, '0'
        mul edi
        add eax,esi
        add ebx, 1
        jmp atoiExtracting
    isNegativeL2:
        cmp ecx, 1
        jne endatoi
        neg eax
    endatoi:
        ret
        
;---------------------------------------
;--------------------------------------

  _start:
      ;example call
      push example
      call atoi
      add esp,4
      ; now the value is in eax
      neg eax
      mov ebx, 10
      div ebx
      add edx, '0'
      mov BYTE [lastdigit],dl
      
      mov eax,4
      mov ebx,1
      mov ecx,lastdigit
      mov edx,1
      int 80h
  exit:
        ;mov eax, 1
        ;mov ebx, 0
        ;int 80h
  
