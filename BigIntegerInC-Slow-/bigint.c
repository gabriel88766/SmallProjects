#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned int u32;
typedef unsigned long long int u64;

const u64 Billion = 1000*1000*1000;
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

void multiplyBig(bigint *b,bigint *c){
    int i,j,maxlen = b->len + c->len;
    u32 carry=0,*v = calloc(maxlen,sizeof(u32));
    u64 aux;
    for(i=0;i<b->len;i++){
        for(j=0; j < c->len; j++){
            aux = c->p[j];
            aux *= b->p[i];
            aux += carry;
            v[i+j] += aux%Billion;
            if(v[i+j] >= Billion){
                carry=1;
                v[i+j] -= Billion;
            }else carry=0;
            carry += aux/Billion;
        }
        v[i+c->len]+=carry;
        if(i!=(b->len-1))carry=0;
    }
    if(carry){
        b->len = maxlen;
    }else{
        b->len = maxlen - 1;
    }
    for(i=0;i<maxlen;i++){
        b->p[i] = v[i];
    }
    free(v);
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

void addBig(bigint *b,bigint *c){
    int bsz = b->len, csz = c->len, maxsz, i;
    u32 carry=0;
    u64 aux;
    maxsz = (bsz > csz ? bsz : csz);
    for(i=0;i<maxsz;i++){
        aux = 0;
        if(csz>i) b->p[i] += c->p[i];
        b->p[i]+=carry;
        if(b->p[i]>=Billion){
            b->p[i]-=Billion;
            carry = 1;
        }else carry = 0;
    }
    b->len = maxsz;
    if(carry) b->p[maxsz] = 1,b->len=maxsz+1;
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
   bigint b,c;
   newBigint(&b,"2",60000);
   newBigint(&c,"2",1);
   for(i=0;i<1e5-1;i++){
       addBig(&b,&b); /*Example */
   }
   printBigint(b);
   freeBigint(&b);
   return 0;
}
