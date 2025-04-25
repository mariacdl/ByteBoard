#include "Dama.h"
#include "Tablero.h"


//Constructor Dama
Dama::Dama(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:Pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

//Verificador del movimiento de la dama
bool Dama::mover_dama(int n_posx, int n_posy)
{
	vector<int> pos_dama_actual;
	pos_dama_actual = pos_actual();

	int quadr = 9;
	int distx = n_posx - pos_dama_actual[0];
	int disty = n_posy - pos_dama_actual[1];

	if ((distx == 0) && (abs(disty) >= 1))
		quadr = -1;
	else
		if ((disty == 0) && (abs(distx) >= 1))
			quadr = 0;
		else
			if ((distx > 0) && (disty > 0))
				quadr = 1;
			else
				if ((distx < 0) && (disty > 0))
					quadr = 2;
				else
					if ((distx < 0) && (disty < 0))
						quadr = 3;
					else
						if ((distx > 0) && (disty < 0))
							quadr = 4;

	if ((abs(n_posx - pos_dama_actual[0]) == abs(n_posy - pos_dama_actual[1])))
	{
		if (obstaculos_dama_xy(pos_dama_actual[0], pos_dama_actual[1], n_posx, n_posy, *tablero_live, quadr))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_dama_actual[1]][pos_dama_actual[0]];
			(*tablero_live)[8 - pos_dama_actual[1]][pos_dama_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			return true;
		}
	}
	else
		if (quadr == -1)
		{
			if (obstaculos_dama_x(pos_dama_actual[0], pos_dama_actual[1], n_posx, n_posy, *tablero_live))
			{
				(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_dama_actual[1]][pos_dama_actual[0]];
				(*tablero_live)[8 - pos_dama_actual[1]][pos_dama_actual[0]] = "XXXX";
				mover(n_posx, n_posy);
				return true;
			}
		}
		else
			if (quadr == 0)
			{
				if (obstaculos_dama_y(pos_dama_actual[0], pos_dama_actual[1], n_posx, n_posy, *tablero_live))
				{
					(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_dama_actual[1]][pos_dama_actual[0]];
					(*tablero_live)[8 - pos_dama_actual[1]][pos_dama_actual[0]] = "XXXX";
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

//Verificador mediante el tablero del movimento diagonal de la dama
bool Dama::obstaculos_dama_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad)
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
		else
		{
			cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
			return false;
		}
	}
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}

//Verificador mediante el tablero del movimento de la dama en el eje_x
bool Dama::obstaculos_dama_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
{
	int i, dist, count = 0;
	dist = n_posy - posy;
	string rival = tablero_directo[(8 - posy) - dist][posx];
	bool muerte = false;

	if (dist > 0)
	{
		for (i = 1; i < dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx] != "XXXX")
				count++;
		}
	}
	else
	{
		for (i = 1; i < abs(dist); i++)
		{
			if (tablero_directo[(8 - posy) + i][posx] != "XXXX")
				count++;
		}
	}

	if (count == 0)
	{
		if ((blanco == true) && ((rival[3] == 'N')))
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
		if ((tablero_directo[(8 - posy) - dist][posx] == "XXXX") || muerte)
			return true;
		else
		{
			cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
			return false;
		}
	}
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}

//Verificador mediante el tablero del movimento de la dama en el eje_y
bool Dama::obstaculos_dama_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
{
	int i, dist, count = 0;
	dist = n_posx - posx;
	string rival = tablero_directo[(8 - posy)][posx + dist];
	bool muerte = false;

	if (dist > 0)
	{
		for (i = 1; i < dist; i++)
		{
			if (tablero_directo[(8 - posy)][posx + i] != "XXXX")
				count++;
		}
	}
	else
		for (i = 1; i < abs(dist); i++)
		{
			if (tablero_directo[(8 - posy)][posx - i] != "XXXX")
				count++;
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
		if ((tablero_directo[(8 - posy)][posx + dist] == "XXXX") || muerte)
			return true;
		else
		{
			cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
			return false;
		}
	}
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}
