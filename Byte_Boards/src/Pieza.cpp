#include "Pieza.h"


int Pieza::ver_numero_movimientos() const {
	return numero_movimientos;
}

EstadoTurno Pieza::ver_color() const {
	return color;
}

void Pieza::incrementar_movimiento() { numero_movimientos++; }