﻿#include "Peon.h"

char Peon::ver_tipo() const {
	return 'P';
}

bool Peon::validar_movimiento(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(make_pair(para_y, para_x));

	int dy = para_x - de_x; // invertido
	int dx = para_y - de_y; // invertido

	// Definir dirección de movimiento según color
	int direccion = (color == 'B') ? -1 : 1;
	int fila_inicial = (color == 'B') ? tablero.ver_altura() - 2 : 1;

	// Verificar si movimiento está dentro del tablero
	if (para_y < 0 || para_y >= tablero.ver_largura() || para_x < 0 || para_x >= tablero.ver_altura())
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
	if (validar_avance_doble(de_x, de_y, para_x, para_y, tablero))
		return true;

	// Movimiento de captura normal (diagonal)
	if (abs(dx) == 1 && dy == direccion && destino != nullptr && destino->ver_color() != color)
		return true;

	// Validar en passant
	if (validar_en_passant(de_x, de_y, para_x, para_y, tablero))
		return true;

	// Movimiento inválido
	return false;
}

bool Peon::validar_avance_doble(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(make_pair(para_y, para_x));
	int direccion = (color == 'B') ? -1 : 1;
	int fila_inicial = (color == 'B') ? tablero.ver_altura() - 2 : 1;

	int dy = para_x - de_x; // invertido
	int dx = para_y - de_y; // invertido

	if (dx == 0 && dy == 2 * direccion && de_x == fila_inicial && destino == nullptr) {
		int x_intermedia = de_x + direccion;
		if (tablero.ver_pieza(make_pair(de_y, x_intermedia)) == nullptr)
			return true;
	}
	return false;
}

bool Peon::validar_en_passant(int de_x, int de_y, int para_x, int para_y, const Tablero& tablero) const {
	Pieza* destino = tablero.ver_pieza(make_pair(para_y, para_x));
	int direccion = (color == 'B') ? -1 : 1;

	int dy = para_x - de_x; // invertido
	int dx = para_y - de_y; // invertido

	if (abs(dx) == 1 && dy == direccion && destino == nullptr) {
		int peon_x = para_x - direccion;
		int peon_y = para_y;

		Pieza* posible_peon = tablero.ver_pieza(make_pair(peon_y, peon_x));

		if (posible_peon != nullptr &&
			posible_peon->ver_tipo() == 'P' &&
			posible_peon->ver_color() != color &&
			posible_peon->ver_numero_movimientos() == 1) {

			// Verificar si el peón rival hizo un movimiento doble desde su fila inicial
			int fila_ini_peon = (posible_peon->ver_color() == 'B') ? tablero.ver_altura() - 2 : 1;
			if (peon_x == fila_ini_peon + 2 * ((posible_peon->ver_color() == 'B') ? -1 : 1))
				return true;
		}
	}
	return false;
}
