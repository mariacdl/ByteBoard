#include "DibujantePiezas.h"
#include "Tablero.h"
#include "freeglut.h"

class DibujanteTablero {
	const float tam;
	const Tablero& tablero;
	DibujantePiezas* dibujantepiezas;

	void dibujarMarco();
public:
	~DibujanteTablero() { delete dibujantepiezas; }
	DibujanteTablero(const Tablero& tab, char modalidad) : tablero(tab), tam((modalidad == 'P') ? 1.5 : 1.3) { dibujantepiezas = new DibujantePiezas(tab); };
	void dibujarTablero();
	void dibujarSeleccion(int fila, int columna, GLfloat r = 0.0f, GLfloat g = 1.0f, GLfloat b = 0.0f);
	void dibujarMovimientos(int fila, int columna);
	float getTam() const;
};