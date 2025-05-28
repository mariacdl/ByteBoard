#pragma once
#include "Configuracion.h"

class Oponente; // Para evitar loop infinito de includes

using namespace std;

class Partida {
private:
    Tablero tablero;
    char turno_actual='B'; // 'B' o 'N'
    char color_jugador1; //'B' o 'N'
    char modalidad; //'P' o 'S'
    pair<int,int> peon_passant={-1,-1};

    bool verificar_movimiento(int de_x, int de_y, int para_x, int para_y);
    bool det_passant(int de_x, int de_y, int para_x, int para_y);
    vector<pair<int, int>> listar_movimientos_validos(int position_x, int position_y);
    void alternar_turno();
public:
    Partida(char modalidad, Configuracion& config, char color_jugador1 = 'B');
    bool jugar(int de_x, int de_y, int para_x, int para_y);
    bool jugar(char color);
    bool mover(int de_x, int de_y, int para_x, int para_y);
    bool enrocar(char color);
    void mover_oponente(int de_x, int de_y, int para_x, int para_y);
    bool det_jaque(char color);
    bool det_jaque_mate(char color);
    bool det_fin();
    char ver_turno() const;

    
    /*void jugar();
    void dibujar_terminal();
    void jugar_terminal();
    */
};