#pragma once
#include "Tablero.h"
#include <utility>
#include <vector>
#include <VistaPartida.h>
#include <Estados.h>

using namespace std;

class Partida {
private:
    VistaPartida* vista_partida;
    Tablero* tablero;
    int numero_turnos = 0;
    EstadoTurno turno_actual; 
    EstadoTurno color_jugador1;
    TipoJuego modalidad; 

    pair<int, int> promocion = { -1,-1 };
    pair<int, int> peon_passant = { -1,-1 };
    pair<int, int> casilla_seleccionada = { -1,-1 };

    bool rey_negro_en_jaque = false;
    bool rey_blanco_en_jaque = false;

    vector<char> promocionesB;
    vector<char> promocionesN;

    bool verificar_movimiento(pair<int, int> desde, pair<int, int> para, bool jaque);
    vector<pair<int, int>> listar_movimientos_validos(pair<int, int> casilla);
    void alternar_turno();
public:
    Partida(TipoJuego m = JUEGO_4x5, EstadoTurno c = BLANCO);
    ~Partida();

    const Tablero& ver_tablero() const;

    void dibujar();
    void actualizar_casilla(pair<int, int>casilla_nueva);

    int ver_numero_turnos() const;
    char ver_turno() const;
    char ver_modalidad() const;

    void jugar(pair<int, int> desde, pair<int, int> para);
    bool validar_jugada(pair<int, int> desde, pair<int, int> para);

    void promocionar(char nuevo_tipo) const;
};