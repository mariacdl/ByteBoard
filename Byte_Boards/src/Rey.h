#pragma once
#include "Pieza.h"
#include "Tablero.h"

class Rey : public Pieza {

public:
	Rey(EstadoTurno c, int n = 0) : Pieza(c, n) {};

	char ver_tipo() const;
	bool validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const override;
	bool verificar_enroque(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const;
};