#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>

uint32_t *buff;
//ARGB
uint32_t toARGB(unsigned char R, unsigned char G, unsigned char B){
    return ((uint32_t)B << 24) | ((uint32_t)G << 16) | ((uint32_t)R << 8) | 0xFF;
}

void setPixel(uint32_t *buff, int x, int y, uint32_t color){
    if(x < 0 || x >= 800 || y < 0 || y >= 600) return;
    buff[800 * y + x] = color;
}

void clear(uint32_t *buff){
    for(int i=0;i<600;i++){
        for(int j=0;j<800;j++){
            setPixel(buff, j, i, 0); //black;
        }
    }
}

double dt = 0.1;
double G = 6.67408e-11;
double M = 1.9891e30;
//p2_x = 400, p2_y = 300;
double pos_x = 100, pos_y = 300;
double vel_x = 0, vel_y = -0.21456;
double acel_x = 0, acel_y = 0;

void new_pos(){
    pos_x += vel_x * dt;
    pos_y += vel_y * dt;
}

void new_vel(){
    vel_x += acel_x * dt;
    vel_y += acel_y * dt;
}

void new_accel(){
    double d_x = 400 - pos_x;
    double d_y = 300 - pos_y;
    double d2 = (pow(d_x, 2) + pow(d_y, 2));
    double rd = sqrt(d2);
    double acel = (G*M)/ (d2 * 2.5e17);
    acel_x = acel * (d_x/rd) * 2.592e-2;
    acel_y = acel * (d_y/rd) * 2.592e-2;
}

int main(){
    freopen("logs", "w", stdout);
    if(!SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    SDL_Window *window = SDL_CreateWindow("My Small Window", 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, 800, 600);

    buff = malloc(sizeof(uint32_t) * 800 * 600);

    bool running = 1; 
    while(running){
        SDL_Event event;
        while (SDL_PollEvent(&event)) { 
            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }
        clear(buff);
        int X = pos_x;
        int Y = pos_y;
        for(int i=-10;i<=10;i++){
            for(int j=-10;j<=10;j++){
                if(i*i + j*j <= 100) setPixel(buff, X+i, Y+j, toARGB(0, 0, 255));
            }
        }
        for(int i=-40;i<=40;i++){
            for(int j=-40;j<=40;j++){
                if(i*i+j*j <= 1600) setPixel(buff, 400 + i, 300 + j, toARGB(255, 255, 0));
            }
        }
        for(int i=0;i<500;i++){
            new_accel();
            new_vel();
            new_pos();
        }
        SDL_RenderClear(renderer);
        

        SDL_UpdateTexture(texture, NULL, buff, 800 * sizeof(uint32_t));


        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

}