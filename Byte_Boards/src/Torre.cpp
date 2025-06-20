#include "Torre.h"


char Torre::ver_tipo() const {
	return 'T';
}

bool Torre::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(para_x, para_y);

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento está dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_ancho() || para_y < 0 || para_y >= tablero.ver_largo())
		return false;

	// Verificar si no hay movimiento
	if (para_x == de_x && para_y == de_y)
		return false;

	// Verificar si intenta capturar su propio rey
	if (destino != nullptr && destino->ver_tipo() == 'R' && destino->ver_color() == color)
		return false;

	// Verificar si el movimiento es solo en línea recta (horizontal o vertical)
	if (dx != 0 && dy != 0)
		return false;

	// Verificar si hay piezas en el camino
	if (dx == 0) { // Movimiento vertical
		int paso = (dy > 0) ? 1 : -1;
		for (int y = de_y + paso; y != para_y; y += paso) {
			if (tablero.ver_pieza(de_x, y) != nullptr)
				return false;
		}
	}
	else { // Movimiento horizontal
		int paso = (dx > 0) ? 1 : -1;
		for (int x = de_x + paso; x != para_x; x += paso) {
			if (tablero.ver_pieza(x, de_y) != nullptr)
				return false;
		}
	}

	// Si la casilla de destino contiene una pieza del mismo color, el movimiento es inválido
	if (destino != nullptr && destino->ver_color() == color)
		return false;

	// Movimiento válido
	return true;
}