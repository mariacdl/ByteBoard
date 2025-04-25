#include "Alfil.h"
#include "Tablero.h"

//Constructor Alfil
Alfil::Alfil(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:Pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

//Verificador del movimiento del alfil
bool Alfil::mover_alfil(int n_posx, int n_posy)
{
	vector<int> pos_alfil_actual;
	pos_alfil_actual = pos_actual();

	int quadr = 0;
	int distx = n_posx - pos_alfil_actual[0];
	int disty = n_posy - pos_alfil_actual[1];

	if ((distx > 0) && (disty > 0))
		quadr = 1;
	if ((distx < 0) && (disty > 0))
		quadr = 2;
	if ((distx < 0) && (disty < 0))
		quadr = 3;
	if ((distx > 0) && (disty < 0))
		quadr = 4;

	if ((abs(n_posx - pos_alfil_actual[0]) == abs(n_posy - pos_alfil_actual[1])))
	{
		if (obstaculos_alfil_xy(pos_alfil_actual[0], pos_alfil_actual[1], n_posx, n_posy, *tablero_live, quadr))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_alfil_actual[1]][pos_alfil_actual[0]];
			(*tablero_live)[8 - pos_alfil_actual[1]][pos_alfil_actual[0]] = "XXXX";
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

//Verificador mediante el tablero del movimento del alfil
bool Alfil::obstaculos_alfil_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad)
{
	int dist = n_posx - posx;
	string rival;
	bool muerte = false;
	dist = abs(dist);
	int i;
	int count = 0;

	switch (quad)
	{
	case 1:
	{
		for (i = 1; i < dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx + i] != "XXXX")
				count++;
		}
		rival = tablero_directo[(8 - posy) - dist][posx + dist];
		break;
	}
	case 2:
	{
		for (i = 1; i < dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx - i] != "XXXX")
				count++;
		}
		rival = tablero_directo[(8 - posy) - dist][posx - dist];
		break;
	}
	case 3:
	{
		for (i = 1; i < dist; i++)
		{
			if (tablero_directo[(8 - posy) + i][posx - i] != "XXXX")
				count++;
		}
		rival = tablero_directo[(8 - posy) + dist][posx - dist];
		break;
	}
	case 4:
	{
		for (i = 1; i < dist; i++)
		{
			if (tablero_directo[(8 - posy) + i][posx + i] != "XXXX")
				count++;
		}
		rival = tablero_directo[(8 - posy) + dist][posx + dist];
		break;
	}
	}
	if (count == 0)
	{
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
		if ((rival == "XXXX") || muerte)
			return true;
	}
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}