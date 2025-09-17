#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Corrida",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         100, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    int running = 1;
    int espera = 500;
    
    SDL_Rect rTempo = { 20,20, 10,10 };
    SDL_Rect rTeclado = { 20,40, 10,10 };
    SDL_Rect rMouse = { 20,60, 10,10 };
    SDL_Rect chegada = { 170,0, 10,100 };
           
    SDL_Event evt;
  
    int windowWidth, windowHeight;
    SDL_GetWindowSize(win, &windowWidth, &windowHeight);
    
    while (running) {
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xfc,0xba,0x03,0x00);
        SDL_RenderFillRect(ren, &rTempo);
        SDL_SetRenderDrawColor(ren, 0x07,0xfc,0x03,0x00);
        SDL_RenderFillRect(ren, &rTeclado);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &rMouse);
        SDL_SetRenderDrawColor(ren, 0xeb,0x40,0x34,0x00);
        SDL_RenderFillRect(ren, &chegada);
        
        SDL_RenderPresent(ren);
        
        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        rTeclado.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        rTeclado.x += 5;
                        break;
                    case SDLK_F4:
                        if (evt.key.keysym.mod & KMOD_ALT){
                        running = 0;
                        }
                        break;
                }
              if (rTeclado.x < 0) {
                  rTeclado.x = 0;
              }
              if (rTeclado.x + rTeclado.w > chegada.x) {
                  rTeclado.x = chegada.x - rTeclado.w;
              }
            }
            else if (evt.type == SDL_QUIT){
                running = 0;
            }
            else if (evt.type == SDL_MOUSEMOTION){
                rMouse.x = evt.motion.x - rMouse.w/2;
                if (rMouse.x + rMouse.w > chegada.x) {
                  rMouse.x = chegada.x - rMouse.w;
                } 
            }     
        }
        else if (!isevt) {
                rTempo.x += 5;
                espera = 500;
                if (rTempo.x + rTempo.w > chegada.x) {
                  rTempo.x = chegada.x - rTempo.w;
                }
        }
 
}
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void resetCorrida(SDL_Rect* rTempo, SDL_Rect* rTeclado, SDL_Rect* rMouse, SDL_Texture** text);

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("Corrida!",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    TTF_Font* fnt = TTF_OpenFont("tiny.ttf", 20);
    assert(fnt != NULL);
    SDL_Color cor = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Texture* text = NULL;
    
    SDL_Surface* sfcReset = TTF_RenderText_Blended(fnt, "R to Reset", cor);
    SDL_Texture* textReset = SDL_CreateTextureFromSurface(ren, sfcReset);
    SDL_FreeSurface(sfcReset);

    
    SDL_Rect destinoTexto = {10,10, 100,100};
    SDL_Rect destinoReset = {10,80, sfcReset->w,sfcReset->h};
    
    /* EXECUÇÃO */
    
    int running = 1;
    int espera = 500;
    
    SDL_Rect rTempo = { 20,20, 10,10 };
    SDL_Rect rTeclado = { 20,40, 10,10 };
    SDL_Rect rMouse = { 20,60, 10,10 };
    SDL_Rect chegada = { 180,0, 10,100 };
           
    SDL_Event evt;
  
    int windowWidth, windowHeight;
    SDL_GetWindowSize(win, &windowWidth, &windowHeight);
    
    while (running) {
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xfc,0xba,0x03,0x00);
        SDL_RenderFillRect(ren, &rTempo);
        SDL_SetRenderDrawColor(ren, 0x07,0xfc,0x03,0x00);
        SDL_RenderFillRect(ren, &rTeclado);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &rMouse);
        SDL_SetRenderDrawColor(ren, 0xeb,0x40,0x34,0x00);
        SDL_RenderFillRect(ren, &chegada);
        if (text != NULL) {
        SDL_RenderCopy(ren, text, NULL, &destinoTexto);
        }
        SDL_RenderCopy(ren, textReset, NULL, &destinoReset);
        SDL_RenderPresent(ren);
        
        SDL_Event evt;
        Uint32 antes = SDL_GetTicks();
        int isevt = SDL_WaitEventTimeout(&evt, espera);
        if (isevt) {
            espera -= (SDL_GetTicks() - antes);
            if (espera < 0) {
                espera = 0;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        rTeclado.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        rTeclado.x += 5;
                        break;
                    case SDLK_r:
                        resetCorrida(&rTempo, &rTeclado, &rMouse, &text);
                        break;
                    case SDLK_F4:
                        if (evt.key.keysym.mod & KMOD_ALT){
                        running = 0;
                        }
                        break;
                }
              if (rTeclado.x < 0) {
                  rTeclado.x = 0;
              }
              if (rTeclado.x + rTeclado.w > chegada.x) {
                  rTeclado.x = chegada.x - rTeclado.w;
                  if (text != NULL) {
                      SDL_DestroyTexture(text);
                  }
                  SDL_Surface* sfc = TTF_RenderText_Blended(fnt, "Teclado Venceu!!", cor);
                  if (sfc != NULL) {
                    text = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_FreeSurface(sfc);
                    // Ajusta o tamanho do destino do texto
                    destinoTexto.w = sfc->w;
                    destinoTexto.h = sfc->h;
                  }
              }
            }
            else if (evt.type == SDL_QUIT){
                running = 0;
            }
            else if (evt.type == SDL_MOUSEMOTION){
                rMouse.x = evt.motion.x - rMouse.w/2;
                if (rMouse.x + rMouse.w > chegada.x) {
                  rMouse.x = chegada.x - rMouse.w;
                  if (text != NULL) {
                      SDL_DestroyTexture(text);
                  }
                  SDL_Surface* sfc = TTF_RenderText_Blended(fnt, "Mouse Venceu!!", cor);
                  if (sfc != NULL) {
                    text = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_FreeSurface(sfc);
                    // Ajusta o tamanho do destino do texto
                    destinoTexto.w = sfc->w;
                    destinoTexto.h = sfc->h;
                  }
                } 
            }     
        }
        else if (!isevt) {
                rTempo.x += 5;
                espera = 500;
                if (rTempo.x + rTempo.w > chegada.x) {
                  rTempo.x = chegada.x - rTempo.w;
                  if (text != NULL) {
                      SDL_DestroyTexture(text);
                  }
                  SDL_Surface* sfc = TTF_RenderText_Blended(fnt, "Tempo Venceu?!", cor);
                  if (sfc != NULL) {
                    text = SDL_CreateTextureFromSurface(ren, sfc);
                    SDL_FreeSurface(sfc);
                    // Ajusta o tamanho do destino do texto
                    destinoTexto.w = sfc->w;
                    destinoTexto.h = sfc->h;
                  }
                }
        }
 
}
    /* FINALIZACAO */
    if (text != NULL) {
    SDL_DestroyTexture(text);
    }
    TTF_CloseFont(fnt);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

//função resetCorrida

void resetCorrida(SDL_Rect* rTempo, SDL_Rect* rTeclado, SDL_Rect* rMouse, SDL_Texture** text) {
    rTempo->x = 20;
    rTeclado->x = 20;
    rMouse->x = 20;

    if (*text != NULL) {
        SDL_DestroyTexture(*text);
        *text = NULL;
    }
}
