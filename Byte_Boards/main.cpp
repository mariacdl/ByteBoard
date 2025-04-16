

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;


int Leer_Tablero_2(vector<vector<string>>& matrix);
void Imprimir_Tablero_2(vector<vector<string>> matrix);


//Clase Pieza
class pieza {
private:
	int pos[2];
	vector <string> name{ "rey", "dama", "torre", "alfil", "caballo", "peon" };
	int num_tipo;
	int num_pieza;
protected:
	vector<vector<string>>* tablero_live;
	bool blanco;
public:
	pieza(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	void mover(int n_posx, int n_posy);
	void tablero_act(vector<vector<string>>& tablero_directo);
	virtual void mostrar(void);
	vector<int> pos_actual(void);
};

//Clase Peon
class peon : public pieza {
private:
	int cant;
public:
	peon(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	bool mover_peon(int n_posx, int n_posy);
	void mostrar(void);
	bool obstaculos_peon_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	// bool obstaculos_peon_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo); Esta funcion servirá para comer en diagonal

};

//Clase Torre
class torre : public pieza {
private:

public:
	torre(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	bool mover_torre(int n_posx, int n_posy);
	bool obstaculos_torre_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool obstaculos_torre_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};

//Clase Caballo
class caballo : public pieza {
private:

public:
	caballo(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	bool mover_caballo(int n_posx, int n_posy);
	bool obstaculos_caballo_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	//bool obstaculos_caballo_xY(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};

//Clase Alfil
class alfil : public pieza {
private:

public:
	alfil(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	bool mover_alfil(int n_posx, int n_posy);
	bool obstaculos_alfil_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad);
};

class rey : public pieza {
private:
	bool jaque;
public:
	rey(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	bool mover_rey(int n_posx, int n_posy);
	bool obstaculos_rey_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	//bool obstaculos_rey_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	//bool obstaculos_rey_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};

class dama : public pieza {
private:

public:
	dama(int posx, int posy, int tipo_pieza, int pieza_num, bool col);
	bool mover_dama(int n_posx, int n_posy);
	bool obstaculos_dama_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad);
	bool obstaculos_dama_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool obstaculos_dama_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};


//Constructor pieza
pieza::pieza(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	: tablero_live(nullptr)
{
	pos[0] = posx;
	pos[1] = posy;
	num_tipo = tipo_pieza;
	num_pieza = pieza_num;
	blanco = col;
}

//Constructor Peon
peon::peon(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	:pieza(posx, posy, tipo_pieza, pieza_num, col)
{
	cant = 0;
}

//Constructor Torre
torre::torre(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	:pieza(posx, posy, tipo_pieza, pieza_num, col)
{

}

//Constructor Caballo
caballo::caballo(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	:pieza(posx, posy, tipo_pieza, pieza_num, col)
{

}

//Constructor Alfil
alfil::alfil(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	:pieza(posx, posy, tipo_pieza, pieza_num, col)
{

}

//Constructor Rey
rey::rey(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	:pieza(posx, posy, tipo_pieza, pieza_num, col)
{
	jaque = false;
}

//Constructor Dama
dama::dama(int posx, int posy, int tipo_pieza, int pieza_num, bool col)
	:pieza(posx, posy, tipo_pieza, pieza_num, col)
{

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

//Verificador del movimiento del peon
bool peon::mover_peon(int n_posx, int n_posy) {

	vector<int> pos_peon_actual;
	pos_peon_actual = pos_actual();

	if ((n_posy - pos_peon_actual[1] > 0) && blanco)
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}
	if ((n_posy - pos_peon_actual[1] < 0) && !blanco)
	{
		cout << "La has liado, intentalo de nuevo" << endl << endl;
		return false;
	}

	if (cant == 0)
	{
		if ((n_posx - pos_peon_actual[0] == 0) && (abs(n_posy - pos_peon_actual[1]) <= 2) && (abs(n_posy - pos_peon_actual[1]) >= 1))
		{
			if (obstaculos_peon_x(pos_peon_actual[0], pos_peon_actual[1], n_posx, n_posy, *tablero_live))
			{
				(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]];
				(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = "XXXX";
				mover(n_posx, n_posy);
				cant++;
				return true;
			}
		}
		else
		{
			cout << "La has liado, intentalo de nuevo" << endl << endl;
			return false;
		}
	}
	else
	{
		if ((n_posx - pos_peon_actual[0] == 0) && abs((n_posy - pos_peon_actual[1])) == 1)
		{
			if (obstaculos_peon_x(pos_peon_actual[0], pos_peon_actual[1], n_posx, n_posy, *tablero_live))
			{

				(*tablero_live)[8 - n_posy][n_posx] = (*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]];
				(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = "XXXX";
				mover(n_posx, n_posy);
				cant++;
				return true;
			}
		}
		else
		{
			cout << "La has liado, intentalo de nuevo" << endl << endl;
			return false;
		}
	}

}

//Verificador mediante el tablero del movimento del peon
bool peon::obstaculos_peon_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
{
	int disty = n_posy - posy;
	if (tablero_directo[((8 - posy) - disty)][n_posx] == "XXXX")
		return true;
	else
	{
		cout << "Hay un obstaculo, elije otro movimiento" << endl;
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
	if (dist > 0)
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx] != "XXXX")
				count++;
		}
	}
	else
	{
		for (i = 1; i <= abs(dist); i++)
		{
			if (tablero_directo[(8 - posy) + i][posx] != "XXXX")
				count++;
		}
	}

	if (count == 0)
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
	if (dist > 0)
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy)][posx + i] != "XXXX")
				count++;
		}
	}
	else
		for (i = 1; i <= abs(dist); i++)
		{
			if (tablero_directo[(8 - posy)][posx - i] != "XXXX")
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
	if (tablero_directo[(8 - posy) - disty][posx + distx] == "XXXX")
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
	dist = abs(dist);
	int i;
	int count = 0;

	switch (quad)
	{
	case 1:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx + i] != "XXXX")
				count++;
		}

		break;
	}
	case 2:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx - i] != "XXXX")
				count++;
		}
		break;
	}
	case 3:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) + i][posx - i] != "XXXX")
				count++;
		}
		break;
	}
	case 4:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) + i][posx + i] != "XXXX")
				count++;
		}
		break;
	}
	}
	if (count == 0)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
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
	if (tablero_directo[(8 - posy) - disty][posx + distx] == "XXXX")
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo denuevo" << endl;
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
	dist = abs(dist);
	int i;
	int count = 0;

	switch (quad)
	{
	case 1:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx + i] != "XXXX")
				count++;
		}

		break;
	}
	case 2:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx - i] != "XXXX")
				count++;
		}
		break;
	}
	case 3:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) + i][posx - i] != "XXXX")
				count++;
		}
		break;
	}
	case 4:
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) + i][posx + i] != "XXXX")
				count++;
		}
		break;
	}
	}
	if (count == 0)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}
}


//Verificador mediante el tablero del movimento de la torre en el eje_x
bool dama::obstaculos_dama_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
{
	int i, dist, count = 0;
	dist = n_posy - posy;
	if (dist > 0)
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy) - i][posx] != "XXXX")
				count++;
		}
	}
	else
	{
		for (i = 1; i <= abs(dist); i++)
		{
			if (tablero_directo[(8 - posy) + i][posx] != "XXXX")
				count++;
		}
	}

	if (count == 0)
		return true;
	else
	{
		cout << "No se puede hacer ese movimiento, intentelo de nuevo" << endl;
		return false;
	}

}

//Verificador mediante el tablero del movimento de la torre en el eje_y
bool dama::obstaculos_dama_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
{
	int i, dist, count = 0;
	dist = n_posx - posx;
	if (dist > 0)
	{
		for (i = 1; i <= dist; i++)
		{
			if (tablero_directo[(8 - posy)][posx + i] != "XXXX")    //problema unicamente al ir hacia la izquierda
				count++;
		}
	}
	else
		for (i = 1; i <= abs(dist); i++)
		{
			if (tablero_directo[(8 - posy)][posx - i] != "XXXX")    //problema unicamente al ir hacia la izquierda
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

//Actualizador de la posicion de la pieza
void pieza::mover(int n_posx, int n_posy)
{
	pos[0] = n_posx;
	pos[1] = n_posy;
	int i, j;
}


//Mostrar datos relavantes a la clase pieza
void pieza::mostrar(void)
{
	cout << endl << "La posicion del \"" << name[num_tipo] << "_" << num_pieza << "\" es:" << endl << "x = " << pos[0] << "\ny = " << pos[1] << endl;
}

//Mostrar datos relecantes a la sub-clase peon
void peon::mostrar(void) {
	pieza::mostrar();

	cout << "Esta pieza ha sido movida " << cant << " veces" << endl;
}

int main()
{
	int i, leer;
	size_t num = 7, x, y;
	int opt;
	char trash;

	bool turno_blanco = true;
	bool bewegung = false;
	vector<string> opciones{ "rey", "dama", "torre", "alfil", "caballo", "peon" };

	vector<vector<string>> matriz;
	vector<vector<string>>& matriz_live = matriz;

	peon* num_p[17];
	torre* num_t[5];
	caballo* num_c[5];
	alfil* num_a[5];
	rey* num_r[3];
	dama* num_d[3];

	for (i = 1; i < 9; i++)
	{
		num_p[i] = new peon(i, 2, 5, i, false);
	}

	for (i = 1; i < 9; i++)
	{
		num_p[i + 8] = new peon(i, 7, 5, i, true);
	}

	num_t[1] = new torre(1, 1, 2, 1, false);
	num_t[2] = new torre(8, 1, 2, 2, false);
	num_t[3] = new torre(1, 8, 2, 1, true);
	num_t[4] = new torre(8, 8, 2, 2, true);

	num_c[1] = new caballo(2, 1, 4, 1, false);
	num_c[2] = new caballo(7, 1, 4, 2, false);
	num_c[3] = new caballo(2, 8, 4, 1, true);
	num_c[4] = new caballo(7, 8, 4, 2, true);

	num_a[1] = new alfil(3, 1, 3, 1, false);
	num_a[2] = new alfil(6, 1, 3, 2, false);
	num_a[3] = new alfil(3, 8, 3, 1, true);
	num_a[4] = new alfil(6, 8, 3, 2, true);

	num_r[1] = new rey(4, 1, 0, 1, false);
	num_r[2] = new rey(4, 8, 0, 1, true);

	num_d[1] = new dama(5, 1, 1, 1, false);
	num_d[2] = new dama(5, 8, 1, 1, true);

	// for (i = 0; i < 8; i++)
	// {
	//	nums[i]->mostrar();
	// }
	//
	leer = Leer_Tablero_2(matriz);
	if (leer != 0)
		return -1;

	while (num <= 8)
	{
		bewegung = false;
		Imprimir_Tablero_2(matriz);
		cout << "\t\t\t\t\t\t\tEs el turno de las piezas de color " << (turno_blanco ? "blanco" : "negro") << endl;

		cout << endl << "Escribe a continuacion que tipo de pieza quieres utlizar:" << endl;
		cout << "1. rey\n" << "2. dama\n" << "3. torre\n" << "4. alfil\n" << "5. caballo\n" << "6. peon \n" << endl;
		do {
			cin >> opt;
		} while ((opt >= 7) || (opt < 1));

		switch (opt)
		{
		case 1:
		{
			//cout << "Usted ha elegido al rey\n";
			if (turno_blanco)
				num_r[2]->mostrar();
			else
				num_r[1]->mostrar();
			break;
		}
		case 2:
		{
			//cout << "Usted ha elegido a la dama\n";
			if (turno_blanco)
				num_d[2]->mostrar();
			else
				num_d[1]->mostrar();
			break;
		}
		case 3:
		{
			//cout << "Usted ha elegido a la torre\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
				cin >> num;
			} while ((num != 1) && (num != 2));
			if (turno_blanco)
				num_t[num + 2]->mostrar();
			else
				num_t[num]->mostrar();
			break;
		}
		case 4:
		{
			//cout << "Usted ha elegido al alfil\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << " quiere utilizar? " << endl;
				cin >> num;
			} while ((num != 1) && (num != 2));
			if (turno_blanco)
				num_a[num + 2]->mostrar();
			else
				num_a[num]->mostrar();
			break;
		}
		case 5:
		{
			//cout << "Usted ha elegido al caballo\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
				cin >> num;
			} while ((num != 1) && (num != 2));
			if (turno_blanco)
				num_c[num + 2]->mostrar();
			else
				num_c[num]->mostrar();
			break;
		}
		case 6:
		{
			//cout << "Usted ha elegido al peon\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
				cin >> num;
			} while ((num < 1) || (num > 8));
			if (turno_blanco)
				num_p[num + 8]->mostrar();
			else
				num_p[num]->mostrar();
			break;
		}
		}

		do {
			cout << "Nueva Posicion en \"x\":" << endl;
			cin >> x;
		} while ((x < 1) || (x > 8));

		do {
			cout << "Nueva Posicion en \"y\":" << endl;
			cin >> y;
		} while ((y < 1) || (y > 8));

		switch (opt)
		{
		case 1:
		{
			//cout << "Usted ha elegido al rey\n";
			if (turno_blanco)
			{
				num_r[2]->tablero_act(matriz_live);
				bewegung = num_r[2]->mover_rey(x, y);
				num_r[2]->mostrar();
			}
			else
			{
				num_r[1]->tablero_act(matriz_live);
				bewegung = num_r[1]->mover_rey(x, y);
				num_r[1]->mostrar();
			}
			break;
		}
		case 2:
		{
			//cout << "Usted ha elegido a la dama\n";
			if (turno_blanco)
			{
				num_d[2]->tablero_act(matriz_live);
				bewegung = num_d[2]->mover_dama(x, y);
				num_d[2]->mostrar();
			}
			else
			{
				num_d[1]->tablero_act(matriz_live);
				bewegung = num_d[1]->mover_dama(x, y);
				num_d[1]->mostrar();
			}
			break;
		}
		case 3:
		{
			//cout << "Usted ha elegido a la torre\n";
			if (turno_blanco)
			{
				num_t[num + 2]->tablero_act(matriz_live);
				bewegung = num_t[num + 2]->mover_torre(x, y);
				num_t[num + 2]->mostrar();
			}
			else
			{
				num_t[num]->tablero_act(matriz_live);
				bewegung = num_t[num]->mover_torre(x, y);
				num_t[num]->mostrar();
			}
			break;
		}
		case 4:
		{
			//cout << "Usted ha elegido al alfil\n";
			if (turno_blanco)
			{
				num_a[num + 2]->tablero_act(matriz_live);
				bewegung = num_a[num + 2]->mover_alfil(x, y);
				num_a[num + 2]->mostrar();
			}
			else
			{
				num_a[num]->tablero_act(matriz_live);
				bewegung = num_a[num]->mover_alfil(x, y);
				num_a[num]->mostrar();
			}
			break;
		}
		case 5:
		{
			//cout << "Usted ha elegido al caballo\n";
			if (turno_blanco)
			{
				num_c[num + 2]->tablero_act(matriz_live);
				bewegung = num_c[num + 2]->mover_caballo(x, y);
				num_c[num + 2]->mostrar();
			}
			else
			{
				num_c[num]->tablero_act(matriz_live);
				bewegung = num_c[num]->mover_caballo(x, y);
				num_c[num]->mostrar();
			}

			break;
		}
		case 6:
		{
			//cout << "Usted ha elegido al peon\n";
			if (turno_blanco)
			{
				num_p[num + 8]->tablero_act(matriz_live);
				bewegung = num_p[num + 8]->mover_peon(x, y);
				num_p[num + 8]->mostrar();
			}
			else
			{
				num_p[num]->tablero_act(matriz_live);
				bewegung = num_p[num]->mover_peon(x, y);
				num_p[num]->mostrar();
			}

			break;
		}
		}
		// num_c[num]->mostrar();
		cout << "Pulse cualquier tecla [...]:" << endl;
		cin >> trash;

		if (bewegung == true)
		{
			turno_blanco = !turno_blanco;
		}

		system("cls");
	}

	return 0;
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
