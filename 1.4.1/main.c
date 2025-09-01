#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>

struct ColoredRect {
    SDL_Rect rect;
    SDL_Color color;
};

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 400, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    bool running = true;
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    
    std::vector<ColoredRect> rects;
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0,255);
    
    int windowWidth, windowHeight;
    SDL_GetWindowSize(win, &windowWidth, &windowHeight);
    
    while (running) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
            
    for (const auto& coloredRect : rects){
        SDL_SetRenderDrawColor(ren, coloredRect.color.r, coloredRect.color.g, coloredRect.color.b, coloredRect.color.a);
        SDL_RenderFillRect(ren, &coloredRect.rect);
    }
        SDL_RenderPresent(ren);

        while(SDL_PollEvent(&evt)) {
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    break;
                case SDLK_F4:
                    if (evt.key.keysym.mod & KMOD_ALT) {
                    running = false;
                    }
                    break;
              }
            if (r.y < 0) {
                r.y = 0;
            }
            if (r.x < 0) {
                r.x = 0;
            }
            if (r.y + r.h > windowHeight) {
                r.y = windowHeight - r.h;
            }
            if (r.x + r.w > windowWidth) {
                r.x = windowWidth - r.w;
            }
            }
        else if (evt.type == SDL_QUIT){
            running = false;
        }
        else if (evt.type == SDL_MOUSEBUTTONDOWN){
            if (rects.size() < 10) {
                ColoredRect newRect;
                newRect.rect.x = evt.button.x;
                newRect.rect.y = evt.button.y;
                newRect.rect.w = 50;
                newRect.rect.h = 40;
                
                newRect.color.r = dist(rng);
                newRect.color.g = dist(rng);
                newRect.color.b = dist(rng);
                newRect.color.a = 255;
                
                rects.push_back(newRect);
            }
        }
    }
}
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
