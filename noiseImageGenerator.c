/*
Author: Gabriel Vinícius, 07/17/2020

This program can generate a 640x480 image in bitmap format with random RGB pixels. 
This code can be modified to generate noise in others color ranges.
Some examples of images created with this file(modified) in Links

Links:
https://photos.app.goo.gl/jCfkrRA8jMV78cRa6
https://photos.app.goo.gl/iLBUh3UDGH4rEMis6

header_and_infoheader: 
For more details about this array, see https://www.fileformat.info/format/bmp/corion.htm 
and you'll can change the resolution of the image.
file size in (array[2], int 4 bytes, little-endian) =  width*height*3 + 0x36
width in (array[18], int 4 bytes, little-endian)
height in (array[22], int 4 bytes, little-endian)
data size in (array[34], int 4 bytes, little-endian) = width*height*3
(optional)resolution(pixels/meters) in array[38] for width and in array[42] for height

*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main(){
unsigned char header_and_infoheader[] = {'B','M',0x36,0x10,0xE,0,0,0,0,0,0x36,0,0,0,0x28,0,0,0,0x80,
                                             2,0,0,0xE0,1,0,0,1,0,0x18,0,0,0,0,0,0,0x10,0xE,0,0x12,
                                                0xB,0,0,0x12,0xB,0,0,0,0,0,0,0,0,0,0};
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
