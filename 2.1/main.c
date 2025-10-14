#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRAVITY 0.5f
#define JUMP_STRENGTH -10.0f
#define DASH_SPEED 20.0f
#define DOUBLE_CLICK_TIME 300  // ms

//eventos de usuário
enum {
    USER_EVENT_DOUBLE_CLICK = SDL_USEREVENT + 1
};

typedef struct {
    float x, y;
    float vx, vy;
    float originalY;
} Square;

int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms)
{
    Uint32 start = SDL_GetTicks();
    int hasEvent = SDL_WaitEventTimeout(evt, *ms);
    Uint32 end = SDL_GetTicks();

    Uint32 elapsed = end - start;
    if (*ms > elapsed)
        *ms -= elapsed;
    else
        *ms = 0;

    return hasEvent;
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    SDL_Window* window = SDL_CreateWindow(
        "SDL_UserEvent - AUX_WaitEventTimeout",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Square sq = {WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 75, 0, 0, WINDOW_HEIGHT - 75};

    Uint32 lastClickTime = 0;
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        SDL_Event e;
        Uint32 timeout = 16;

        // Espera eventos com tempo limitado e atualiza o timeout restante
        while (AUX_WaitEventTimeout(&e, &timeout)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN: {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        Uint32 now = SDL_GetTicks();
                        if (now - lastClickTime < DOUBLE_CLICK_TIME) {
                            // Dispara evento de usuário (clique duplo)
                            SDL_Event userEvent;
                            SDL_zero(userEvent);
                            userEvent.type = USER_EVENT_DOUBLE_CLICK;
                            userEvent.user.code = 0;
                            userEvent.user.data1 = (void*)(intptr_t)e.button.x;
                            userEvent.user.data2 = (void*)(intptr_t)e.button.y;
                            SDL_PushEvent(&userEvent);
                        } else {
                            // Clique simples: pulo
                            sq.vy = JUMP_STRENGTH;
                        }
                        lastClickTime = now;
                    }
                } break;

                case USER_EVENT_DOUBLE_CLICK: {
                    int mouseX = (int)(intptr_t)e.user.data1;
                    // Faz o quadrado dar um dash na direção do mouse
                    if (mouseX > sq.x)
                        sq.vx = DASH_SPEED;
                    else
                        sq.vx = -DASH_SPEED;
                } break;
            }
        }

        // ======= Atualização da física =======
        Uint32 currentTime = SDL_GetTicks();
        float delta = (currentTime - lastTime) / 16.0f; // aproximação (~60 fps)
        lastTime = currentTime;

        sq.vy += GRAVITY * delta;
        sq.y += sq.vy * delta;
        sq.x += sq.vx * delta;

        // Gravidade e chão
        if (sq.y > sq.originalY) {
            sq.y = sq.originalY;
            sq.vy = 0;
        }

        // Reduz a velocidade do dash (fricção)
        sq.vx *= 0.9f;
        if (fabs(sq.vx) < 0.1f)
            sq.vx = 0;

        // ======= Renderização =======
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_Rect rect = {(int)sq.x, (int)sq.y, 50, 50};
        SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
