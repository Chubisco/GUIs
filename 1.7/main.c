#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Animação Com Sprites!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300,200,SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    SDL_Texture* pac = IMG_LoadTexture(ren, "pacmanSprite.png");
    if (!pac) {
        printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* ghosts = IMG_LoadTexture(ren, "ghostSprites.png");
    if (!ghosts) {
        printf("Erro ao carregar a imagem: %s\n", IMG_GetError());
        return 1;
    }

    /* EXECUÇÃO */
    
    int screenWidth, screenHeight;
    SDL_GetWindowSize(win, &screenWidth, &screenHeight);

    int espera = 200;
    int go = 1;
    int open = 1;
    int ypac = (screenHeight / 2) - (64 / 2); //  64 = altura pacman
    int xpac = 0;
    int yf = (screenHeight / 2) - (32 / 2); //  32 = altura fantasma
    int xf1 = 70;
    int xf2 = xf1+40;
    int xf3 = xf2+40;
    int xf4 = xf3+40;
    
    while (xf1 < 332) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        
        SDL_Rect pacman;
        SDL_Rect RedGhost;
        SDL_Rect PinkGhost;
        SDL_Rect CianGhost;
        SDL_Rect OrangeGhost;
                
        SDL_Rect destinoPac = {xpac,ypac, 64,64};
        SDL_Rect destinoRG = {xf1,yf, 32, 32}; //red ghost
        SDL_Rect destinoCG = {xf2,yf, 32, 32}; //cian ghost
        SDL_Rect destinoPG = {xf3,yf, 32, 32}; //pink ghost
        SDL_Rect destinoOG = {xf4,yf, 32, 32}; //orange ghost
        
        if (open) {
            pacman = (SDL_Rect) {0,0, 64,64};
            RedGhost = (SDL_Rect) {0,0, 32,32};
            PinkGhost = (SDL_Rect) {0,32, 32,32};
            CianGhost = (SDL_Rect) {0,64, 32,32};
            OrangeGhost = (SDL_Rect) {0,98, 32,32};

        } else {
            pacman = (SDL_Rect) {64,0, 64,64};
            RedGhost = (SDL_Rect) {32,0, 32,32};
            PinkGhost = (SDL_Rect) {32,32, 32,32};
            CianGhost = (SDL_Rect) {32,64, 32,32};
            OrangeGhost = (SDL_Rect) {32,98, 32,32};

        }
        
        SDL_RenderCopy(ren, pac, &pacman, &destinoPac);
        SDL_RenderCopy(ren, ghosts, &RedGhost, &destinoRG);
        SDL_RenderCopy(ren, ghosts, &PinkGhost, &destinoPG);
        SDL_RenderCopy(ren, ghosts, &CianGhost, &destinoCG);
        SDL_RenderCopy(ren, ghosts, &OrangeGhost, &destinoOG);
        
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
            else if (evt.type == SDL_QUIT){
                SDL_Quit();
            }
        } else {
            if (go) {
            espera = 400;
            open = !open;
            xpac += 4;
            xf1 += 4;
            xf2 += 4;
            xf3 += 4;
            xf4 += 4;
            } else {
                espera = 2000;
                go = 1;
              }
          }
                         
    }

    /* FINALIZACAO */
    SDL_DestroyTexture(pac);
    SDL_DestroyTexture(ghosts);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    IMG_Quit();
}
