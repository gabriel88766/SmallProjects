/*
 If you want to run this code you need to compile as below
 gcc -m32 -masm=intel fibonacciMASMAssembly.c

It only will work if n is stored in 

Input : n - number you want to see output from fibonacci sequence
Output : Fn, where F0 = 1, F1 = 1 , Fn = Fn-1 + Fn-2

*/
#include <stdio.h>


__asm(
    "fibonacci:\n"
    "push ebp\n"
    "mov ebp, esp\n"
    "mov eax, 1\n" /*Fn*/
    "mov ebx, 1\n" /*b, Fn+1*/
    "mov esi, 0\n" /*for(i=0) */
    "mov edx, DWORD PTR[esp+8]\n" /*n */
    "beginfor:\n"
    "cmp esi, edx\n" /*next two lines, if(i>=n) then jump to endfor */
    "jge endfor\n"
    "mov edi, ebx\n" /*old Fn+1 value stored in edi*/
    "add ebx, eax\n" /*update Fn+1*/
    "mov eax, edi\n" /*update Fn = old Fn+1 */
    "add esi, 1\n" /* i++ */
    "jmp beginfor\n" 
    "endfor:\n"
    "pop ebp\n" 
    "ret 4"
);



int main(){
    int n;
    scanf("%d",&n);
    __asm(
	"push ebx\n"
	"call fibonacci"
	:"=a" (n) /*output is n and comes from eax*/
	:"b" (n)  /* input is n and is in ebx */
	);
    printf("\n\nFn = %d",n);
    
    return 0;
    
}
