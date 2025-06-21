#pragma once
#include "VistaPiezas.h"
#include "freeglut.h"
#include <utility>

using namespace std;

class Tablero;

class VistaTablero {
	const float tam;
	VistaPiezas* vista_piezas;

	void dibujar_marco(const Tablero& tablero) const;
public:
	VistaTablero(char m) : tam((m == 'P') ? 1.5 : 1.3), vista_piezas(new VistaPiezas()) { };
	~VistaTablero() { delete vista_piezas; }
	void dibujar_tablero(const Tablero& tablero);
	void dibujar_seleccion(pair<int,int> casilla, const Tablero& tablero, GLfloat r = 0.0f, GLfloat g = 1.0f, GLfloat b = 0.0f) const;
	void dibujar_movimientos(pair<int, int> casilla, const Tablero& tablero);
	float getTam() const;
};