#include "Rey.h"


char Rey::ver_tipo() const {
	return 'R';
}

bool Rey::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* empiece = tablero.ver_pieza(de_x, de_y);
	Pieza* destino = tablero.ver_pieza(para_x, para_y); // Hipotetico, puede estar libre

	// Verificar si movimiento esta dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_ancho() || para_y < 0 || para_y >= tablero.ver_largo()) {
		return false;
	}

	//Verificar si en la posición final se encuentra el rey
	if (destino->ver_tipo() == 'R' && destino->ver_color() == empiece->ver_color()) {
		return false;
	}

	// Verificar si movimiento es para la misma casilla
	if (para_x == de_x && para_y == de_y) {
		return false;
	}

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento es valido para la pieza
	if (abs(dx) > 1 || abs(dy) > 1)
		return false;

	return true;
}