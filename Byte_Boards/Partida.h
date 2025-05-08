#pragma once
#include "Tablero.h"

class Oponente; // Para evitar loop infinito de includes

using namespace std;

class Partida {
private:
    Tablero tablero;
    char turno_actual; // 'B' o 'N'

    friend class Oponente;
public:
    Partida(int altura = 8, int largura = 8);

    void dibujar_terminal();
    void mover_terminal();
    void alternar_turno();
    char ver_turno() const;
    
};