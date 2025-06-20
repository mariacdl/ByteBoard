#pragma once
#include <vector>

class Pieza;

using namespace std;

class Tablero {
private:
    int ancho = 0;
    int largo = 0;
    char modalidad;
    vector<Pieza*> lista_piezas;

public:
    Tablero(char modalidad, int ancho, int largo) : modalidad(modalidad), ancho(ancho), largo(largo) {};
    Tablero(char modalidad) ;
    ~Tablero();
    int ver_largo() const;
    int ver_ancho() const;
    char ver_modalidad() const;
    Pieza* ver_pieza(int pos_x,int pos_y) const;
    void colocar_pieza(int pos_x, int pos_y, char tipo, char color, int numero_movimientos = 0);
    void retirar_pieza(int pos_x, int pos_y);
    void mover_pieza(int de_x, int de_y, int para_x, int para_y);
    const vector<Pieza*>& listar_piezas() const;
};