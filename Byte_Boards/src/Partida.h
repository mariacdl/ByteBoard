#pragma once
#include "Tablero.h"
#include <utility>
#include <vector>

using namespace std;

class Partida {
private:
    Tablero tablero;
    char turno_actual='B'; // 'B' o 'N'
    char color_jugador1; //'B' o 'N'
    char modalidad; //'P' o 'S'
    pair<int,int> promocion={-1,-1};
    pair<int,int> peon_passant={-1,-1};
    vector<char> promocionesB;
    vector<char> promocionesN;

    bool verificar_movimiento(int de_x, int de_y, int para_x, int para_y);
    vector<pair<int, int>> listar_movimientos_validos(int position_x, int position_y);
    void alternar_turno();
public:
    Partida(char m, char c = 'B') : tablero(m), modalidad(m), color_jugador1(c) {};
    bool jugar(int de_x, int de_y, int para_x, int para_y); //Movimiento simple
    bool jugar(char color); //Enroque
    bool mover(int de_x, int de_y, int para_x, int para_y);
    bool enrocar(char color);
    bool det_jaque(char color);
    bool det_jaque_mate(char color);
    char det_fin();
    bool promocionar(char tipo);
    pair<int,int> getPromocion();
    char ver_turno() const;
    char ver_modalidad() const;
    const Tablero& ver_tablero() const;
};