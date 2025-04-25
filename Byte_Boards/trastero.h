#include "Alfil.h"
#include "Caballo.h"
#include "Dama.h"
#include "Peon.h"
#include "Pieza.h"
#include "Rey.h"
#include "Torre.h"
#include "Tablero.h"

struct Death_ID {
	int num_tipo;
	int num_pieza;
	int blanc;
};

struct datos_damas
{
	int C_D_T;		//Cantidad Damas Totales
	int C_D_B;		//Cantidad Damas Blancas
	int C_D_N;		//Cantidad Damas Negras
	vector<int> conv_B_T;
	vector<int> conv_N_T;
};

struct datos_torres
{
	int C_T_T;		//Cantidad Torres Totales
	int C_T_B;		//Cantidad Torres Blancas
	int C_T_N;		//Cantidad Torres Negras
	vector<int> conv_B_T;
	vector<int> conv_N_T;
};

struct datos_alfiles
{
	int C_A_T;		//Cantidad Alfiles Totales
	int C_A_B;		//Cantidad Alfiles Blancas
	int C_A_N;		//Cantidad Alfiles Negras
	vector<int> conv_B_T;
	vector<int> conv_N_T;
};

struct datos_caballos
{
	int C_C_T;		//Cantidad Caballos Totales
	int C_C_B;		//Cantidad Caballos	Blancos
	int C_C_N;		//Cantidad Caballos Negros
	vector<int> conv_B_T;
	vector<int> conv_N_T;
};


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
