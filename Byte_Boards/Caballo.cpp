#include "Caballo.h"
#include "Tablero.h"
#include <vector>

//Constructor Caballo
Caballo::Caballo(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:Pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

// Verificador del movimiento del caballo
bool Caballo::mover_caballo(int n_posx, int n_posy)
{
	vector<int> pos_caballo_actual;
	pos_caballo_actual = pos_actual();

	if ((abs(n_posx - pos_caballo_actual[0]) == 2) && (abs(n_posy - pos_caballo_actual[1]) == 1))
	{
		if (obstaculos_caballo_xy(pos_caballo_actual[0], pos_caballo_actual[1], n_posx, n_posy, *tablero_live))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_caballo_actual[1]][pos_caballo_actual[0]];
			(*tablero_live)[8 - pos_caballo_actual[1]][pos_caballo_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			return true;
		}
	}
	else if ((abs(n_posx - pos_caballo_actual[0]) == 1) && (abs(n_posy - pos_caballo_actual[1]) == 2))
	{
		if (obstaculos_caballo_xy(pos_caballo_actual[0], pos_caballo_actual[1], n_posx, n_posy, *tablero_live))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_caballo_actual[1]][pos_caballo_actual[0]];
			(*tablero_live)[8 - pos_caballo_actual[1]][pos_caballo_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			return true;
		}
	}
	else
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}


}

//Verificador mediante el tablero del movimento del caballo
bool Caballo::obstaculos_caballo_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
{
	int distx = n_posx - posx;
	int disty = n_posy - posy;
	bool muerte = false;

	string rival = tablero_directo[(8 - posy) - disty][posx + distx];
	if ((blanco == true) && (rival[3] == 'N'))
	{
		Death_List(rival);
		muerte = true;
	}
	else
		if ((blanco == false) && (rival[3] == 'B'))
		{
			Death_List(rival);
			muerte = true;
		}
		else
			Death_List("****");

	//cout << "***" << rival << endl;
	//cout << "***" << rival[3] << endl;

	if ((tablero_directo[(8 - posy) - disty][posx + distx] == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}
