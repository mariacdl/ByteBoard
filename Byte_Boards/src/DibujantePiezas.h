#include "Tablero.h"

class DibujantePiezas {
	const Tablero& tablero;

	void dibujarPeonCiencias(int fila,int columna, float tam);
	void dibujarTorreCiencias(int fila, int columna, float tam);
	void dibujarCaballoCiencias(int fila, int columna, float tam);
	void dibujarAlfilCiencias(int fila, int columna, float tam);
	void dibujarReyCiencias(int fila, int columna, float tam);
	void dibujarReinaCiencias(int fila, int columna, float tam);
	void dibujarPeonLetras(int fila, int columna, float tam);
	void dibujarTorreLetras(int fila, int columna, float tam);
	void dibujarCaballoLetras(int fila, int columna, float tam);
	void dibujarAlfilLetras(int fila, int columna, float tam);
	void dibujarReyLetras(int fila, int columna, float tam);
	void dibujarReinaLetras(int fila, int columna, float tam);
public:
	DibujantePiezas(const Tablero& tab) : tablero(tab){}
	void dibujar(float tam);
};