/*
Author: Gabriel Vinícius, 07/17/2020
This program can generate a image in bitmap(.bmp) format with random RGB pixels.
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
(optional)resolution(pixels/meters) in array[38] for width and in array[42] for height.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct RGB{
	unsigned char B;
	unsigned char G;
	unsigned char R;
}RGB;

void make_random_image(char *filename, unsigned int width, unsigned int height, RGB lower, RGB higher, unsigned int mode){
	unsigned char header_and_infoheader[] = {'B','M',0,0,0,0,0,0,0,0,0x36,0,0,0,0x28,0,0,0,0,
	                                             0,0,0,0,0,0,0,1,0,0x18,0,0,0,0,0,0,0,0,0,0,
	                                                0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	RGB *randBGR;
	unsigned int i,j,imagesize, filesize,aux;
	unsigned int rangeR,rangeB,rangeG;
	float aux1,aux2,aux3;
	FILE *f;

	rangeR = higher.R - lower.R + 1;
	rangeG = higher.G - lower.G + 1;
	rangeB = higher.B - lower.B + 1;


    filesize = 0x36 + width*height*3;
    memcpy(header_and_infoheader+2,&filesize,4);
    memcpy(header_and_infoheader+18,&width,4);
    memcpy(header_and_infoheader+22,&height,4);
    imagesize = filesize - 0x36;
    memcpy(header_and_infoheader+34,&imagesize,4);

    randBGR = malloc(width*height*sizeof(RGB));
	srand((unsigned int)time(NULL));
	switch(mode){
        case 0:{
            for(i = 0; i < height; i++){
                for(j = 0; j < width; j++){
                    randBGR[i*width+j].B = ((rand() % rangeB) + lower.B);
                    randBGR[i*width+j].G = ((rand() % rangeG) + lower.G);
                    randBGR[i*width+j].R = ((rand() % rangeR) + lower.R);
                }
            }
            break;
        }
        case 1:{
            aux1 = ((float)rangeR)/256;
            aux2 = ((float)rangeG)/256;
            aux3 = ((float)rangeB)/256;
            for(i=0; i<height; i++){
                for(j=0;j<width;j++){
                    aux = rand()%256;
                    randBGR[i*width+j].B = (unsigned int)(aux*aux3+(float)lower.B );
                    randBGR[i*width+j].G = (unsigned int)(aux*aux2+(float)lower.G );
                    randBGR[i*width+j].R = (unsigned int)(aux*aux1+(float)lower.R );
                }
            }
            break;
        }
        default:{
            printf("error");
            exit(1);
        }
	}

	f = fopen(filename,"wb");
	if(!f){
		exit(1);
	}
	fwrite(header_and_infoheader,1,0x36,f);
	fwrite(randBGR,1,imagesize,f);
	fclose(f);

	free(randBGR);
}
int main(){

unsigned int width,height,aux1,aux2,aux3,mode;
char filename[55] = {0};
RGB lower,upper;
printf("Input: width and height(width must be multiple of 4)\n\n");
scanf("%u%u",&width,&height);
printf("Input: lower bound RGB (0 to 255 each) where (R_lower < R_higher, G_lower < G_higher, B_lower < B_higher)\n");
scanf("%u%u%u",&aux1,&aux2,&aux3);
lower.R = aux1; lower.G = aux2; lower.B = aux3;
printf("Input: upper bound RGB(R_lower < R_higher, G_lower < G_higher, B_lower < B_higher)\n");
scanf("%u%u%u",&aux1,&aux2,&aux3);
upper.R = aux1; upper.G = aux2; upper.B = aux3;
if(lower.R>upper.R || lower.G > upper.G || lower.B > upper.B){
    printf("error");
    exit(1);
}
printf("enter mode:\n");
scanf("%u",&mode); /* mode 0: all colors of each pixel are random; mode 1: colors = Ax+B where B=lower, A = (upper-lower)  0<x<1   */
printf("enter file name(up to 50 letters):\n");
scanf("%s",filename);
aux1 = strlen(filename);
filename[aux1]='.';
filename[aux1+1]='b';
filename[aux1+2]='m';
filename[aux1+3]='p';
make_random_image(filename,width,height,lower,upper,mode);

return 0;
}

