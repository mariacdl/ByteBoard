#include "Peon.h"


char Peon::ver_tipo() const { 
	return 'P'; 
}

bool Peon::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
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

	int direccion = (ver_color() == 'B') ? -1 : 1;
	int fila_inicial = (ver_color() == 'B') ? tablero.ver_largo() - 2 : 1;

	// Movimiento simple hacia adelante
	if (dx == 0 && dy == direccion && destino->ver_tipo() == '0') return true;

	// Movimiento doble desde la fila inicial
	if (dx == 0 && dy == 2 * direccion && de_y == fila_inicial && destino->ver_tipo() == '0' && tablero.ver_modalidad() == 'P') {
		// Verificar que la celda intermedia tambien esta vacia
		int y_intermedia = de_y + direccion;
		if (tablero.ver_pieza(de_x, y_intermedia)->ver_tipo() == '0')
			return true;
	}

	// Captura en diagonal
	if (abs(dx) == 1 && dy == direccion && destino->ver_tipo() != '0') {
		return true;
	}

	// Captura al paso
	if (abs(dx) == 1 && dy == direccion && destino->ver_tipo() == '0') {
		// La casilla al lado donde debe estar el peón que se puede capturar al paso
		int peon_x = para_x;
		int peon_y = para_y - direccion;

		Pieza* posible_peon = tablero.ver_pieza(peon_x, peon_y);

		// Verifica si hay un peón enemigo elegible para en passant
		if (posible_peon != nullptr &&
			posible_peon->ver_tipo() == 'P' &&
			posible_peon->ver_color() != this->ver_color() &&
			posible_peon->ver_numero_movimientos() == 1) { // Debe haberse movido exactamente una vez

			// Asegurarse que el peón avanzó 2 casillas desde su posición inicial
			int fila_inicial = (posible_peon->ver_color() == 'B') ? tablero.ver_largo() - 2 : 1;
			if (peon_y == fila_inicial + 2 * ((posible_peon->ver_color() == 'B') ? -1 : 1)) {
				return true; // En passant válido
			}
		}
	}
	return true;
}