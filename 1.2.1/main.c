#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Desenho 1.2.1!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xff,0xff,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x46,0x63,0x3a,0x00);
    SDL_Rect r = { 40,20, 5,200 };
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, 0x23,0xaa,0xff,0x00);
    SDL_Rect r2 = { 400,200, 30,400 };
    SDL_RenderFillRect(ren, &r2);
    SDL_SetRenderDrawColor(ren, 0x53,0x27,0xdd,0x00);
    SDL_Rect r3 = { 150,150, 200,5 };
    SDL_RenderFillRect(ren, &r3);
    SDL_SetRenderDrawColor(ren, 0x13,0x17,0x22,0x00);
    SDL_Rect r4 = { 200,300, 100,20 };
    SDL_RenderFillRect(ren, &r4);
    SDL_SetRenderDrawColor(ren, 0x69,0x3e,0x45,0x00);
    SDL_Rect r5 = { 100,300, 60,50 };
    SDL_RenderFillRect(ren, &r5);
    SDL_SetRenderDrawColor(ren, 0xe3,0x0b,0x0b,0x00);
    SDL_Rect ponto = { 120,80, 3,3 };
    SDL_RenderFillRect(ren, &ponto);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
