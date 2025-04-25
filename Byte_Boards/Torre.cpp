#include "Torre.h"
#include "Tablero.h"

//Constructor Torre
Torre::Torre(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:Pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{
	mov_t = false;
}

// Verificador del movimiento de la torre
bool Torre::mover_torre(int n_posx, int n_posy)
{
	vector<int> pos_torre_actual;
	pos_torre_actual = pos_actual();
	//vector<vector<string>> tablero_directo_torre = tablero_live;
	if ((n_posx - pos_torre_actual[0] == 0) && (n_posy - pos_torre_actual[1] != 0))
	{
		if (obstaculos_torre_x(pos_torre_actual[0], pos_torre_actual[1], n_posx, n_posy, *tablero_live))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]];
			(*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			mov_t = true;
			return true;
		}

	}
	else if ((n_posy - pos_torre_actual[1] == 0) && (n_posx - pos_torre_actual[0] != 0))
	{
		if (obstaculos_torre_y(pos_torre_actual[0], pos_torre_actual[1], n_posx, n_posy, *tablero_live))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]];
			(*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			mov_t = true;
			return true;
		}
	}
	else
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}
}

//Mueve la torre en el caso de que se detecte un jaque:
void Torre::mover_torre(int tipo)
{
	vector<int> pos_torre_actual;
	pos_torre_actual = pos_actual();

	switch (tipo)
	{
	case 2:
	{
		int n_posy = pos_torre_actual[1];
		int n_posx = pos_torre_actual[0] + 2;
		(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]];
		(*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]] = "XXXX";
		mover(n_posx, n_posy);
		mov_t++;
		break;
	}
	case 3:
	{
		int n_posy = pos_torre_actual[1];
		int n_posx = pos_torre_actual[0] - 3;
		(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]];
		(*tablero_live)[8 - pos_torre_actual[1]][pos_torre_actual[0]] = "XXXX";
		mover(n_posx, n_posy);
		mov_t++;
		break;
	}
	}
}

//Verificador mediante el tablero del movimento de la torre en el eje_x
bool Torre::obstaculos_torre_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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

//Verificador mediante el tablero del movimento de la torre en el eje_y
bool Torre::obstaculos_torre_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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

//Devuelve a la funcion main informacion acerca de si se ha movido la torre o no, para el roque 
bool Torre::mov_torre(void)
{
	return mov_t;
}