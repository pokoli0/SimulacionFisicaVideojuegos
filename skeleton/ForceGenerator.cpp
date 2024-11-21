#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(float dur)
    : duration(dur), alive(true)  // Marca como vivo al inicio
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
