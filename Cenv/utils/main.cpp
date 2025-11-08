#include <SDL2/SDL.h>
#include "utils.hpp"
#include <iostream>
#include <deque>

using namespace graphics;
int main(){
    freopen("../logs", "r", stdin);
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << SDL_GetError() << "\n";
        exit(1);
    }
    //add points

    SDL_Window* window = SDL_CreateWindow( "My Graph", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1010, 490, SDL_WINDOW_SHOWN );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, 1010, 490);
    //CREATE IMAGE
    std::deque<double> ini;
    double x;
    for(int i=1;i<=1000;i++){
        std::cin >> x;
        ini.push_back(x);
    } 
    int qnt;
    while(std::cin >> x){
        ini.push_back(x);
        std::cout << x << " ";
        if(ini.size() == 1040){
            while(ini.size() != 1000) ini.pop_front();
            SDL_RenderClear(renderer);
            Graph g;
            for(int i=0;i<ini.size();i++) g.addPoint(i, ini[i]);
            Image img(490, 1010);
            g.plot(img);
            SDL_UpdateTexture(texture, NULL, img.buffer, 1010 * sizeof(uint32_t));
            SDL_Rect dstRect = {0, 0, 1010, 490};
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }
    SDL_DestroyWindow( window );
	SDL_Quit();
}
