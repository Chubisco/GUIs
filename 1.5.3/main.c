#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animação 1.5.3 (clique)!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200,100,SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    /* EXECUÇÃO */
    int espera = 500;
    int go = 1;
    int open = 1;
    int xpacman = 40;
    int xf1 = 90;
    int xf2 = 115;
    int xf3 = 140;
    int xf4 = 165;
    
    while (xpacman < 210) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

        if (open) {
            filledPieRGBA(ren, xpacman,50, 30, 40,300, 242, 230, 61, 255); //pacman//
        } else {
            filledPieRGBA(ren, xpacman,50, 30, 0,359, 242, 230, 61, 255); //pacman//
        }
        
        filledEllipseRGBA(ren, xf1,50, 7,10, 255, 22, 0, 255); //fantasminha vermelho//
        filledEllipseRGBA(ren, xf2,50, 7,10, 0, 255, 234, 255); //fantasminha ciano//
        filledEllipseRGBA(ren, xf3,50, 7,10, 255, 201, 251, 255); //fantasminha rosa//
        filledEllipseRGBA(ren, xf4,50, 7,10, 255, 153, 0, 255); //fantasminha laranja//
        SDL_RenderPresent(ren);
        
        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_MOUSEBUTTONDOWN) {
                go = !go;
                }
        } else {
            if (go) {
            SDL_Delay(200);
            open = !open;
            xpacman += 2;
            xf1 += 2;
            xf2 += 2;
            xf3 += 2;
            xf4 += 2;
            } else {
                SDL_Delay(2000);
                go = 1;
                 }
          }
                         
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
