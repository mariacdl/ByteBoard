

#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
};

class peon : public pieza {
private:
	int cant;
public:
	peon(int posx, int posy, int tipo_pieza, int pieza_num);
	void mostrar(void);
};


pieza::pieza(int posx, int posy, int tipo_pieza, int pieza_num)
{
	pos[0] = posx;
	pos[1] = posy;
	num_tipo = tipo_pieza;
	num_pieza = pieza_num;
}

peon::peon(int posx, int posy, int tipo_pieza, int pieza_num)
	:pieza(posx, posy, tipo_pieza, pieza_num)
{
	cant = 0;
}
void pieza::mostrar(void)
{
	cout << "La posicion de la pieza de tipo " << name[num_tipo] << " y numero \"" << num_pieza << "\" es " << pos[0] << " en \"x\", y " << pos[1] << " en \"y\"" << endl;
}

void peon::mostrar(void) {
	pieza::mostrar();

	cout << "Esta pieza ha sido movida " << cant << " veces" << endl << endl;
}

int main()
{
	int i, j, k;
	pieza* nums[16];
	for (i = 0; i < 8; i++)
	{
		nums[i] = new peon(i + 1, 2, 5, i + 1);
	}

	for (i = 0; i < 8; i++)
	{
		nums[i]->mostrar();
	}

	return 0;
}
