#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef unsigned int u32;
typedef unsigned long long int u64;
#define Billion 1000000000

u32 powersOf10[] = { 1,10,100,1000,10000,100000,1000000,10000000,100000000};

typedef struct bigint{
    u32 len;
    u32 *p;
}bigint;

/* This was done for simplicity*/

/* in max_len you must put the number of digits divided by 9 */
/* value must be only numbers in a null terminated string, if it assign wrong value so something is wrong with the input*/
void newBigint(bigint *b,char *value,int max_len){
    int pointer,count,count2=0;
    b->p = calloc(max_len,sizeof(u32));
    pointer = strlen(value)-1;
    while(pointer>=0){
        count = 0;
        while((count!=9)&&(pointer>=0)){
            if( value[pointer]<'0' || value[pointer]>'9'){ /* unexpected character, break! (You can change two lines below to ignore it)*/
                pointer=-1;
                break;
            }
            b->p[count2]+=((u32)(value[pointer]-'0'))*powersOf10[count];
            count++;
            pointer--;
        }
        count2++;
    }
    b->len=count2;
}

void freeBigint(bigint *b){
    free(b->p);
    b->len=0;
}

void multiplySmall(bigint *b,int num){
    u64 aux;
    u32 carry=0;
    int i;
    for(i=0;i<b->len;i++){
       aux = b->p[i];
       aux*=num;
       aux+=carry;
       b->p[i]=aux%Billion;
       carry=aux/Billion;
    }
    if(carry!=0){
        b->len++;
        b->p[b->len-1]=carry;
    }
}

void printBigint(bigint b){
    u32 aux;
    int i,j=0;
    printf("%d",b.p[b.len-1]);
    for(i=(b.len-2);i>=0;i--){   
         printf("%.09d",b.p[i]);
    }
    printf("\n");
}

int main() {
   int t,i,a,j;
   bigint b;
   newBigint(&b,"1",60000);
   for(i=0;i<10000;i++){
    multiplySmall(&b,2); /*Example */
   }
   printBigint(b);
   free(b.p);
   return 0;
}
