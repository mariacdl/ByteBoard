#include "Caballo.h"

char Caballo::ver_tipo() const {
	return 'C';
}

bool Caballo::validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(para); // Recordar: first = y, second = x

	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	// Verificar si el movimiento está dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura())
		return false;

	// Verificar si es la misma casilla
	if (para_x == desde_x && para_y == desde_y)
		return false;

	// Verificar si es un movimiento en L
	if (!((abs(delta_x) == 2 && abs(delta_y) == 1) || (abs(delta_x) == 1 && abs(delta_y) == 2)))
		return false;

	// Si la casilla está ocupada...
	if (destino != nullptr) {
		// No se puede capturar al rey enemigo
		if (destino->ver_tipo() == 'R')
			return false;

		// No se puede capturar pieza aliada
		if (destino->ver_color() == color)
			return false;
	}

	return true;
}
