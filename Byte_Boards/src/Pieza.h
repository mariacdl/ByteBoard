#pragma once

class Pieza {

public:
	enum figuras {Rey, Torre,
		Alfil, Caballo, Peon};

	enum equipos {Ciencias, Letras};

	Pieza(figuras figuras, equipos equipos);

	void dibujar(float x, float y, float tam);

private:

	figuras _figuras;
	equipos _equipos;

	void dibujarRey(float tam);
	void dibujarTorre(float tam);
	void dibujarAlfil(float tam);
	void dibujarCaballo(float tam);
	void dibujarPeon(float tam);

};



