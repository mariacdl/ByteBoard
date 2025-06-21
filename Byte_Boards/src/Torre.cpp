#include "Torre.h"

char Torre::ver_tipo() const {
	return 'T';
}

bool Torre::validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(para); // first = y, second = x

	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	// Verificar si el movimiento está dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura())
		return false;

	// Verificar si no hay movimiento
	if (delta_x == 0 && delta_y == 0)
		return false;

	// Verificar si intenta capturar su propio rey
	if (destino != nullptr && destino->ver_tipo() == 'R' && destino->ver_color() == color)
		return false;

	// Verificar si el movimiento es solo en línea recta (horizontal o vertical)
	if (delta_x != 0 && delta_y != 0)
		return false;

	// Verificar si hay piezas en el camino
	if (delta_x == 0) { // Movimiento vertical
		int paso = (delta_y > 0) ? 1 : -1;
		for (int y = desde_y + paso; y != para_y; y += paso) {
			if (tablero.ver_pieza(make_pair(y, desde_x)) != nullptr)
				return false;
		}
	}
	else { // Movimiento horizontal
		int paso = (delta_x > 0) ? 1 : -1;
		for (int x = desde_x + paso; x != para_x; x += paso) {
			if (tablero.ver_pieza(make_pair(desde_y, x)) != nullptr)
				return false;
		}
	}

	// Verificar si hay una pieza aliada en el destino
	if (destino != nullptr && destino->ver_color() == color)
		return false;

	// Movimiento válido
	return true;
}
