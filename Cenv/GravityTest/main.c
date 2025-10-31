#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>


typedef struct {
    double x, y;
    double vx, vy;
    double ax, ay;
    double m;
    double radius;
    uint32_t color;
} Body;

const uint32_t toARGB(unsigned char R, unsigned char G, unsigned char B){
    return ((uint32_t)B << 24) | ((uint32_t)G << 16) | ((uint32_t)R << 8) | 0xFF;
}

const int body_count = 9;
Body bodies[9];

void init_bodies(){
    bodies[0] = (Body){400 + 58.5, 300, 0, -1.1, 0, 0, 0.0553, 4,  toARGB(169,169,169)}; //Mercury
    bodies[1] = (Body){400 + 108, 300, 0, -0.801006711409395, 0, 0, 0.815, 9,  toARGB(255,165,0)}; //Venus
    bodies[2] = (Body){400 +150, 300, 0, -0.682885906040268, 0, 0, 1,10,  toARGB(0,0,255)}; //Earth
    bodies[3] = (Body){400 +228, 300, 0, -0.55369127516778523, 0, 0, 0.1075, 6,  toARGB(255,0,0)}; //Mars
    bodies[4] = (Body){400 +780, 300, 0, -0.29899328859060402, 0, 0, 317.8,30, toARGB(210,180,140)}; //Jupiter
    bodies[5] = (Body){400 +1431, 300, 0, -0.22147651006711409395, 0, 0, 95.2,25, toARGB(255,255,153)}; //Saturn
    bodies[6] = (Body){400 +2880, 300, 0, -0.15503355704697986,0, 0, 14.6,16, toARGB(173,216,230)}; //Uranus
    bodies[7] = (Body){400 +4509, 300, 0, -0.1255033557046979865, 0, 0, 17.2,16, toARGB(0,0,139)}; //Neptune
    bodies[8] = (Body){400, 300, 0, 0, 0, 0, 330000,45, toARGB(255,255,0)}; //Sun
}

uint32_t *buff;
//ARGB


void setPixel(uint32_t *buff, int x, int y, uint32_t color){
    if(x < 0 || x >= 800 || y < 0 || y >= 600) return;
    buff[800 * y + x] = color;
}

const double G = 0.00022;
const double dt = 0.1;
void moveBodies(){
    for(int i=0;i<body_count;i++){
        bodies[i].ax = bodies[i].ay = 0;
        for(int j=0;j<body_count;j++){
            if(i == j) continue;
            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double d2 = dx*dx + dy*dy;
            double dist = sqrt(d2);
            double a = G * bodies[j].m / d2;
            bodies[i].ax += a * dx / dist;
            bodies[i].ay += a * dy / dist;
        }
    }
    for(int i=0; i<body_count; i++){
        bodies[i].vx += bodies[i].ax * dt;
        bodies[i].vy += bodies[i].ay * dt;
        bodies[i].x  += bodies[i].vx * dt;
        bodies[i].y  += bodies[i].vy * dt;
    }
}

void newFrame(uint32_t *buff){
    memset(buff, 0, sizeof(uint32_t) * 800 * 600);
    for(int k=0;k<9;k++){
        int X = bodies[k].x;
        int Y = bodies[k].y;
        int K = bodies[k].radius;
        for(int i=Y-K-1;i<=Y+K+1;i++){
            for(int j=X-K-1;j<=X+K+1;j++){
                double dx = bodies[k].x - j;
                double dy = bodies[k].y - i;
                const double r = bodies[k].radius;
                if(dx*dx + dy*dy <= r*r){
                    setPixel(buff, j, i, bodies[k].color);
                }
            }
        }
    }
}

int MOVES_PER_FRAME = 60;

int main(){
    // freopen("logs", "w", stdout);
    if(!SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    init_bodies();
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
        for(int i=0;i<MOVES_PER_FRAME;i++){
            moveBodies();
        }
        newFrame(buff);
        
        SDL_RenderClear(renderer);
        

        SDL_UpdateTexture(texture, NULL, buff, 800 * sizeof(uint32_t));


        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        SDL_Delay(12);
    }

}