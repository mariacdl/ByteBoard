#include "Caballo.h"


char Caballo::ver_tipo() const {
	return 'C';
}

bool Caballo::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(make_pair(para_x, para_y)); // Hipotetico, puede estar libre

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento esta dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura()) 
		return false;
	
	// Verificar si movimiento es para la misma casilla
	if (para_x == de_x && para_y == de_y) 
		return false;

	// Verificar si movimiento es en L
	if (!((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)))
		return false;
	
	// Casilla ocupada
	if(destino != nullptr) {
		// Verificar si en la posición final se encuentra el rey
		// No es posible matar al rey
		if (destino->ver_tipo() == 'R') 
			return false;

		// Verificar si hay aliado
		if (destino->ver_color() == color) {
			return false; // No puede capturar pieza aliada
		}
	}

	return true;
}