#pragma once
#include "Tablero.h"
#include <utility>
#include <vector>
#include <VistaPartida.h>

using namespace std;

class Partida {
private:
    VistaPartida* vista_partida;
    Tablero* tablero;
    int numero_turnos = 0;
    char turno_actual='B'; // 'B' o 'N'
    char color_jugador1; //'B' o 'N'
    char modalidad; //'P' o 'S'

    pair<int, int> promocion = { -1,-1 };
    pair<int, int> peon_passant = { -1,-1 };
    pair<int, int> casilla_seleccionada = { -1,-1 };

    vector<char> promocionesB;
    vector<char> promocionesN;

    bool verificar_movimiento(pair<int, int> desde, pair<int, int> para);
    vector<pair<int, int>> listar_movimientos_validos(pair<int, int> casilla);
    void alternar_turno();
public:
    Partida(char m = 'P', char c = 'B');
    ~Partida();

    void dibujar();
    void actualizar_casilla(pair<int, int>casilla_nueva);


    bool jugar(pair<int, int> desde, pair<int, int> para); //Movimiento simple
    bool jugar(char color); //Enroque
    bool mover(pair<int, int> desde, pair<int, int> para);
    bool enrocar(char color);
    bool determinar_jaque(char color);
    bool sin_movimientos_validos(char color);
    bool determinar_jaque_mate(char color);
    char determinar_fin();
    bool promocionar(char tipo);
    pair<int,int> getPromocion();
    char ver_turno() const;
    int ver_numero_turnos() const;
    char ver_modalidad() const;
    const Tablero& ver_tablero() const;
};