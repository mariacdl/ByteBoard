#include "Pieza.h"

//Clase Dama
class Dama : public Pieza {
private:

public:
	Dama(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_dama(int n_posx, int n_posy);
	bool obstaculos_dama_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int quad);
	bool obstaculos_dama_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool obstaculos_dama_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
};