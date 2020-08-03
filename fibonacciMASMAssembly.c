/*
 If you want to run this code you need to compile as below
 gcc -m32 -masm=intel fibonacciMASMAssembly.c

*/
#include <stdio.h>


__asm(
    "fibonacci:\n"
    "push ebp\n"
    "mov ebp, esp\n"
    "sub esp, 12\n"
    "mov DWORD PTR[ebp-8], 1\n" /*F_n*/
    "mov DWORD PTR[ebp-4], 1\n" /*b, F_(n+1)*/
    "mov DWORD PTR[ebp-12], 0\n"
    "beginfor:\n"
    "mov eax, DWORD PTR[ebp+8]\n" /*next three lines, if(i>=n) then jump to endfor */
    "cmp DWORD PTR[ebp-12], eax\n" 
    "jge endfor\n"
    "mov eax, DWORD PTR[ebp-4]\n" /*old b value*/
    "mov edx, DWORD PTR[ebp-8]\n"
    "add DWORD PTR[ebp-4], edx\n" /*update b*/
    "mov DWORD PTR[ebp-8], eax\n" /*update a */
    "add DWORD PTR[ebp-12], 1\n" /* i++ */
    "jmp beginfor\n" 
    "endfor:\n"
    "mov eax, DWORD PTR[ebp-8]\n"
    "mov esp, ebp\n"
    "pop ebp\n"
    "ret 4"
);

int main(){
    int a=2,n=10,S=0; /*You need to choose n*/
    __asm(
    "mov eax, DWORD PTR[ebp-16]\n" /*this code only works if &n = ebp-16 and &S = ebp-20 */
    "push eax\n"
    "call fibonacci\n"
    "mov DWORD PTR[ebp-20], eax"
    );
    printf("%d",S);
    return 0;
    
}