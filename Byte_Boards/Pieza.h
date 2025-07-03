#pragma once
#include "Tablero.h"
#include <Estados.h>
#include <utility>

using namespace std;


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
    virtual bool validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero & tablero, bool determinar_jaque = false) const = 0;

    virtual Pieza* clonar() const = 0;
};