#include "Rey.h"


char Rey::ver_tipo() const {
	return 'R';
}

bool Rey::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* empiece = tablero.ver_pieza(de_x, de_y);
	Pieza* destino = tablero.ver_pieza(para_x, para_y); // Hipotetico, puede estar libre

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento es para la misma casilla
	if (para_x == de_x && para_y == de_y) 
		return false;

	// Verificar si movimiento esta dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_ancho() || para_y < 0 || para_y >= tablero.ver_largo()) 
		return false;

	// Verificar si movimiento es valido para la pieza
	if (abs(dx) > 1 || abs(dy) > 1)
		return false;

	// Verificar si enroque es posible
	if (verificar_enroque(de_x, de_y, para_x, para_y, tablero))
		return true;

	// Casilla ocupada
	if (destino != nullptr) {
		// Verificar si en la posición final se encuentra el rey
		// No es posible matar al rey
		if (destino->ver_tipo() == 'R' && destino->ver_color() == empiece->ver_color())
			return false;
	}

	return true;
}

bool Rey::verificar_enroque(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* empiece = tablero.ver_pieza(de_x, de_y);

	// Enroque lado izquierdo
	if (para_x == de_x - 2) {
		// Verificar si hay piezas en el camino del rey
		if (tablero.ver_pieza(de_x - 1, de_y) != nullptr || tablero.ver_pieza(de_x - 2, de_y) != nullptr)
			return false;

		// Enroque corto
		Pieza* torre = tablero.ver_pieza(de_x - 3, de_y);
		if (torre != nullptr) {
			bool es_torre_aliada = torre && torre->ver_tipo() == 'T' && torre->ver_color() == empiece->ver_color();
			if (es_torre_aliada)
				return true;
		}

		// Enroque largo
		torre = tablero.ver_pieza(de_x - 4, de_y);
		if (torre != nullptr) {
			bool es_torre_aliada = torre && torre->ver_tipo() == 'T' && torre->ver_color() == empiece->ver_color();
			if (es_torre_aliada && tablero.ver_pieza(de_x - 3, de_y) == nullptr)
				return true;
		}
	}

	// Enroque lado izquierdo
	if (para_x == de_x + 2) {
		// Verificar si hay piezas en el camino del rey
		if (tablero.ver_pieza(de_x + 1, de_y) != nullptr || tablero.ver_pieza(de_x + 2, de_y) != nullptr)
			return false;

		// Enroque corto
		Pieza* torre = tablero.ver_pieza(de_x + 3, de_y);
		if (torre != nullptr) {
			bool es_torre_aliada = torre && torre->ver_tipo() == 'T' && torre->ver_color() == empiece->ver_color();
			if (es_torre_aliada)
				return true;
		}

		// Enroque largo
		torre = tablero.ver_pieza(de_x + 4, de_y);
		if (torre != nullptr) {
			bool es_torre_aliada = torre && torre->ver_tipo() == 'T' && torre->ver_color() == empiece->ver_color();
			if (es_torre_aliada && tablero.ver_pieza(de_x + 3, de_y) == nullptr)
				return true;
		}
	}
	return false;
}