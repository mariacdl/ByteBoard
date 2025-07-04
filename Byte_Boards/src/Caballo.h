#pragma once
#include "Pieza.h"
#include "Tablero.h"
#include <utility>

using namespace std;

class Caballo : public Pieza {

public:
	Caballo(EstadoTurno c, int n = 0) : Pieza(c, n) {};

	char ver_tipo() const;
	bool validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero, bool determinar_jaque = false) const override;

	Caballo* clonar() const override { return new Caballo(*this); };
};