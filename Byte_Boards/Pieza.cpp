#include "Pieza.h"
#include "Tablero.h"

//Constructor pieza
Pieza::Pieza(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	: tablero_live(nullptr)
{
	pos[0] = posx;
	pos[1] = posy;
	num_tipo = tipo_pieza;
	num_pieza = pieza_num;
	blanco = col;
	vida = live;
}

//Posicion actual pieza
vector<int> Pieza::pos_actual(void)
{
	vector<int> pos_act{ pos[0], pos[1] };
	return pos_act;
}

//Posicion actual de todas las piezas en el tablero
void Pieza::tablero_act(vector<vector<string>>& tablero_directo)
{
	tablero_live = &tablero_directo;
}

//Actualizador de la posicion de la pieza
void Pieza::mover(int n_posx, int n_posy)
{
	pos[0] = n_posx;
	pos[1] = n_posy;
	int i, j;
}

//Comprobar si hay alguna pieza que haya muerto en este turno
void Pieza::Juicio_final(int tipo_muerto, int num_muerto, int blanco_muerto)
{
	/*
	cout << "He llegado al juicio final " << endl;
	cout << num_tipo << " = " << tipo_muerto << endl;
	cout << num_pieza << " = " << num_muerto << endl;
	cout << blanco << " = " << blanco_muerto << endl; */

	if ((num_tipo == tipo_muerto) && (num_pieza == num_muerto) && (blanco == (bool)blanco_muerto))
	{
		vida = false;
		cout << "La vida del " << name[num_tipo] << " numero " << num_pieza << " de color " << (blanco ? "blanco" : "negro") << " es del tipo " << (vida ? "vivo" : "muerto") << endl;
	}
}

//Comprobar si hay que ascender a alguna pieza
void Pieza::Juicio_final(int num_tipo_mejora)
{
	cout << "Esta pieza ha sido ascendida a " << name[num_tipo_mejora] << " y de ahora en adelante dejará de ser un peon" << endl;
	vida = false;
}

//Comprobar si la pieza seleccionada ha muerto
bool Pieza::obituary(void)
{
	if (num_pieza != 0)
		cout << "La vida del " << name[num_tipo] << " numero " << num_pieza << " de color " << (blanco ? "blanco" : "negro") << " es del tipo " << (vida ? "vivo" : "muerto") << endl;
	return !vida;
}

//Mostrar datos relavantes a la clase pieza
void Pieza::mostrar(void)
{
	cout << "La posicion del \"" << name[num_tipo] << "_" << num_pieza << "\" es:" << endl << "x = " << pos[0] << "\ny = " << pos[1] << endl;
}
