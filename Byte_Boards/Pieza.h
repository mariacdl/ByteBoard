#pragma once

class Pieza {
	char tipo, color;

public:
	Pieza() : tipo('0'), color('0') {}
	Pieza(char tipo, char color);
	char ver_tipo();
	char ver_color();
};