/*
5) Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo..
*/

#include "SDL2/SDL.h"
#include <stdbool.h>

void draw_diagonals(SDL_Renderer* renderer, SDL_Window* window){
    int w,h;
    SDL_GetWindowSize(window,&w,&h);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawLine(renderer,0,0,w,h);
    SDL_RenderDrawLine(renderer,0,h,w,0);
}


int main(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(1280,720,0,&window,&renderer);
    SDL_Event e;

    bool run = true;
    while(run){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) run = false;
        }
        draw_diagonals(renderer,window);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


