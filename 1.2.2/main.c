#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Desenho Elaborado 1.2.2!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0xff,0xff,0xFF,0x00);
    SDL_RenderClear(ren);
    filledCircleRGBA(ren, 250,200, 30, 207,167,250, 255);
    filledCircleRGBA(ren, 300,70, 30, 56,77,51, 124);
    filledCircleRGBA(ren, 400,300, 30, 0,0,0, 255);
    filledCircleRGBA(ren, 350,400, 10, 245, 84, 66, 255);
    filledCircleRGBA(ren, 380,400, 10, 245, 84, 66, 255);
    filledCircleRGBA(ren, 410,400, 10, 245, 84, 66, 255);
    filledEllipseRGBA(ren, 170,140, 30,60, 255,0,128, 255);
    filledPieRGBA(ren, 200,20, 70, 90,187, 86,194,62, 255);
    filledPieRGBA(ren, 20,200, 120, 0,180, 86,194,62, 255);
    filledPieRGBA(ren, 300,400, 50, 35,300, 242, 230, 61, 255);
    pixelRGBA(ren, 120,80, 127,90,77, 255);
    pixelRGBA(ren, 80,120, 127,90,77, 255);
    pixelRGBA(ren, 400,80, 127,90,77, 255);
    pixelRGBA(ren, 320,80, 127,90,77, 255);
    pixelRGBA(ren, 200,30, 127,90,77, 255);
    pixelRGBA(ren, 160,400, 127,90,77, 255);
    pixelRGBA(ren, 120,270, 127,90,77, 255);
    pixelRGBA(ren, 240,160, 127,90,77, 255);
    pixelRGBA(ren, 120,20, 127,90,77, 255);
    pixelRGBA(ren, 300,320, 127,90,77, 255);
    pixelRGBA(ren, 120,460, 127,90,77, 255);
    pixelRGBA(ren, 180,100, 127,90,77, 255);
    pixelRGBA(ren, 120,300, 127,90,77, 255);
    roundedBoxRGBA(ren, 100,300, 160,450, 20, 142,40,173, 255);
    characterRGBA(ren, 300, 250, 'A', 166,27,25, 255);
    characterRGBA(ren, 310, 250, 'C', 166,27,25, 255);
    characterRGBA(ren, 320, 250, 'A', 166,27,25, 255);
    characterRGBA(ren, 330, 250, 'B', 166,27,25, 255);
    vlineRGBA(ren, 400,430,200, 25,166,74, 255);
    hlineRGBA(ren, 150,200,5, 25,166,74, 255);
    
    SDL_SetRenderDrawColor(ren, 0x53,0x27,0xdd,0x00);
    SDL_Rect r3 = { 150,150, 200,5 };
    SDL_RenderFillRect(ren, &r3);
    
    SDL_SetRenderDrawColor(ren, 0x13,0x17,0x22,0x00);
    SDL_Rect r4 = { 200,300, 100,20 };
    SDL_RenderFillRect(ren, &r4);
    
    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
