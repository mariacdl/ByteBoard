
class Tablero
{
	int num=0;//tamaño del tablero
	double tam=0.0;//tamaño de la casilla
	int filas;
	int columnas;

public: 
	Tablero(int filas, int columnas, double tam); //constructor

	void dibujarMarco(float tamCasilla, int filas, int columnas);
	void dibujar();
};