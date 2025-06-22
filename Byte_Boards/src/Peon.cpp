#include "Peon.h"

char Peon::ver_tipo() const {
	return 'P';
}

bool Peon::validar_movimiento(pair<int, int> desde, pair<int, int> para, const Tablero& tablero, bool jaque) const {
	Pieza* destino = tablero.ver_pieza(para);

	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	int direccion = (color == BLANCO) ? -1 : 1;
	int fila_inicial = (color == BLANCO) ? tablero.ver_altura() - 2 : 1;

	// Verificar límites del tablero
	if (para_x < 0 || para_x >= tablero.ver_largura() || para_y < 0 || para_y >= tablero.ver_altura())
		return false;

	// Sin movimiento
	if (delta_x == 0 && delta_y == 0)
		return false;

	// Verificar si casilla esta ocupada
	if (destino != nullptr) {
		// No se puede capturar al rey enemigo
		// A menos que sea para verificar jaque
		if (destino->ver_tipo() == 'R')
			return jaque;

		// No se puede capturar una pieza del mismo color
		if (destino->ver_color() == color)
			return false;
	}

	// Avance simple (una casilla hacia adelante, casilla libre)
	if (delta_x == 0 && delta_y == direccion && destino == nullptr)
		return true;

	// Avance doble (desde la fila inicial, ambas casillas deben estar libres)
	if (validar_avance_doble(desde, para, tablero))
		return true;

	// Captura diagonal (una casilla en diagonal, hay enemigo presente)
	if (abs(delta_x) == 1 && delta_y == direccion && destino != nullptr)
		return true;

	// En passant
	if (validar_en_passant(desde, para, tablero))
		return true;

	return false;
}


bool Peon::validar_avance_doble(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(para);

	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	int direccion = (color == BLANCO) ? -1 : 1;
	int fila_inicial = (color == BLANCO) ? tablero.ver_altura() - 2 : 1;

	if (delta_x == 0 && delta_y == 2 * direccion && desde_y == fila_inicial && destino == nullptr) {
		// Casilla intermedia libre
		if (tablero.ver_pieza(make_pair(desde_y + direccion, desde_x)) == nullptr)
			return true;
	}
	return false;
}

bool Peon::validar_en_passant(pair<int, int> desde, pair<int, int> para, const Tablero& tablero) const {
	int desde_y = desde.first;
	int desde_x = desde.second;
	int para_y = para.first;
	int para_x = para.second;

	int delta_x = para_x - desde_x;
	int delta_y = para_y - desde_y;

	int direccion = (color == BLANCO) ? -1 : 1;

	Pieza* destino = tablero.ver_pieza(para);

	if (abs(delta_x) == 1 && delta_y == direccion && destino == nullptr) {
		int peon_y = desde_y;
		int peon_x = para_x;

		Pieza* posible_peon = tablero.ver_pieza(make_pair(peon_y, peon_x));

		if (posible_peon != nullptr &&
			posible_peon->ver_tipo() == 'P' &&
			posible_peon->ver_color() != color &&
			posible_peon->ver_numero_movimientos() == 1) {

			int fila_ini_peon = (posible_peon->ver_color() == BLANCO) ? tablero.ver_altura() - 2 : 1;
			int esperado_y = fila_ini_peon + 2 * ((posible_peon->ver_color() == BLANCO) ? -1 : 1);

			if (peon_y == esperado_y)
				return true;
		}
	}
	return false;
}
