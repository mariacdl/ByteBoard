#pragma once
#include <vector>
#include <utility>
#include "VistaTablero.h"
#include <Estados.h>

class Pieza;

using namespace std;

class Tablero {
private:
    VistaTablero* vista_tablero;

    TipoJuego modalidad;
    int largura = 0;
    int altura = 0;
    vector<Pieza*> lista_piezas;

public:
    Tablero(TipoJuego m);
    ~Tablero();

    void dibujar(pair<int, int> casilla_seleccionada);
    const VistaTablero& ver_vista_tablero() const;

    int ver_altura() const;
    int ver_largura() const;
    char ver_modalidad() const;
    Pieza* ver_pieza(pair<int, int> pos) const;
    void colocar_pieza(pair<int, int> pos, char tipo, EstadoTurno color, int numero_movimientos = 0);
    void retirar_pieza(pair<int, int> pos);
    void mover_pieza(pair<int, int> origen, pair<int, int> destino);
    const vector<Pieza*>& listar_piezas() const;
    bool validar_movimiento(pair<int, int> origen, pair<int, int> destino) const;
    vector<pair<int, int>> listar_movimientos_validos(pair<int, int> casilla) const;
};