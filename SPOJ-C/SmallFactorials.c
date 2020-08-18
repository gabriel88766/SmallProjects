/* link https://www.spoj.com/problems/FCTRL2/ */
/* implementing big int, this program can print up to 200!, It can multiply and divide by any numbers. You can modify and do other things */

#include<stdio.h>
#include<stdlib.h>
#define D 0x19999999 /* 2^32/10 */
typedef unsigned int u32;
typedef unsigned long long int u64;
#define A printf("entrou");
#define F ((aux2*6)/10)

typedef struct bigint{
    u32 len;
    u32 *p;
}bigint;

void multiply(bigint *b,int num){
    u64 aux;
    u32 carry=0;
    int i;
    for(i=0;i<b->len;i++){
       aux = b->p[i];
       aux*=num;
       aux+=carry;
       b->p[i]=(aux); /*no carry*/
       carry=(aux>>32);
    }
    if(carry!=0){
        b->len++;
        b->p[b->len-1]=carry;
    }
}

void divideBy10(bigint *b){ 
    u64 aux,rem=0;
    int i = (b->len)-1;
    while(i>-1){
        rem <<=32;
        rem+= b->p[i];
        aux=rem/10;
        b->p[i]=aux;
        rem %=10;
        i--;
    }

}

void print(bigint b){
    char v[200];
    u32 aux=2,count=0,i,at;
    while(aux!=0){
        aux=0;
        at=b.p[0]%10;
        for(i=1;i<b.len;i++){
            aux|=b.p[i];
            at+=((b.p[i]%10)*6);
        }
        at%=10;
        at+='0';
        v[count]=at;
        count++;
        divideBy10(&b);
        aux|=b.p[0];
    }
    count--;
    while(count!=-1){
        printf("%c",v[count]);
        count--;
    }
    printf("\n");
}

int main() {
   int t,i,a,j;
   bigint b;
   b.p = malloc(sizeof(u32)*20);
   b.len = 1;
   scanf("%d",&t);
   for(i=0;i<t;i++){
       for(j=1;j<20;j++){
           b.p[j]=0;
       }
       b.p[0]=1;
       scanf("%d",&a);
       for(j=2;j<=a;j++){
           multiply(&b,j);
       }
       print(b);
   }
   free(b.p);
   return 0;
}
