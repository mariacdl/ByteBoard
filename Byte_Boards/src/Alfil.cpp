#include "Alfil.h"

char Alfil::ver_tipo() const {
	return 'A';
}

bool Alfil::validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero, bool determinar_jaque) const {
	Pieza* destino = tablero.ver_pieza(para); // Puede ser nullptr (casilla vacía)

	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	// Verificar si el movimiento está dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura())
		return false;

	// Verificar si el movimiento es para la misma casilla
	if (para_x == desde_x && para_y == desde_y)
		return false;

	// Verificar si el movimiento es diagonal
	if (abs(delta_x) != abs(delta_y))
		return false;

	// Verificar si hay obstáculos en la diagonal
	int paso_x = delta_x / abs(delta_x);
	int paso_y = delta_y / abs(delta_y);
	int x = desde_x + paso_x;
	int y = desde_y + paso_y;
	while (x != para_x && y != para_y) {
		if (tablero.ver_pieza(make_pair(y, x)) != nullptr)
			return false; // Hay una pieza en el camino
		x += paso_x;
		y += paso_y;
	}

	// Verificar si casilla esta ocupada
	if (destino != nullptr) {
		// No se puede capturar una pieza del mismo color
		//if (destino->ver_color() == color)
		//	return false;

		// Si es el rey enemigo:
		if (destino->ver_tipo() == 'R')
			return determinar_jaque;
	}

	return true;
}
