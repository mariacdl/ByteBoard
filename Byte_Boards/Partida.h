#pragma once
#include "Tablero.h"

class Partida {
private:
    Tablero tablero;
    char turno_actual; // 'B' ou 'N'

public:
    Partida(int altura = 8, int largura = 8);

    void dibujar_terminal();
    void mover_terminal();
    void alternar_turno();
    char ver_turno() const;
};