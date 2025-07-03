#pragma once
#include "VistaPiezas.h"
#include "freeglut.h"
#include <utility>
#include <vector>
#include <Estados.h>

using namespace std;

class Tablero;

class VistaTablero {
	const float tam;
	VistaPiezas* vista_piezas;

	void dibujar_marco(const Tablero& tablero) const;
public:
	VistaTablero(TipoJuego m) : tam((m == JUEGO_4x5) ? 1.5f : 1.3f), vista_piezas(new VistaPiezas()) { };
	VistaTablero(const VistaTablero& otro) : tam(otro.tam), vista_piezas(new VistaPiezas(*otro.vista_piezas)) {};
	~VistaTablero() { delete vista_piezas; };
	void dibujar_tablero(const Tablero& tablero);
	void dibujar_seleccion(pair<int,int> casilla, const Tablero& tablero, GLfloat r = 0.0f, GLfloat g = 1.0f, GLfloat b = 0.0f) const;
	void dibujar_movimientos(vector<pair<int, int>> movimientos_validos, const Tablero& tablero);
	float getTam() const;
};