#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Pieza.h"

using namespace std;

class Tablero {
private:
    int ancho;
    int largo;
    vector<Pieza> lista_piezas;

public:
    Tablero(){}
    Tablero(int altura, int largura);
    int ver_largo() const;
    int ver_ancho() const;
    Pieza getPieza(int pos_x,int pos_y) const;
    void colocar_pieza(int pos_x, int pos_y, char tipo, char color, int numero_movimiento=0);
    void retirar_pieza(int pos_x, int pos_y);
    void mover_pieza(int de_x, int de_y, int para_x, int para_y);
};