#include "Pieza.h"

//Clase Torre
class Torre : public Pieza {
private:
	bool mov_t;
public:
	Torre(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_torre(int n_posx, int n_posy);
	void mover_torre(int tipo);
	bool obstaculos_torre_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool obstaculos_torre_y(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool mov_torre(void);
};