#pragma once
#include "Tablero.h"

class Pieza {
protected:
    char color; // 'B' o 'N'
    int numero_movimientos;

public:
    Pieza(char c,int n = 0) : color(color), numero_movimientos(n) {};
    virtual ~Pieza() {}

    char ver_color() const;
    int ver_numero_movimientos() const;
    void incrementar_movimiento();

    virtual char ver_tipo() const = 0; // 'P', 'T', etc
    virtual bool validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero & tablero) const = 0;
};