#include "Pieza.h"

//Clase Caballo
class Caballo : public Pieza {
private:

public:
	Caballo(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_caballo(int n_posx, int n_posy);
	bool obstaculos_caballo_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	//bool obstaculos_caballo_xY(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};