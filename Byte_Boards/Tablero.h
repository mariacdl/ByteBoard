#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Pieza.h"

class Tablero {
private:
    int altura, largura;
    std::vector<Pieza> lista_piezas;

public:
    Tablero(int altura, int largura);
    void dibujar();
    void dibujar_terminal();
    void colocar_pieza(int pos_x, int pos_y, char tipo, char color);
    void retirar_pieza(int pos_x, int pos_y);
    bool verificar_movimiento(int position_x, int position_y, int next_position_x, int next_position_y);
    std::vector<Pieza> listar_piezas();
    
    int ver_altura();
    int ver_largura();
};
