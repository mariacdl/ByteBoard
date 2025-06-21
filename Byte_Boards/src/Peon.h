#pragma once
#include "Pieza.h"
#include "Tablero.h"


class Peon : public Pieza {

public:
	Peon(EstadoTurno c, int n = 0) : Pieza(c, n) {};

	char ver_tipo() const;
	bool validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const override;
	bool validar_avance_doble(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const;
	bool validar_en_passant(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const;
};