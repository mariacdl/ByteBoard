

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Imprimir_Tablero(void);

//Clase Pieza
class pieza {
private:
	int pos[2];
	vector <string> name{ "rey", "dama", "torre", "alfil", "caballo", "peon" };
	int num_tipo;
	int num_pieza;

public:
	pieza(int posx, int posy, int tipo_pieza, int pieza_num);
	void mover(int n_posx, int n_posy);
	virtual void mostrar(void);
	vector<int> pos_actual(void);
};

//Clase Peon
class peon : public pieza {
private:
	int cant;
public:
	peon(int posx, int posy, int tipo_pieza, int pieza_num);
	void mover_peon(int n_posx, int n_posy);
	void mostrar(void);

};

//Clase Torre
class torre : public pieza {
private:

public:
	torre(int posx, int posy, int tipo_pieza, int pieza_num);
	void mover_torre(int n_posx, int n_posy);
};

//Constructor pieza
pieza::pieza(int posx, int posy, int tipo_pieza, int pieza_num)
{
	pos[0] = posx;
	pos[1] = posy;
	num_tipo = tipo_pieza;
	num_pieza = pieza_num;
}

//Constructor Peon
peon::peon(int posx, int posy, int tipo_pieza, int pieza_num)
	:pieza(posx, posy, tipo_pieza, pieza_num)
{
	cant = 0;
}

//Constructor Torre
torre::torre(int posx, int posy, int tipo_pieza, int pieza_num)
	:pieza(posx, posy, tipo_pieza, pieza_num)
{

}

//Posicion actual pieza
vector<int> pieza::pos_actual(void)
{
	vector<int> pos_act{ pos[0], pos[1] };
	return pos_act;
}

//Verificador del movimiento del peon
void peon::mover_peon(int n_posx, int n_posy) {

	vector<int> pos_peon_actual;
	pos_peon_actual = pos_actual();

	// cout << endl << endl << "*** La posicion actual de ese peon en \"x\" es " << pos_peon_actual[0] << "y " << pos_peon_actual[1] << "en \"y\"***" << endl;
	// cout << "*** Segun lo que me dices, la nueva posicion que quieres es " << n_posx << "en \"x\", y " << n_posy << "en \"y\"***";

	if (cant == 0)
	{
		if ((n_posx - pos_peon_actual[0] == 0) && (n_posy - pos_peon_actual[1] <= 2) && (n_posy - pos_peon_actual[1] >= 1))
		{
			mover(n_posx, n_posy);
			cant++;
		}
		else
			cout << "La has liado, intentalo de nuevo" << endl << endl;
	}
	else
		if (cant != 0)
		{
			if ((n_posx - pos_peon_actual[0] == 0) && (n_posy - pos_peon_actual[1] == 1))
			{
				mover(n_posx, n_posy);
				cant++;
			}
			else
				cout << "La has liado, intentalo de nuevo" << endl << endl;
		}

}

// Verificador del movimiento de la torre
void torre::mover_torre(int n_posx, int n_posy)
{
	vector<int> pos_torre_actual;
	pos_torre_actual = pos_actual();

	if ((n_posx - pos_torre_actual[0] == 0) && (n_posy - pos_torre_actual[1] != 0))
	{
		mover(n_posx, n_posy);
	}
	else if ((n_posy - pos_torre_actual[1] == 0) && (n_posx - pos_torre_actual[0] != 0))
	{
		mover(n_posx, n_posy);
	}
	else
		cout << "La has liado, intentalo de nuevo" << endl << endl;

}

//Actualizador de la posicion de la pieza
void pieza::mover(int n_posx, int n_posy)
{
	pos[0] = n_posx;
	pos[1] = n_posy;
}


//Mostrar datos relavantes a la clase pieza
void pieza::mostrar(void)
{
	cout << endl << "La posicion de la pieza de tipo " << name[num_tipo] << " y numero \"" << num_pieza << "\" es " << pos[0] << " en \"x\", y " << pos[1] << " en \"y\"" << endl;
}

//Mostrar datos relecantes a la sub-clase peon
void peon::mostrar(void) {
	pieza::mostrar();

	cout << "Esta pieza ha sido movida " << cant << " veces" << endl << endl;
}

int main()
{
	//Imprimir_Tablero();

	int i;
	size_t num = 7, x, y, z;
	int opt;
	char trash;
	vector<string> opciones{ "rey", "dama", "torre", "alfil", "caballo", "peon" };
	// pieza *nums[17];
	peon* num_p[9];
	torre* num_t[3];

	for (i = 1; i < 9; i++)
	{
		num_p[i] = new peon(i, 2, 5, i);
	}

	num_t[1] = new torre(1, 1, 2, 1);
	num_t[2] = new torre(8, 1, 2, 2);

	// for (i = 0; i < 8; i++)
	// {
	//	nums[i]->mostrar();
	// } 
	//
	while (num <= 8)
	{
		//Imprimir_Tablero();
		cout << "Escribe a continuacion que tipo de pieza quieres utlizar:" << endl;
		cout << "1. rey\n" << "2. dama\n" << "3. torre\n" << "4. alfil\n" << "5. caballo\n" << "6. peon \n" << endl;

		do {
			cin >> opt;
		} while ((opt > 7) || (opt < 1));


		switch (opt)
		{
		case 1:
		{
			//cout << "Usted ha elegido al rey\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << "quiere utilizar? " << endl;
				cin >> num;
			} while (num != 1);
			break;
		}
		case 2:
		{
			//cout << "Usted ha elegido a la dama\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << "quiere utilizar? " << endl;
				cin >> num;
			} while (num != 1);
			break;
		}
		case 3:
		{
			do {
				cout << "Que numero de " << opciones[opt - 1] << "quiere utilizar? " << endl;
				cin >> num;
			} while ((num != 1) && (num != 2));
			//cout << "Usted ha elegido a la torre\n";
			num_t[num]->mostrar();
			break;
		}
		case 4:
		{
			//cout << "Usted ha elegido al alfil\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << "quiere utilizar? " << endl;
				cin >> num;
			} while ((num != 1) && (num != 2));
			break;
		}
		case 5:
		{
			//cout << "Usted ha elegido al caballo\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << "quiere utilizar? " << endl;
				cin >> num;
			} while ((num != 1) && (num != 2));
			break;
		}
		case 6:
		{
			//cout << "Usted ha elegido al peon\n";
			do {
				cout << "Que numero de " << opciones[opt - 1] << "quiere utilizar? " << endl;
				cin >> num;
			} while ((num < 1) || (num > 8));
			num_p[num]->mostrar();
			break;
		}
		}

		do {
			cout << endl << "Nueva Posicion en \"x\":" << endl;
			cin >> x;
		} while ((x < 1) || (x > 8));

		do {
			cout << endl << "Nueva Posicion en \"y\":" << endl;
			cin >> y;
		} while ((y < 1) || (y > 8));

		switch (opt)
		{
		case 1:
		{
			//cout << "Usted ha elegido al rey\n";
			break;
		}
		case 2:
		{
			//cout << "Usted ha elegido a la dama\n";
			break;
		}
		case 3:
		{
			//cout << "Usted ha elegido a la torre\n";
			num_t[num]->mover_torre(x, y);
			break;
		}
		case 4:
		{
			//cout << "Usted ha elegido al alfil\n";
			break;
		}
		case 5:
		{
			//cout << "Usted ha elegido al caballo\n";
			break;
		}
		case 6:
		{
			//cout << "Usted ha elegido al peon\n";
			num_p[num]->mover_peon(x, y);
			break;
		}
		}
		cout << "Pulse cualquier tecla [...]:" << endl;
		cin >> trash;
		system("cls");
	}

	return 0;
}

void Imprimir_Tablero(void)
{
	size_t i, j, k = 2, y;
	cout << "\t\tTamblero de Ajedrez" << endl << endl;
	for (i = 0; i < 8; i++)
	{

		for (y = 0; y < 3; y++)
		{
			if (y == 1)
				cout << "POSICION EN Y: " << 8 - i << "\t\t";
			else
				cout << "                \t\t";
			if (i != 6)
			{
				for (j = 0; j < 8; j++)
				{
					if ((j + k) % 2 == 0)
					{
						cout << "||||||";
					}
					else
						cout << "      ";
				}
			}
			else
				for (j = 0; j < 8; j++)
				{
					if ((j + k) % 2 == 0)
					{
						cout << "||PP||";
					}
					else
						cout << "  PP  ";
				}

			cout << endl;
		}

		k++;
	}
	cout << endl << endl << "POSICION EN X: \t\t\t";
	cout << "  1      2     3     4     5     6     7     8" << endl;

}