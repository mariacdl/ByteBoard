#pragma once
#include "Pieza.h"
#include "Tablero.h"
#include <utility>

using namespace std;


class Rey : public Pieza {

public:
	Rey(EstadoTurno c, int n = 0) : Pieza(c, n) {};

	char ver_tipo() const;
	bool validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero, bool determinar_jaque = false) const override;
	bool verificar_enroque(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const;

	Rey* clonar() const override { return new Rey(*this); };
};