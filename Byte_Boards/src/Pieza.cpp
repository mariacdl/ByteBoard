#include "Pieza.h"

using namespace std;

Pieza::Pieza(char tipo, char color, int numero_movimiento) {
	this->tipo = tipo;
	this->color = color;
	this->numero_movimiento=numero_movimiento;
}

int Pieza::ver_numero_movimiento(){
	return numero_movimiento;
}

char Pieza::ver_tipo() {
	return tipo;
}

char Pieza::ver_color() {
	return color;
}
