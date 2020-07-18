/*
Author: Gabriel Vinícius, 07/17/2020

This program can generate a 640x480 image in bitmap format with random RGB pixels. 
This code can be modified to generate noise in others color ranges.
Some examples of images created with this file(modified) https://prnt.sc/tk059k https://prnt.sc/tk05x7

Esse programa pode gerar uma imagem 640x480 no formato bitmap com pixels RGB aleatórios.
Este código pode ser modificado para gerar imagens com ruído em certo intervalos de cores. 
Alguns exemplos de imagens feitas com esse arquivo https://prnt.sc/tk059k https://prnt.sc/tk05x7
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main(){
unsigned char header_and_infoheader[] = {'B','M',0x36,0x10,0xE,0,0,0,0,0,0x36,0,0,0,0x28,0,0,0,0x80,
                                             2,0,0,0xE0,1,0,0,1,0,0x18,0,0,0,0,0,0,0x10,0xE,0,0x12,
                                                0xB,0,0,0x12,0xB,0,0,0,0,0,0,0,0,0,0};
unsigned long randomnumber;
unsigned char randBGR[640][480][3];
int i,j,k;
FILE *f;
srand((unsigned int)time(NULL));
for(i=0; i<640; i++){
	for(j=0;j<480;j++){
		for(k=0;k<3;k++){
			randBGR[i][j][k] = (unsigned char)(rand() % 256);
		}
	}
}
f = fopen("randomimage.bmp","wb");
if(!f){
	exit(1);
}
fwrite(header_and_infoheader,1,0x36,f);
fwrite(randBGR,1,0xE1000,f);
fclose(f);
}
