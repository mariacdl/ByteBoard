#include "Rey.h"
#include "Tablero.h"

//Constructor Rey
Rey::Rey(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:Pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{
	jaque = false;
	mov_r = false;
}

//Verificador del movimiento del rey
int Rey::mover_rey(int n_posx, int n_posy, bool mov_torre_Iz, bool mov_torre_Dch)
{
	vector<int> pos_rey_actual;
	pos_rey_actual = pos_actual();

	int distx = n_posx - pos_rey_actual[0];
	int disty = n_posy - pos_rey_actual[1];

	if ((abs(distx) <= 1) && (abs(disty) <= 1))
	{
		if (obstaculos_rey_xy(pos_rey_actual[0], pos_rey_actual[1], n_posx, n_posy, *tablero_live))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_rey_actual[1]][pos_rey_actual[0]];
			(*tablero_live)[8 - pos_rey_actual[1]][pos_rey_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
		if ((abs(distx) == 2) && (abs(disty) == 0) && !mov_r && (!mov_torre_Iz || !mov_torre_Dch) && !jaque)
		{
			if (distx < 0)
			{
				if (verificador_enroque(pos_rey_actual[0], pos_rey_actual[1], n_posx, n_posy, *tablero_live, mov_torre_Iz, mov_torre_Dch))
				{
					(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_rey_actual[1]][pos_rey_actual[0]];
					(*tablero_live)[8 - pos_rey_actual[1]][pos_rey_actual[0]] = "XXXX";
					mover(n_posx, n_posy);
					//cout << n_posx << n_posy << endl;
					return 2;
				}
				else
				{
					return 0;
				}
			}
			else
				if (verificador_enroque(pos_rey_actual[0], pos_rey_actual[1], n_posx, n_posy, *tablero_live, mov_torre_Iz, mov_torre_Dch))
				{
					(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_rey_actual[1]][pos_rey_actual[0]];
					(*tablero_live)[8 - pos_rey_actual[1]][pos_rey_actual[0]] = "XXXX";
					mover(n_posx, n_posy);
					return 3;
				}
				else
				{
					return 0;
				}
		}
		else
		{
			cout << "La has liado, intentalo de nuevo" << endl << endl;
			return 0;
		}

}

//Verificador mediante el tablero del movimento diagonal de la dama
bool Rey::obstaculos_rey_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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

	if ((tablero_directo[(8 - posy) - disty][posx + distx] == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}

//Verificar que el rey no está en jaque
bool Rey::comp_jaque(void)
{
	vector<int> pos_rey_actual;
	pos_rey_actual = pos_actual();
	if (comp_jaque_xy(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
	{
		//cout << "El rey" << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
		jaque = true;
		return true;
	}
	else
		if (comp_jaque_x(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
		{
			//cout << "El rey " << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
			jaque = true;
			return true;
		}
		else
			if (comp_jaque_y(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
			{
				//cout << "El rey " << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
				jaque = true;
				return true;
			}
			else
				if (comp_jaque_caballo(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
				{
					//cout << "El rey " << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
					jaque = true;
					return true;
				}
				else
				{
					//cout << "El rey " << (blanco ? "blanco" : "negro") << " no esta en jaque" << endl;
					jaque = false;
					return false;
				}
}

//Verificar si hay jaque proveniente del eje xy 
bool Rey::comp_jaque_xy(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i;
	int count = 0;
	//Cuadrante 1 - +
	for (i = 1; ((8 - posy) - i) >= 0 && (posx + i) <= 8; i++)
	{
		if ((posx + i <= 8) && (posx + i > 0))
		{
			string rival = tablero_directo[(8 - posy) - i][posx + i];
			//cout << rival;
			if (blanco && (rival[3] == 'B'))
				break;
			else
				if (!blanco && (rival[3] == 'N'))
					break;
				else
					if (blanco && (((rival[3] == 'N') && ((rival[0] == 'A') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'A') || (rival[0] == 'D')))))
						{
							count = 1;
							break;
						}
		}

	}

	//Cuadrante 2 - -
	for (i = 1; ((8 - posy) - i) >= 0 && (posx - i) >= 1; i++)
	{
		if ((posx - i <= 8) && (posx - i > 0))
		{
			string rival = tablero_directo[(8 - posy) - i][posx - i];
			//cout << rival;
			if (blanco && (rival[3] == 'B'))
				break;
			else
				if (!blanco && (rival[3] == 'N'))
					break;
				else
					if (blanco && (((rival[3] == 'N') && ((rival[0] == 'A') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'A') || (rival[0] == 'D')))))
						{
							count = 1;
							break;
						}
		}
	}
	// CAMBIO AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII "<= 8" -> "<= 7"
	//Cuadrante 3 + - 
	for (i = 1; ((8 - posy) + i) <= 7 && (posx - i) >= 1; i++)
	{
		if ((posx - i <= 8) && (posx - i > 0))
		{
			string rival = tablero_directo[(8 - posy) + i][posx - i];
			//cout << rival;
			if (blanco && (rival[3] == 'B'))
				break;
			else
				if (!blanco && (rival[3] == 'N'))
					break;
				else
					if (blanco && (((rival[3] == 'N') && ((rival[0] == 'A') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'A') || (rival[0] == 'D')))))
						{
							count = 1;
							break;
						}
		}
	}
	// CAMBIO AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII "<= 8" -> "<= 7"
	//Cuadrante 4 + +
	for (i = 1; ((8 - posy) + i) <= 7 && (posx + i) <= 8; i++)
	{
		if ((posx + i <= 8) && (posx + i > 0))
		{
			string rival = tablero_directo[(8 - posy) + i][posx + i];
			//cout << rival;
			if (blanco && (rival[3] == 'B'))
				break;
			else
				if (!blanco && (rival[3] == 'N'))
					break;
				else
					if (blanco && (((rival[3] == 'N') && ((rival[0] == 'A') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'A') || (rival[0] == 'D')))))
						{
							count = 1;
							break;
						}
		}
	}

	//cout << " count = " << count << endl;
	if (count == 0)
	{
		if (blanco)
		{
			string rival = tablero_directo[(8 - posy) + 1][posx + 1];
			if ((rival[3] == 'N') && (rival[0] == 'P'))
			{
				count = 1;
				//cout << "rival peon" << rival;
			}
			if ((posx - 1 <= 8) && (posx - 1 > 0))
			{
				rival = tablero_directo[(8 - posy) + 1][posx - 1];
				if ((rival[3] == 'N') && (rival[0] == 'P'))
				{
					count = 1;
					//cout << "rival peon" << rival;
				}
			}

		}
		else
			if (!blanco)
			{
				if ((posx - 1 <= 8) && (posx - 1 > 0))
				{
					string rival = tablero_directo[(8 - posy) - 1][posx - 1];
					if ((rival[3] == 'B') && (rival[0] == 'P'))
					{
						count = 1;
						//cout << "rival peon" << rival;
					}
				}
				string rival = tablero_directo[(8 - posy) - 1][posx + 1];
				if ((rival[3] == 'B') && (rival[0] == 'P'))
				{
					count = 1;
					//cout << "rival peon" << rival;
				}
			}
	}
	if (count == 1)
	{
		cout << "Hay un jaque en el eje xy" << endl;
		return true;
	}
	else
	{
		return false;
	}

}

//Verificar si hay jaque proveniente del eje y 
bool Rey::comp_jaque_y(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i;
	int count = 0;
	//Vertical positiva - 
	for (i = 1; ((8 - posy) - i) >= 0; i++)
	{
		string rival = tablero_directo[(8 - posy) - i][posx];
		//cout << rival;
		if (blanco && (rival[3] == 'B'))
			break;
		else
			if (!blanco && (rival[3] == 'N'))
				break;
			else
				if (blanco && (((rival[3] == 'N') && ((rival[0] == 'T') || (rival[0] == 'D')))))
				{
					count = 1;
					break;
				}
				else
					if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'T') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
	}
	// CAMBIO AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII "<= 8" -> "<= 7"
	//Vertical negativa +
	for (i = 1; ((8 - posy) + i) <= 7; i++)
	{
		string rival = tablero_directo[(8 - posy) + i][posx];
		//cout << rival;
		if (blanco && (rival[3] == 'B'))
			break;
		else
			if (!blanco && (rival[3] == 'N'))
				break;
			else
				if (blanco && (((rival[3] == 'N') && ((rival[0] == 'T') || (rival[0] == 'D')))))
				{
					count = 1;
					break;
				}
				else
					if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'T') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
	}
	//cout << " count = " << count << endl;
	if (count == 1)
	{
		cout << "Hay un jaque en el eje y" << endl;
		return true;
	}
	else
	{
		return false;
	}

}

//Verificar si hay jaque proveniente del eje x 
bool Rey::comp_jaque_x(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i;
	int count = 0;
	//Horizontal positiva + 
	for (i = 1; (posx + i) <= 8; i++)
	{
		if ((posx + i <= 8) && (posx + i > 0))
		{
			string rival = tablero_directo[(8 - posy)][posx + i];
			if (blanco && (rival[3] == 'B'))
				break;
			else
				if (!blanco && (rival[3] == 'N'))
					break;
				else
					if (blanco && (((rival[3] == 'N') && ((rival[0] == 'T') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'T') || (rival[0] == 'D')))))
						{
							count = 1;
							break;
						}
		}

	}

	//Horizontal negativa -
	for (i = 1; posx - i >= 0; i++)
	{
		if ((posx - i <= 8) && (posx - i > 0))
		{
			string rival = tablero_directo[(8 - posy)][posx - i];
			if (blanco && (rival[3] == 'B'))
				break;
			else
				if (!blanco && (rival[3] == 'N'))
					break;
				else
					if (blanco && (((rival[3] == 'N') && ((rival[0] == 'T') || (rival[0] == 'D')))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && (((rival[3] == 'B') && ((rival[0] == 'T') || (rival[0] == 'D')))))
						{
							count = 1;
							break;
						}
		}

	}
	if (count == 1)
	{
		cout << "Hay un jaque en el eje x" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

//Verificar si hay jaque por culpa de un caballo 
bool Rey::comp_jaque_caballo(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i, j;
	int x, y, trade;
	int count = 0;
	vector<int> fila{ 1,2,2,1 };
	vector<int> columna{ -2,-1,1,2, };
	//cout << "comp_jaque_caballo" << endl;
	//((8 - posy) - i) >= 0 && (posx + i)
	//Cuadrante 1 - +
	for (j = 1; j >= -1; j -= 2)
	{
		for (i = 0; i < 4; i++)
		{
			x = fila[i];
			x *= j;
			y = columna[i];
			//cout << "Posicion en [i] = " << (8 - posy) - x << "Posicion en [j] = " << posx + y << endl;
			if (((8 - posy) - x <= 7) && ((8 - posy) - x >= 0))
			{
				if ((posx + y <= 8) && (posx + y > 0))  //(posx + x <= 8) && (posx + x >= 0) -> ((posx + y <= 8) && (posx + y > 0))
				{
					string rival = tablero_directo[(8 - posy) - x][posx + y];
					//cout << "El objetivo es " << rival << endl;
					if (blanco && ((rival[3] == 'N') && ((rival[0] == 'C'))))
					{
						count = 1;
						break;
					}
					else
						if (!blanco && ((rival[3] == 'B') && (rival[0] == 'C')))
						{
							count = 1;
							break;
						}
				}

			}

		}
	}

	//cout << " count = " << count << endl;
	if (count == 1)
	{
		cout << "Hay un jaque causado por caballo" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

//Verificador de roque
bool Rey::verificador_enroque(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, bool m_t_I, bool m_t_D)
{
	int distx = n_posx - posx;
	int i, count = 0;
	if (distx > 0 && !m_t_D)
	{
		for (i = 1; i <= 3; i++)
		{
			if (tablero_directo[(8 - posy)][posx + i] != "XXXX")
				count++;
		}
		if (comp_jaque_xy(posx + 1, posy, tablero_directo) || comp_jaque_y(posx + 1, posy, tablero_directo) || comp_jaque_caballo(posx + 1, posy, tablero_directo))
		{
			count++;
		}
		if (count == 0)
			return true;
		else
		{
			cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
			return false;
		}
	}
	else
		if (distx < 0 && !m_t_I)
		{
			for (i = 1; i <= 2; i++)
			{
				if (tablero_directo[(8 - posy)][posx - i] != "XXXX")
					count++;
			}
			if (comp_jaque_xy(posx - 1, posy, tablero_directo) || comp_jaque_y(posx - 1, posy, tablero_directo) || comp_jaque_caballo(posx - 1, posy, tablero_directo))
			{
				count++;
			}
			if (count == 0)
				return true;
			else
			{
				cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
				return false;
			}
		}

}

