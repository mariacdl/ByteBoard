#pragma once
#include "Tablero.h"
#include <Estados.h>


class Pieza {
protected:
    EstadoTurno color; 
    int numero_movimientos;

public:
    Pieza(EstadoTurno c, int n = 0) : color(c), numero_movimientos(n) {};
    virtual ~Pieza() {}

    EstadoTurno ver_color() const;
    int ver_numero_movimientos() const;
    void incrementar_movimiento();

    virtual char ver_tipo() const = 0; // 'P', 'T', etc
    virtual bool validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero & tablero) const = 0;
};