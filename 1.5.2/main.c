#include <SDL2/SDL.h>

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
