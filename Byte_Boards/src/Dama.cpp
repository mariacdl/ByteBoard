#include "Dama.h"


char Dama::ver_tipo() const {
	return 'D';
}

bool Dama::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* empiece = tablero.ver_pieza(de_x, de_y);
	Pieza* destino = tablero.ver_pieza(para_x, para_y); // Hipotetico, puede estar libre

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento esta dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_ancho() || para_y < 0 || para_y >= tablero.ver_largo()) 
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
		if (tablero.ver_pieza(x, y) != nullptr) return false;
		x += paso_x;
		y += paso_y;
	}

	// Casilla ocupada
	if (destino != nullptr) {
		//Verificar si en la posición final se encuentra el rey
		// No es posible matar al rey
		if (destino->ver_tipo() == 'R' && destino->ver_color() == empiece->ver_color())
			return false;
	}
	
	return true;
}