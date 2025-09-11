#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    
    int running = 1;
    int espera = 500;
    
    SDL_Rect rTempo = { 20,20, 10,10 };
    SDL_Rect rTeclado = { 40,20, 10,10 };
    SDL_Rect rMouse = { 60,20, 10,10 };
           
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
                    case SDLK_UP:
                        rTeclado.y -= 5;
                        break;
                    case SDLK_DOWN:
                        rTeclado.y += 5;
                        break;
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
              if (rTeclado.y < 0) {
                  rTeclado.y = 0;
              }
              if (rTeclado.x < 0) {
                  rTeclado.x = 0;
              }
              if (rTeclado.y + rTeclado.h > windowHeight) {
                  rTeclado.y = windowHeight - rTeclado.h;
              }
              if (rTeclado.x + rTeclado.w > windowWidth) {
                  rTeclado.x = windowWidth - rTeclado.w;
              }
            }
            else if (evt.type == SDL_QUIT){
                running = 0;
            }
            else if (evt.type == SDL_MOUSEMOTION){
                rMouse.x = evt.motion.x - rMouse.w/2;
                rMouse.y = evt.motion.y - rMouse.h/2;
            }     
        }
        else if (!isevt) {
              if (rTempo.x <= 170) {
                espera = 500;
                rTempo.x += 5;
                rTempo.y += 5;
              }
              else {
              espera = 500;
              rTempo.x -= 5;
              rTempo.y -= 5;
              }
            }
}
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
