#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
  
    Uint32 start = SDL_GetTicks();

    int resultado = SDL_WaitEventTimeout(evt, *ms);

    Uint32 finish = SDL_GetTicks();
    
    Uint32 tempo_decorrido = finish - start;
  
    if (*ms > tempo_decorrido) {
        *ms -= tempo_decorrido;
    } else {
        *ms = 0; 
    }
    
    return resultado;
}

int main (int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Windown* win = SDL_CreateWindow("Click, Drag and Drop (or Not!)",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Rect harbe = {365,265, 70,70};
    SDL_Point lembrar;

    int state = 0;
    int idle = 1;
    int drag = 2;
    int waiting = 3;
    

    SDL_Point centralizar;

    int running = 1;
    SDL_Event evt;

    while (running) {
        Uint32 timeout = 250;

        if (AUX_WaitEventTimeoutCount(&evt, &timeout))
            switch (evt.type) {
                
                case SDL_QUIT:
                    running = 0;
                    break;
                
                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_ESCAPE){
                        if (state == waiting || state == idle) {
                            harbe.x = lembrar.x;
                            harbe.y = lembrar.y;
                            state = idle;
                            printf("ESC pressionado = Drag cancelado");
                        }                                         
                    }
                    break;
                
                case SDL_MOUSE
                }

        }

}
