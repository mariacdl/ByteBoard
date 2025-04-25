#include "Peon.h"
#include "Tablero.h"

//Constructor Peon
Peon::Peon(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live)
	:Pieza(posx, posy, tipo_pieza, pieza_num, col, live)
{
	cant = 0;
}

//Verificador del movimiento del peon
bool Peon::mover_peon(int n_posx, int n_posy) {

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
bool Peon::obstaculos_peon_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int cant_mov)
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
bool Peon::obstaculos_peon_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo)
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

//Verificador de que el peon blanco / negro no ha llegado al otro lado del tablero
vector<int> Peon::comp_tope_peon(void)
{
	vector<int> pos_peon_actual = pos_actual();
	int premio_tope;
	vector<int> premio_escogido{ 0,0 };	//Posicion del peon en el eje x, y la recompensa escogida
	if (blanco)
	{
		if (pos_peon_actual[1] == 1)
		{
			cout << endl << "Has llegado con el peon al otro lado del tablero, ahora puedes elejir convertirlo en:" << endl;
			cout << "1. Dama" << endl << "2. Torre" << endl << "3. Alfil" << endl << "4. Caballo" << endl;
			cin >> premio_tope;
			premio_escogido[0] = pos_peon_actual[0];
			premio_escogido[1] = premio_tope;
			return premio_escogido;
		}
		else return premio_escogido;
	}
	if (!blanco)
	{
		if (pos_peon_actual[1] == 8)
		{
			cout << endl << "Has llegado con el peon al otro lado del tablero, ahora puedes elejir convertirlo en:" << endl;
			cout << "1. Dama" << endl << "2. Torre" << endl << "3. Alfil" << endl << "4. Caballo" << endl;
			cin >> premio_tope;
			premio_escogido[0] = pos_peon_actual[0];
			premio_escogido[1] = premio_tope;
			return premio_escogido;
		}
		else return premio_escogido;
	}
}

//Se encarga de actualizar en el tablero a un peon en una pieza mejorada
void Peon::transductor_peon_a_premio(int num_tipo_mejora, int num_pieza_mejora, bool blanche)
{
	vector<int> pos_peon_actual;
	pos_peon_actual = pos_actual();

	switch (num_tipo_mejora)
	{
	case 1:
	{
		string puzle;
		string pieza_1 = to_string(num_pieza_mejora);
		string pieza_2 = (blanche ? "B" : "N");
		puzle = "D" + pieza_1 + "_" + pieza_2;
		(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = puzle;
		break;
	}
	case 2:
	{
		string puzle;
		string pieza_1 = to_string(num_pieza_mejora);
		string pieza_2 = (blanche ? "B" : "N");
		puzle = "T" + pieza_1 + "_" + pieza_2;
		(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = puzle;
		break;
	}
	case 3:
	{
		string puzle;
		string pieza_1 = to_string(num_pieza_mejora);
		string pieza_2 = (blanche ? "B" : "N");
		puzle = "A" + pieza_1 + "_" + pieza_2;
		(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = puzle;
		break;
	}
	case 4:
	{
		string puzle;
		string pieza_1 = to_string(num_pieza_mejora);
		string pieza_2 = (blanche ? "B" : "N");
		puzle = "C" + pieza_1 + "_" + pieza_2;
		(*tablero_live)[8 - pos_peon_actual[1]][pos_peon_actual[0]] = puzle;
		break;
	}

	}
}


//Mostrar datos relecantes a la sub-clase peon
void Peon::mostrar(void) {
	Pieza::mostrar();

	cout << "Esta pieza ha sido movida " << cant << " veces" << endl;
}