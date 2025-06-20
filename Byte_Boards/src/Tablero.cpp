#include "Tablero.h"
#include "Pieza.h"
#include "Peon.h"
#include "Torre.h"
#include "Alfil.h"
#include "Rey.h"
#include "Caballo.h"
#include "Dama.h"

using namespace std;

Tablero::Tablero(char modalidad) {
	this->modalidad = modalidad;

	if (modalidad == 'P') {
		// Inicializa o tablero con punteros nulos (casillas vacías)
		lista_piezas.resize(4 * 5, nullptr);
		this->ancho = 4;
		this->largo = 5;

		colocar_pieza(0, 0, 'R', 'N');
		colocar_pieza(1, 0, 'C', 'N');
		colocar_pieza(2, 0, 'A', 'N');
		colocar_pieza(3, 0, 'T', 'N');
		colocar_pieza(0, 1, 'P', 'N');

		colocar_pieza(3, 4, 'R', 'B');
		colocar_pieza(2, 4, 'C', 'B');
		colocar_pieza(1, 4, 'A', 'B');
		colocar_pieza(0, 4, 'T', 'B');
		colocar_pieza(3, 3, 'P', 'B');

	}
	else {
		// Inicializa o tablero con punteros nulos (casillas vacías)
		lista_piezas.resize(5 * 6, nullptr);
		this->ancho = 5;
		this->largo = 6;

		colocar_pieza(0, 0, 'D', 'N');
		colocar_pieza(1, 0, 'R', 'N');
		colocar_pieza(2, 0, 'A', 'N');
		colocar_pieza(3, 0, 'C', 'N');
		colocar_pieza(4, 0, 'T', 'N');
		colocar_pieza(0, 1, 'P', 'N');
		colocar_pieza(1, 1, 'P', 'N');
		colocar_pieza(2, 1, 'P', 'N');
		colocar_pieza(3, 1, 'P', 'N');
		colocar_pieza(4, 1, 'P', 'N');

		colocar_pieza(0, 5, 'T', 'B');
		colocar_pieza(1, 5, 'C', 'B');
		colocar_pieza(2, 5, 'A', 'B');
		colocar_pieza(3, 5, 'R', 'B');
		colocar_pieza(4, 5, 'D', 'B');
		colocar_pieza(0, 4, 'P', 'B');
		colocar_pieza(1, 4, 'P', 'B');
		colocar_pieza(2, 4, 'P', 'B');
		colocar_pieza(3, 4, 'P', 'B');
		colocar_pieza(4, 4, 'P', 'B');
	}
}

Tablero::~Tablero() {
	// Libera la memoria de todas las piezas
	for (auto pieza : lista_piezas) {
		delete pieza;
	}
}

int Tablero::ver_largo() const {
	return largo;
}

int Tablero::ver_ancho() const {
	return ancho;
}

char Tablero::ver_modalidad() const {
	return modalidad;
}

Pieza* Tablero::ver_pieza(int pos_x, int pos_y) const {
	return lista_piezas[ancho * pos_y + pos_x];
}

void Tablero::colocar_pieza(int pos_x, int pos_y, char tipo, char color, int numero_movimientos) {
	int index = ancho * pos_y + pos_x;
	delete lista_piezas[index]; // evitar memory leak

	Pieza* nueva = nullptr;

	switch (tipo) {
	case 'P': nueva = new Peon(color); break;
	case 'T': nueva = new Torre(color); break;
	case 'A': nueva = new Alfil(color); break;
	case 'C': nueva = new Caballo(color); break;
	case 'D': nueva = new Dama(color); break;
	case 'R': nueva = new Rey(color); break;
	default: nueva = nullptr; // Casilla vacía
	}
	lista_piezas[index] = nueva;
}

void Tablero::retirar_pieza(int pos_x, int pos_y) {
	int index = ancho * pos_y + pos_x;
	delete lista_piezas[index]; // libera memoria
	lista_piezas[index] = nullptr; // casilla vacía
}

void Tablero::mover_pieza(int de_x, int de_y, int para_x, int para_y) {
	int index_origen = ancho * de_y + de_x;
	int index_destino = ancho * para_y + para_x;

	if (lista_piezas[index_origen]) {
		// Eliminar cualquier pieza en destino (captura)
		delete lista_piezas[index_destino];
		// Mover puntero
		lista_piezas[index_destino] = lista_piezas[index_origen];
		lista_piezas[index_origen] = nullptr;
		lista_piezas[index_destino]->incrementar_movimiento();
	}
}

const vector<Pieza*>& Tablero::listar_piezas() const {
	return lista_piezas;
}
bool Tablero::validar_movimiento(int de_x, int de_y, int para_x, int para_y) const {
	Pieza* pieza = ver_pieza(de_x, de_y);
	return pieza->validar_movimiento(de_x, de_y, para_x, para_y, *this);
}

vector<pair<int, int>> Tablero::listar_movimientos_validos(int position_x, int position_y) const{
	vector<pair<int, int>> movimientos_validos;
	for (int x = 0; x < ancho; ++x) {
		for (int y = 0; y < largo; ++y) {
			if (validar_movimiento(position_x, position_y, x, y)) {
				movimientos_validos.emplace_back(x, y);
			}
		}
	}
	return movimientos_validos;
}

