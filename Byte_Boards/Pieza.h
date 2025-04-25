#pragma once
#include <vector>
#include <string>

using namespace std;

//Clase Pieza
class Pieza {
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
	Pieza(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	void mover(int n_posx, int n_posy);
	void tablero_act(vector<vector<string>>& tablero_directo);
	virtual void mostrar(void);
	vector<int> pos_actual(void);
	void Juicio_final(int tipo_muerto, int num_muerto, int blanco_muerto); // Este Juicio final determina si ha muerto una pieza
	void Juicio_final(int num_tipo_mejora); // Este juicio final apaga a los peones ascendidos
	bool obituary(void);
};