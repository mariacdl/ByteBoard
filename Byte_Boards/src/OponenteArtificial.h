#pragma once
#include <vector>
#include <utility>
#include <Estados.h>
#include "Tablero.h"

using namespace std;

class OponenteArtificial {
    EstadoTurno color;
    float temperatura;

public:
    OponenteArtificial(EstadoTurno color = NEGRO, float temperatura = 1.0f) : color(color), temperatura(temperatura) {}

    EstadoTurno ver_color() const;

    int puntuar_jugada(Tablero& tablero, pair<int, int> origen, pair<int, int> destino);
    pair<pair<int, int>, pair<int, int>> elegir_proxima_jugada(Tablero& tablero);
};