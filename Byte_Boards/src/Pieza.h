#pragma once

class Pieza {
	char tipo, color;
	int numero_movimiento; // Para "Enroque" del rey

public:
	Pieza() : tipo('0'), color('0'), numero_movimiento(0) {}
	Pieza(char tipo, char color, int numero_movimiento);
	int ver_numero_movimiento();
	char ver_tipo();
	char ver_color();
};