#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

uint32_t *buff;
//ARGB
uint32_t toARGB(unsigned char R, unsigned char G, unsigned char B){
    return ((uint32_t)B << 24) | ((uint32_t)G << 16) | ((uint32_t)R << 8) | 0xFF;
}

void setPixel(uint32_t *buff, int x, int y, uint32_t color){
    buff[800 * y + x] = color;
}

void clear(uint32_t *buff){
    for(int i=0;i<600;i++){
        for(int j=0;j<800;j++){
            setPixel(buff, j, i, 0); //black;
        }
    }
}

//p2_x = 400, p2_y = 300;
float pos_x = 20, pos_y = 300;
float vel_x = 0, vel_y = -0.5;

void new_pos(){
    pos_x += vel_x;
    pos_y += vel_y;
}

void new_vel(){

}

int main(){
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
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                setPixel(buff, X+i, Y+j, toARGB(0, 0, 255));
            }
        }
        new_pos();
        new_vel();
        SDL_RenderClear(renderer);
        

        SDL_UpdateTexture(texture, NULL, buff, 800 * sizeof(uint32_t));


        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

}