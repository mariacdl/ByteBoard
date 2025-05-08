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
    int altura, largura;
    vector<Pieza> lista_piezas;

public:
    Tablero(int altura, int largura);
    int ver_altura();
    int ver_largura();
    void dibujar();
    void dibujar_terminal();
    void dibujar_terminal(const vector<pair<int, int>>& selecionados);
    void colocar_pieza(int pos_x, int pos_y, char tipo, char color);
    void retirar_pieza(int pos_x, int pos_y);
    void mover_pieza(int de_x, int de_y, int para_x, int para_y);
    bool verificar_movimiento(int position_x, int position_y, int next_position_x, int next_position_y);
    vector<Pieza> listar_piezas();
    vector<pair<int, int>> listar_movimientos_validos(int position_x, int position_y);
};
