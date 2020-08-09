;
;  In this program you can print a 32 bits long in assembly. works in emu8086. It can converts DX:AX to string
;  based on Jose Manuel Abarca Rodríguez answer on https://stackoverflow.com/questions/37605815/how-can-i-print-0-to-100-in-assembly-language-in-emu-8086 
;
       .MODEL SMALL
     .STACK 100H
     .DATA
        NUM DW ?                                   
        lbk    db 13,10,'$'   ;LINE BREAK.
        numstr db '$$$$$$$$$$$$'     ;STRING FOR 4 DIGITS.

     .CODE
     MAIN PROC
          MOV AX,@DATA
          MOV DS,AX

          MOV ax, 9801
          MOV cx, 15536 ;example, dx:ax = 9801*15536 -> ax = 6e30h, dx =913h 
          MUL cx
   

     ;CONVERT NUMBER TO STRING.
         mov  si, offset numstr 
         call number2string    ;RETURNS NUMSTR.

     
     ;DISPLAY STRING.
         mov  ah, 9
         mov  dx, offset numstr
         int 21h     

     ;DISPLAY LINE BREAK.
         mov  ah, 9
         mov  dx, offset lbk
         int 21h     

         
         

     END_:
         mov ax,4C00h
         int 21h
         MAIN ENDP
                      
                      
               
;------------------------------------------                      
;this function can take a dx:ax number and print
number2string proc
  push bp
  mov  bp, sp
  sub  sp, 10; [bp-2] = counter, [bp-4] = remainder, [bp-6] DX, [bp-8], AX where DX:AX = long , [bp-10] stores dx
  mov  cx, 0
  mov  [bp-2], cx; counter=0 
  call dollars ;fill string with '$' 
  mov  bx, 10; divisor  
  mov  [bp-8], ax 
  mov  [bp-6], dx   
cycle1:       
  mov  dx, 0; setting dx to 0 before division/multiplication   
  mov  ax, [bp-8]; updated AX value
  div  bx      ; dx:ax / 10 = ax:QUOTIENT dx:REMAINDER.
  mov  [bp-4], dx ; update remainder
  mov  [bp-8], ax ; update AX
  mov  dx, 0      ; setting dx to 0
  mov  ax, [bp-6] ; setting ax to DX
  div  bx         ; division
  mov  [bp-6], ax
  mov  ax, dx
  mov  [bp-10], dx
  mov  cx, 6553
  mul  cx
  add  [bp-8], ax
  mov  ax, [bp-10]
  mov  cx, 6
  mul  cx   
  mov  dx, 0
  div  bx
  add  [bp-8], ax
  add  [bp-4], dx
  mov  ax, [bp-4]
  mov  dx, 0
  div  bx
  add  [bp-8], ax 
  push dx      
  add  [bp-2], 1      
  mov  ax, [bp-8]   ;IF NUMBER IS
  mov  dx, [bp-6]
  or   ax, dx
  cmp  ax, 0
  jne  cycle1  ;NOT ZERO, LOOP.
  mov  cx, [bp-2] 
;NOW RETRIEVE PUSHED DIGITS.
cycle2:  
  pop  dx        
  add  dl, 48  ;CONVERT DIGIT TO CHARACTER.
  mov  [ si ], dl
  inc  si
  loop cycle2  
  
  mov sp, bp
  pop bp
  ret 
number2string endp  
;------------------------------------------       


;------------------------------------------
;FILLS VARIABLE WITH '$'.
;USED BEFORE CONVERT NUMBERS TO STRING, BECAUSE
;THE STRING WILL BE DISPLAYED.
;PARAMETER : SI = POINTING TO STRING TO FILL.

proc dollars                 
  mov  cx, 12
  mov  di, offset numstr
dollars_loop:      
  mov  bl, '$'
  mov  [ di ], bl
  inc  di
  loop dollars_loop

  ret
endp  

;------------------------------------------

     END MAIN
