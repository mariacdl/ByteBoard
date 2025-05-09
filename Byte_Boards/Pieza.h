#pragma once

class Pieza {
	char tipo, color;
	int numero_movimiento = 0; // Para "En passant" del peon y "Enroque" del rey

public:
	Pieza() : tipo('0'), color('0') {}
	Pieza(char tipo, char color);
	char ver_tipo();
	char ver_color();
};