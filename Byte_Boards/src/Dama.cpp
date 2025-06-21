#include "Dama.h"


char Dama::ver_tipo() const {
	return 'D';
}

bool Dama::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(make_pair(para_x, para_y)); // Hipotetico, puede estar libre

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento esta dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura()) 
		return false;
	
	// Verificar si movimiento es para la misma casilla
	if (para_x == de_x && para_y == de_y) 
		return false;

	// Verificar si movimiento es para la misma casilla
	if (!(dx == 0 || dy == 0 || abs(dx) == abs(dy)))
		return false;
	
	// Verificar movimiento en la vertical, horizontal o diagonal
	// Verificar si hay obstaculos en movimiento
	int paso_x = (dx == 0) ? 0 : dx / abs(dx);
	int paso_y = (dy == 0) ? 0 : dy / abs(dy);
	int x = de_x + paso_x;
	int y = de_y + paso_y;
	while (x != para_x || y != para_y) {
		if (tablero.ver_pieza(make_pair(x,y)) != nullptr) return false;
		x += paso_x;
		y += paso_y;
	}

	// Casilla ocupada
	if (destino != nullptr) {
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