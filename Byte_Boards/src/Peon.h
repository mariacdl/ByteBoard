#pragma once
#include "Pieza.h"
#include "Tablero.h"
#include <utility>

using namespace std;

class Peon : public Pieza {

public:
	Peon(EstadoTurno c, int n = 0) : Pieza(c, n) {};

	char ver_tipo() const;
	bool validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero, bool jaque = false) const override;
	bool validar_avance_doble(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const;
	bool validar_en_passant(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const;
};