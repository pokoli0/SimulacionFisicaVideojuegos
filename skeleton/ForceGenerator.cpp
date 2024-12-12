#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(float dur, ForceType t)
    : duration(dur), alive(true), type(t)
{
    if (duration <= 0.0f) {
        alive = true;  // Fuerza infinita, siempre viva
    }
    else {
        alive = true;  // Fuerza activa al principio
    }
}

ForceGenerator::~ForceGenerator()
{
}
