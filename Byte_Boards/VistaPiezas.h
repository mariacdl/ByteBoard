#pragma once
#include <utility>

using namespace std;
class Tablero;

class VistaPiezas {

	void dibujar_peon_blanco(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_torre_blanco(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_caballo_blanco(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_alfil_blanco(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_rey_blanco(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_dama_blanco(pair<int, int> pos, float tam, const Tablero& tablero);

	void dibujar_peon_negro(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_torre_negro(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_caballo_negro(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_alfil_negro(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_rey_negro(pair<int, int> pos, float tam, const Tablero& tablero);
	void dibujar_dama_negro(pair<int, int> pos, float tam, const Tablero& tablero);
public:
	VistaPiezas() {};
	VistaPiezas(const VistaPiezas& otro) {};

	void dibujar_piezas(float tam, const Tablero& tablero);
};