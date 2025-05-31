#pragma once

class DTablero
{
	float tam=0.0f;//tamaño de la casilla
	int filas;
	int columnas;

public: 
	DTablero(int filas, int columnas, float tam): filas(filas), columnas(columnas), tam(tam) {}

	void dibujarMarco(float tamCasilla, int filas, int columnas);//dibuja el borde exterior del tablero
	void dibujarSeleccion(int fila, int columna);//dibuja un cuadrado en la casilla para hacer ver que está selccionada
	void dibujar();//dibuja las casillas del tablero

	int getFilas() const { return filas; }
	int getColumnas() const { return columnas; }
	float getTam() const { return tam; }

};