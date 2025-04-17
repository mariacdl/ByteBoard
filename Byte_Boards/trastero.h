

using namespace std;

struct Death_ID {
	int num_tipo;
	int num_pieza;
	int blanc;
};

//Funciones
int Leer_Tablero_2(vector<vector<string>>& matrix);
void Imprimir_Tablero_2(vector<vector<string>> matrix);
void Death_List(string victim);
struct Death_ID Read_Victim_Data(struct Death_ID victim);


//Clase Pieza
class pieza {
private:
	int pos[2];
	vector <string> name{ "rey", "dama", "torre", "alfil", "caballo", "peon" };
	int num_tipo;
	int num_pieza;
	bool vida;
protected:
	vector<vector<string>>* tablero_live;
	bool blanco;
public:
	pieza(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	void mover(int n_posx, int n_posy);
	void tablero_act(vector<vector<string>>& tablero_directo);
	virtual void mostrar(void);
	vector<int> pos_actual(void);
	void Juicio_final(int tipo_muerto, int num_muerto, int blanco_muerto);
	bool obituary(void);
};


//Clase Rey
class rey : public pieza {
private:
	bool jaque;
public:
	rey(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_rey(int n_posx, int n_posy);
	bool obstaculos_rey_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool comp_jaque(void);
	bool comp_jaque_xy(int posx, int posy, vector<vector<string>> tablero_directo);
	bool comp_jaque_x(int posx, int posy, vector<vector<string>> tablero_directo);
	bool comp_jaque_y(int posx, int posy, vector<vector<string>> tablero_directo);
	bool comp_jaque_caballo(int posx, int posy, vector<vector<string>> tablero_directo);
};

//Clase Dama
class dama : public pieza {
private:

public:
	dama(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_dama(int n_posx, int n_posy);
	bool obstaculos_dama_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad);
	bool obstaculos_dama_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool obstaculos_dama_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};

//Clase Torre
class torre : public pieza {
private:

public:
	torre(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_torre(int n_posx, int n_posy);
	bool obstaculos_torre_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool obstaculos_torre_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};

//Clase Alfil
class alfil : public pieza {
private:

public:
	alfil(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_alfil(int n_posx, int n_posy);
	bool obstaculos_alfil_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad);
};

//Clase Caballo
class caballo : public pieza {
private:

public:
	caballo(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_caballo(int n_posx, int n_posy);
	bool obstaculos_caballo_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	//bool obstaculos_caballo_xY(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};

//Clase Peon
class peon : public pieza {
private:
	int cant;
public:
	peon(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_peon(int n_posx, int n_posy);
	void mostrar(void);
	bool obstaculos_peon_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int cant_mov);
	bool obstaculos_peon_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo); // Esta funcion servirá para comer en diagonal
};


//Constructor pieza
pieza::pieza(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	: tablero_live(nullptr)
{
	pos[0] = posx;
	pos[1] = posy;
	num_tipo = tipo_pieza;
	num_pieza = pieza_num;
	blanco = col;
	vida = live;
}


//Constructor Rey
rey::rey(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{
	jaque = false;
}

//Constructor Dama
dama::dama(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

//Constructor Torre
torre::torre(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

//Constructor Alfil
alfil::alfil(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

//Constructor Caballo
caballo::caballo(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{

}

//Constructor Peon
peon::peon(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{
	cant = 0;
}


//Verificador del movimiento del rey
bool rey::mover_rey(int n_posx, int n_posy)
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
bool rey::obstaculos_rey_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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
bool rey::comp_jaque(void)
{
	vector<int> pos_rey_actual;
	pos_rey_actual = pos_actual();

	if (comp_jaque_xy(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
	{
		//cout << "El rey" << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
		return true;
	}
	else
		if (comp_jaque_x(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
		{
			//cout << "El rey " << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
			return true;
		}
		else
			if (comp_jaque_y(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
			{
				//cout << "El rey " << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
				return true;
			}
			else
				if (comp_jaque_caballo(pos_rey_actual[0], pos_rey_actual[1], *tablero_live))
				{
					//cout << "El rey " << (blanco ? "blanco" : "negro") << " esta en jaque" << endl;
					return true;
				}
				else
				{
					//cout << "El rey " << (blanco ? "blanco" : "negro") << " no esta en jaque" << endl;
					return false;
				}
}

//Verificar si hay jaque proveniente del eje xy 
bool rey::comp_jaque_xy(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i;
	int count = 0;
	//Cuadrante 1 - +
	for (i = 1; ((8 - posy) - i) >= 0 && (posx + i) <= 8; i++)
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

	//Cuadrante 2 - -
	for (i = 1; ((8 - posy) - i) >= 0 && (posx - i) >= 1; i++)
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
	// CAMBIO AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII "<= 8" -> "<= 7"
	//Cuadrante 3 + - 
	for (i = 1; ((8 - posy) + i) <= 7 && (posx - i) >= 1; i++)
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
	// CAMBIO AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII "<= 8" -> "<= 7"
	//Cuadrante 4 + +
	for (i = 1; ((8 - posy) + i) <= 7 && (posx + i) <= 8; i++)
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
			rival = tablero_directo[(8 - posy) + 1][posx - 1];
			if ((rival[3] == 'N') && (rival[0] == 'P'))
			{
				count = 1;
				//cout << "rival peon" << rival;
			}
		}
		else
			if (!blanco)
			{
				string rival = tablero_directo[(8 - posy) - 1][posx - 1];
				if ((rival[3] == 'B') && (rival[0] == 'P'))
				{
					count = 1;
					//cout << "rival peon" << rival;
				}
				rival = tablero_directo[(8 - posy) - 1][posx + 1];
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
bool rey::comp_jaque_y(int posx, int posy, vector<vector<string>> tablero_directo)
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
bool rey::comp_jaque_x(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i;
	int count = 0;

	//Horizontal positiva + 
	for (i = 1; (posx + i) <= 8; i++)
	{
		string rival = tablero_directo[(8 - posy)][posx + i];
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

	//Horizontal negativa -
	for (i = 1; posx - i >= 0; i++)
	{
		string rival = tablero_directo[(8 - posy)][posx - i];
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
		cout << "Hay un jaque en el eje x" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

//Verificar si hay jaque por culpa de un caballo 
bool rey::comp_jaque_caballo(int posx, int posy, vector<vector<string>> tablero_directo)
{
	int i, j;
	int x, y, trade;
	int count = 0;
	vector<int> fila{ 1,2,2,1 };
	vector<int> columna{ -2,-1,1,2, };

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
				if ((posx + x <= 8) && (posx + x >= 0))
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



//Verificador del movimiento de la dama
bool dama::mover_dama(int n_posx, int n_posy)
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
bool dama::obstaculos_dama_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad)
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
	}

	if ((rival == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}

//Verificador mediante el tablero del movimento de la dama en el eje_x
bool dama::obstaculos_dama_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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
	}

	if ((tablero_directo[(8 - posy) - dist][posx] == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}

//Verificador mediante el tablero del movimento de la dama en el eje_y
bool dama::obstaculos_dama_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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
	}

	if ((tablero_directo[(8 - posy)][posx + dist] == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}


// Verificador del movimiento de la torre
bool torre::mover_torre(int n_posx, int n_posy)
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
			return true;
		}
	}
	else
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}
}

//Verificador mediante el tablero del movimento de la torre en el eje_x
bool torre::obstaculos_torre_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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
	}

	if ((tablero_directo[(8 - posy) - dist][posx] == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}

//Verificador mediante el tablero del movimento de la torre en el eje_y
bool torre::obstaculos_torre_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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
	}

	if ((tablero_directo[(8 - posy)][posx + dist] == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}


//Verificador del movimiento del alfil
bool alfil::mover_alfil(int n_posx, int n_posy)
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
bool alfil::obstaculos_alfil_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad)
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
	}

	if ((rival == "XXXX") || muerte)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}


// Verificador del movimiento del caballo
bool caballo::mover_caballo(int n_posx, int n_posy)
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
bool caballo::obstaculos_caballo_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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


//Verificador del movimiento del peon
bool peon::mover_peon(int n_posx, int n_posy) {

	vector<int> pos_peon_actual;
	pos_peon_actual = pos_actual();
	//Diferenciar entre peones blancos y negros
	if ((n_posy - pos_peon_actual[1] > 0) && blanco)
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}
	//Diferenciar entre peones blancos y negros
	if ((n_posy - pos_peon_actual[1] < 0) && !blanco)
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}

	if ((n_posx - pos_peon_actual[0] == 0) && (abs(n_posy - pos_peon_actual[1]) <= 2))
	{
		if (obstaculos_peon_x(pos_peon_actual[0], pos_peon_actual[1], n_posx, n_posy, *tablero_live, cant))
		{
			(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]];
			(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = "XXXX";
			mover(n_posx, n_posy);
			cant++;
			return true;
		}
	}
	else
		if (abs(n_posx - pos_peon_actual[0]) == 1 && (abs(n_posy - pos_peon_actual[1]) == 1))
		{
			if (obstaculos_peon_xy(pos_peon_actual[0], pos_peon_actual[1], n_posx, n_posy, *tablero_live))
			{
				(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]];
				(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = "XXXX";
				mover(n_posx, n_posy);
				cant++;
				return true;
			}
		}
		else {
			cout << "La has liado, intentalo de nuevo" << endl << endl;
			return false;
		}
}

//Verificador mediante el tablero del movimento del peon
bool peon::obstaculos_peon_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int cant_mov)
{
	int disty = n_posy - posy;

	if ((abs(disty) == 2) && (cant_mov == 0) && (tablero_directo[((8 - posy) - disty)][n_posx] == "XXXX"))
		return true;
	else
		if ((abs(disty) == 1) && (tablero_directo[((8 - posy) - disty)][n_posx] == "XXXX"))
			return true;
		else
		{
			cout << "Hay un obstaculo, elije otro movimiento" << endl;
			return false;
		}
}

//Verificador mediante el tablero del peon comiendo
bool peon::obstaculos_peon_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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


//Posicion actual pieza
vector<int> pieza::pos_actual(void)
{
	vector<int> pos_act{ pos[0], pos[1] };
	return pos_act;
}

//Posicion actual de todas las piezas en el tablero
void pieza::tablero_act(vector<vector<string>>& tablero_directo)
{
	tablero_live = &tablero_directo;
}

//Actualizador de la posicion de la pieza
void pieza::mover(int n_posx, int n_posy)
{
	pos[0] = n_posx;
	pos[1] = n_posy;
	int i, j;
}

//Comprobar si hay alguna pieza que haya muerto en este turno
void pieza::Juicio_final(int tipo_muerto, int num_muerto, int blanco_muerto)
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

//Comprobar si la pieza seleccionada ha muerto
bool pieza::obituary(void)
{
	if (num_pieza != 0)
	cout << "La vida del " << name[num_tipo] << " numero " << num_pieza << " de color " << (blanco ? "blanco" : "negro") << " es del tipo " << (vida ? "vivo" : "muerto") << endl;
	return !vida;
}

//Mostrar datos relavantes a la clase pieza
void pieza::mostrar(void)
{
	cout << "La posicion del \"" << name[num_tipo] << "_" << num_pieza << "\" es:" << endl << "x = " << pos[0] << "\ny = " << pos[1] << endl;
}

//Mostrar datos relecantes a la sub-clase peon
void peon::mostrar(void) {
	pieza::mostrar();

	cout << "Esta pieza ha sido movida " << cant << " veces" << endl;
}

void Imprimir_Tablero_2(vector<vector<string>> matrix)
{
	size_t i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 9; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int Leer_Tablero_2(vector<vector<string>>& matrix)
{

	string linea;
	string elemento;

	// pieza *nums[17];
	ifstream table;
	//table.open("C:/Users/Usuario/Desktop/INFO/pruebasVS/Trabajo/tablero.txt", ios::in); //CAUTION
	table.open("tablero.txt", ios::in); //CAUTION
	if (!table.is_open()) {
		cout << "No se ha conseguido Leer adecuadamente el tablero\n";
		return -1;
	}
	else
	{
		while (getline(table, linea))
		{
			vector<string> fila;  // Vector que guarda los elementos de la linea actual
			stringstream ss(linea);

			while (getline(ss, elemento, ';')) {
				fila.push_back(elemento);
			}
			matrix.push_back(fila);
		}
		return 0;
	}

}

void Death_List(string victim)
{
	//cout << "He llegado hasta Death List" << endl;
	ofstream Death_Note;
	Death_Note.open("Death_Note.txt");
	if (!Death_Note.is_open()) {
		cout << "No se ha conseguido Crear la carta \n";
	}
	Death_Note << victim;

	Death_Note.close();

}

struct Death_ID Read_Victim_Data(struct Death_ID victim)
{
	struct Death_ID victim_ID { 0, 0, 0 };
	string Victim_ID;
	ifstream Death_Note;
	//cout << "He llegado hasta Leer Death List" << endl;
	Death_Note.open("Death_Note.txt");
	if (!Death_Note.is_open()) {
		cout << "No se ha conseguido Leer adecuadamente la lista\n";
	}
	Death_Note >> Victim_ID;
	switch (Victim_ID[0])
	{
	case 'R':
	{
		victim_ID.num_tipo = 0;
		break;
	}
	case 'D':
	{
		victim_ID.num_tipo = 1;
		break;
	}
	case 'T':
	{
		victim_ID.num_tipo = 2;
		break;
	}
	case 'A':
	{
		victim_ID.num_tipo = 3;
		break;
	}
	case 'C':
	{
		victim_ID.num_tipo = 4;
		break;
	}
	case 'P':
	{
		victim_ID.num_tipo = 5;
		break;
	}
	case '*':
		return victim_ID;
	}

	switch (Victim_ID[1])
	{
	case '1':
	{
		victim_ID.num_pieza = 1;
		break;
	}
	case '2':
	{
		victim_ID.num_pieza = 2;
		break;
	}
	case '3':
	{
		victim_ID.num_pieza = 3;
		break;
	}
	case '4':
	{
		victim_ID.num_pieza = 4;
		break;
	}
	case '5':
	{
		victim_ID.num_pieza = 5;
		break;
	}
	case '6':
	{
		victim_ID.num_pieza = 6;
		break;
	}

	case '7':
	{
		victim_ID.num_pieza = 7;
		break;
	}
	case '8':
	{
		victim_ID.num_pieza = 8;
		break;
	}
	}

	switch (Victim_ID[3])
	{
	case 'B':
	{
		victim_ID.blanc = 1;
		break;
	}
	case 'N':
	{
		victim_ID.blanc = 0;
		break;
	}
	}

	Death_Note.close();
	return victim_ID;
}
