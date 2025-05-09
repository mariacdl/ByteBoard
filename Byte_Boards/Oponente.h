#pragma once
#include <vector>
#include <utility>
#include "Tablero.h"

using namespace std;

class Oponente {
    char color;
    float temperatura; // Parámetro para IA futura

public:
    Oponente(char color, float temperatura = 1.0f) : color(color), temperatura(temperatura) {}

    int puntuar_jugada(Tablero& tablero, pair<int, int> origen, pair<int, int> destino);
    pair<pair<int, int>, pair<int, int>> elegir_proxima_jugada(Tablero& tablero);
};
