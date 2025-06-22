#include "Rey.h"

char Rey::ver_tipo() const {
	return 'R';
}

bool Rey::validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero, bool determinar_jaque) const {
	Pieza* destino = tablero.ver_pieza(para); // first = y, second = x

	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	// Verificar si movimiento es para la misma casilla
	if (delta_x == 0 && delta_y == 0)
		return false;

	// Verificar si movimiento está dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura())
		return false;

	// Movimiento válido si es 1 casilla a cualquier dirección
	if (abs(delta_x) > 1 || abs(delta_y) > 1) {
		// Verificar si enroque es posible
		if (!verificar_enroque(desde, para, tablero) && numero_movimientos == 0)
			return false;
	}

	// Verificar si casilla esta ocupada
	if (destino != nullptr) {
		// No se puede capturar una pieza del mismo color
		if (destino->ver_color() == color)
			return false;

		// Si es el rey enemigo:
		if (destino->ver_tipo() == 'R')
			return determinar_jaque;
	}

	return true;
}

bool Rey::verificar_enroque(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const {
	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	// Enroque hacia la izquierda
	if (para_x == desde_x - 2 && para_y == desde_y) {
		// Verificar si hay piezas entre el rey y la torre
		if (tablero.ver_pieza(make_pair(desde_y, desde_x - 1)) != nullptr ||
			tablero.ver_pieza(make_pair(desde_y, desde_x - 2)) != nullptr)
			return false;

		// Enroque corto
		Pieza* torre = tablero.ver_pieza(make_pair(desde_y, desde_x - 3));
		if (torre != nullptr && torre->ver_tipo() == 'T' && torre->ver_color() == color)
			return true;

		// Enroque largo
		torre = tablero.ver_pieza(make_pair(desde_y, desde_x - 4));
		if (torre != nullptr && torre->ver_tipo() == 'T' && torre->ver_color() == color &&
			tablero.ver_pieza(make_pair(desde_y, desde_x - 3)) == nullptr)
			return true;
	}

	// Enroque hacia la derecha
	if (para_x == desde_x + 2 && para_y == desde_y) {
		if (tablero.ver_pieza(make_pair(desde_y, desde_x + 1)) != nullptr ||
			tablero.ver_pieza(make_pair(desde_y, desde_x + 2)) != nullptr)
			return false;

		// Enroque corto
		Pieza* torre = tablero.ver_pieza(make_pair(desde_y, desde_x + 3));
		if (torre != nullptr && torre->ver_tipo() == 'T' && torre->ver_color() == color)
			return true;

		// Enroque largo
		torre = tablero.ver_pieza(make_pair(desde_y, desde_x + 4));
		if (torre != nullptr && torre->ver_tipo() == 'T' && torre->ver_color() == color &&
			tablero.ver_pieza(make_pair(desde_y, desde_x + 3)) == nullptr)
			return true;
	}

	return false;
}
