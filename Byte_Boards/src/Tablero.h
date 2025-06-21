#pragma once
#include <vector>
#include <utility>
#include "VistaTablero.h"

class Pieza;

using namespace std;

class Tablero {
private:
    VistaTablero* vista_tablero;

    char modalidad;
    int ancho = 0;
    int largo = 0;
    vector<Pieza*> lista_piezas;

public:
    Tablero(char m);
    ~Tablero();

    void dibujar(pair<int, int> casilla_seleccionada);
    const VistaTablero& ver_vista_tablero() const;

    int ver_largo() const;
    int ver_ancho() const;
    char ver_modalidad() const;
    Pieza* ver_pieza(pair<int, int> pos) const;
    void colocar_pieza(pair<int, int> pos, char tipo, char color, int numero_movimientos = 0);
    void retirar_pieza(pair<int, int> pos);
    void mover_pieza(pair<int, int> origen, pair<int, int> destino);
    const vector<Pieza*>& listar_piezas() const;
    bool validar_movimiento(pair<int, int> origen, pair<int, int> destino) const;
    vector<pair<int, int>> listar_movimientos_validos(pair<int, int> casilla) const;
};