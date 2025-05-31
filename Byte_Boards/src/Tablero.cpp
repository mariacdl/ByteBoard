#include "Tablero.h"
#include "Pieza.h"

using namespace std;

Tablero::Tablero(int ancho,int largo) {
	this->ancho=ancho;
	this->largo=largo;
	lista_piezas.resize(ancho*largo);
}

void Tablero::colocar_pieza(int pos_x, int pos_y, char tipo, char color, int numero_movimiento) {
	lista_piezas[ancho* pos_y + pos_x] = Pieza(tipo, color, numero_movimiento);
}

void Tablero::retirar_pieza(int pos_x, int pos_y) {
	lista_piezas[ancho * pos_y + pos_x] = Pieza('0', '0',0); // Pieza vacía
}

void Tablero::mover_pieza(int de_x, int de_y, int para_x, int para_y) {
	Pieza pieza = lista_piezas[ancho * de_y + de_x];

	colocar_pieza(para_x, para_y, pieza.ver_tipo(), pieza.ver_color(), pieza.ver_numero_movimiento()+1);
	retirar_pieza(de_x, de_y);
}

Pieza Tablero::getPieza(int pos_x,int pos_y){
	return lista_piezas[ancho * pos_y + pos_x];
}

int Tablero::ver_largo() {
	return largo;
}

int Tablero::ver_ancho() {
	return ancho;
}




/*
void Tablero::dibujar_terminal() {
	cout << endl << "    ";
	for (int x = 0; x < largura; ++x) {
		cout << x << "  ";
	}
	cout << endl;
	for (int y = 0; y < altura; ++y) {
		cout << " " << y << " ";

		for (int x = 0; x < largura; ++x) {
			int index = largura * y + x;
			Pieza pieza = lista_piezas[index];

			if (pieza.ver_tipo() == '0') {
				cout << "__ "; // vazio
			}
			else {
				if (pieza.ver_color() == 'N')
					cout << "\033[34m" << pieza.ver_tipo() << "N\033[0m ";
				else cout << pieza.ver_tipo() << "B ";
				
			}
		}
		cout << endl;
	}
}


// Selection overload
void Tablero::dibujar_terminal(const vector<pair<int, int>>& selecionados) {
	cout << endl << "    ";
	for (int x = 0; x < largura; ++x) {
		cout << x << "  ";
	}
	cout << endl;

	for (int y = 0; y < altura; ++y) {
		cout << " " << y << " ";

		for (int x = 0; x < largura; ++x) {
			int index = largura * y + x;
			Pieza pieza = lista_piezas[index];

			bool selecionado = find(selecionados.begin(), selecionados.end(), make_pair(x, y)) != selecionados.end();

			if (selecionado) cout << "\033[100m";

			if (pieza.ver_tipo() == '0') {
				cout << "__"; // vazio
			}
			else {
				if (pieza.ver_color() == 'N')
					cout << "\033[34m" << pieza.ver_tipo() << "N\033[0m";
				else cout << pieza.ver_tipo() << "B";

			}
			if (selecionado)
				cout << "\033[0m";

			cout << " ";
		}
		cout << endl;
	}
}
*/