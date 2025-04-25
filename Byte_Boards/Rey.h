#include "Pieza.h"

//Clase Rey
class Rey : public Pieza {
private:
	bool jaque;
	bool mov_r;
public:
	Rey(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	int mover_rey(int n_posx, int n_posy, bool mov_torre_Iz, bool mov_torre_Dch);
	bool obstaculos_rey_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo);
	bool comp_jaque(void);
	bool comp_jaque_xy(int posx, int posy, vector<vector<string>> tablero_directo);
	bool comp_jaque_x(int posx, int posy, vector<vector<string>> tablero_directo);
	bool comp_jaque_y(int posx, int posy, vector<vector<string>> tablero_directo);
	bool comp_jaque_caballo(int posx, int posy, vector<vector<string>> tablero_directo);
	bool verificador_enroque(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, bool m_t_I, bool m_t_D);
};