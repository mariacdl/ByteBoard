#pragma once
#include "Pieza.h"

//Clase Alfil
class Alfil : public Pieza {
private:

public:
	Alfil(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_alfil(int n_posx, int n_posy);
	bool obstaculos_alfil_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad);
};