// Requires SDL to be installed: sudo apt-get install libsdl2-dev


#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PARTICLE_COUNT 250
#define PARTICLE_RADIUS 5

typedef struct {
    float x, y;
    float vx, vy;
} Particle;

void move_particles(Particle particles[], int count) {
    for (int i = 0; i < count; i++) {
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;

        // Deflecting
        if (particles[i].x <= PARTICLE_RADIUS 
        || particles[i].x >= SCREEN_WIDTH - PARTICLE_RADIUS)
            particles[i].vx = -particles[i].vx;

        if (particles[i].y <= PARTICLE_RADIUS
        || particles[i].y >= SCREEN_HEIGHT - PARTICLE_RADIUS)
            particles[i].vy = -particles[i].vy;
    }
}

void draw_particles(SDL_Renderer *renderer, Particle particles[], int count) {
    for (int i = 0; i < count; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        for (int w = 0; w < PARTICLE_RADIUS * 2; w++) {
            for (int h = 0; h < PARTICLE_RADIUS * 2; h++) {
                int dx = PARTICLE_RADIUS - w;
                int dy = PARTICLE_RADIUS - h;

                if ((dx * dx + dy * dy) <= (PARTICLE_RADIUS * PARTICLE_RADIUS)) 
                    SDL_RenderDrawPoint(renderer, particles[i].x + dx, particles[i].y + dy);
            }
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Particle Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand(time(NULL));
    Particle particles[PARTICLE_COUNT];

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].x = rand() % SCREEN_WIDTH;
        particles[i].y = rand() % SCREEN_HEIGHT;
        particles[i].vx = ((float)(rand() % 100) / 100.0f) - 0.5f;
        particles[i].vy = ((float)(rand() % 100) / 100.0f) - 0.5f;
    }

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        move_particles(particles, PARTICLE_COUNT);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_particles(renderer, particles, PARTICLE_COUNT);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}