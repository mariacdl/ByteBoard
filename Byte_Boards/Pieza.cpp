#include "Pieza.h"

using namespace std;

Pieza::Pieza(char tipo, char color) {
	this->tipo = tipo;
	this->color = color;
}

char Pieza::ver_tipo() {
	return tipo;
}

char Pieza::ver_color() {
	return color;
}

