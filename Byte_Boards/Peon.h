#include "Pieza.h"

//Clase Peon
class Peon : public Pieza {
private:
	int cant;
public:
	Peon(int posx, int posy, int tipo_pieza, int pieza_num, bool col, bool live);
	bool mover_peon(int n_posx, int n_posy);
	void mostrar(void);
	bool obstaculos_peon_x(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo, int cant_mov);
	bool obstaculos_peon_xy(int posx, int posy, int n_posx, int n_posy, vector<vector<string>> tablero_directo); // Esta funcion servirá para comer en diagonal
	vector<int> comp_tope_peon(void);
	void transductor_peon_a_premio(int num_tipo_mejora, int num_pieza_mejora, bool blanche);
};