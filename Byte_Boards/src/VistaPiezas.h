#pragma once

class Tablero;

class VistaPiezas {

	void dibujarPeonCiencias(int fila,int columna, float tam, const Tablero& tablero);
	void dibujarTorreCiencias(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarCaballoCiencias(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarAlfilCiencias(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarReyCiencias(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarReinaCiencias(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarPeonLetras(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarTorreLetras(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarCaballoLetras(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarAlfilLetras(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarReyLetras(int fila, int columna, float tam, const Tablero& tablero);
	void dibujarReinaLetras(int fila, int columna, float tam, const Tablero& tablero);
public:
	void dibujar(float tam, const Tablero& tablero);
};