#include "Tablero.h"
#include "Pieza.h"

using namespace std;

Tablero::Tablero(int ancho,int largo) {
	this->ancho=ancho;
	this->largo=largo;
	lista_piezas.resize(ancho*largo);
}

void Tablero::colocar_pieza(int pos_x, int pos_y, char tipo, char color, int numero_movimiento) {
	lista_piezas[ancho* pos_y + pos_x] = Pieza(tipo, color, numero_movimiento);
}

void Tablero::retirar_pieza(int pos_x, int pos_y) {
	lista_piezas[ancho * pos_y + pos_x] = Pieza('0', '0',0); // Pieza vacía
}

void Tablero::mover_pieza(int de_x, int de_y, int para_x, int para_y) {
	Pieza pieza = lista_piezas[ancho * de_y + de_x];

	colocar_pieza(para_x, para_y, pieza.ver_tipo(), pieza.ver_color(), pieza.ver_numero_movimiento()+1);
	retirar_pieza(de_x, de_y);
}

Pieza Tablero::getPieza(int pos_x,int pos_y) const {
	return lista_piezas[ancho * pos_y + pos_x];
}

int Tablero::ver_largo() const {
	return largo;
}

int Tablero::ver_ancho() const {
	return ancho;
}

