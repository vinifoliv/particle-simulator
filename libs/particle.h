#ifndef PARTICLE_H
#define PARTICLE_H

/// @brief Struct defining a particle with its current position and velocity values
typedef struct {
    float x, y;
    float vx, vy;
    int color;
} Particle;

#endif