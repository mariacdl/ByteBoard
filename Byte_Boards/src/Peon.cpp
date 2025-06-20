#include "Peon.h"


char Peon::ver_tipo() const {
	return 'P'; 
}

bool Peon::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(para_x, para_y);

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Definir dirección de movimiento según color
	int direccion = (ver_color() == 'B') ? -1 : 1;
	int fila_inicial = (ver_color() == 'B') ? tablero.ver_largo() - 2 : 1;

	// Verificar si movimiento está dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_ancho() || para_y < 0 || para_y >= tablero.ver_largo())
		return false;

	// Verificar si no hay movimiento
	if (para_x == de_x && para_y == de_y)
		return false;

	// Verificar si intenta capturar su propio rey
	if (destino != nullptr && destino->ver_tipo() == 'R' && destino->ver_color() == color)
		return false;

	// Movimiento de avance simple
	if (dx == 0 && dy == direccion && destino == nullptr)
		return true;

	// Movimiento de avance doble desde la fila inicial
	if (dx == 0 && dy == 2 * direccion && de_y == fila_inicial && destino == nullptr) {
		int y_intermedia = de_y + direccion;
		if (tablero.ver_pieza(de_x, y_intermedia) == nullptr)
			return true;
	}

	// Movimiento de captura normal (diagonal)
	if (abs(dx) == 1 && dy == direccion && destino != nullptr && destino->ver_color() != color)
		return true;

	// Movimiento especial: en passant
	if (abs(dx) == 1 && dy == direccion && destino == nullptr) {
		int peon_x = para_x;
		int peon_y = para_y - direccion;

		Pieza* posible_peon = tablero.ver_pieza(peon_x, peon_y);

		if (posible_peon != nullptr &&
			posible_peon->ver_tipo() == 'P' &&
			posible_peon->ver_color() != color &&
			posible_peon->ver_numero_movimientos() == 1) {

			// Verificar si el peón rival hizo un movimiento doble desde su fila inicial
			int fila_ini_peon = (posible_peon->ver_color() == 'B') ? tablero.ver_largo() - 2 : 1;
			if (peon_y == fila_ini_peon + 2 * ((posible_peon->ver_color() == 'B') ? -1 : 1))
				return true;
		}
	}

	// Movimiento inválido
	return false;
}