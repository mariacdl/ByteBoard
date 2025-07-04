#pragma once
#include <vector>
#include <utility>
#include "VistaTablero.h"
#include <Estados.h>

class Pieza;

using namespace std;

class Tablero {
protected:
    VistaTablero* vista_tablero;

    TipoJuego modalidad;
    int largura = 0;
    int altura = 0;
    vector<Pieza*> lista_piezas;
    

public:
    Tablero(TipoJuego m);
    Tablero(const Tablero& otro);
    ~Tablero();

    void dibujar(pair<int, int> casilla_seleccionada, vector<pair<int, int>> ultimos_movimientos_validos);
    const VistaTablero& ver_vista_tablero() const;

    int ver_altura() const;
    int ver_largura() const;
    char ver_modalidad() const;
    
    Pieza* ver_pieza(pair<int, int> pos) const;
    const vector<Pieza*>& listar_piezas() const;

    void colocar_pieza(pair<int, int> pos, char nuevo_tipo);
    void colocar_pieza(pair<int, int> origen, pair<int, int> destino);
    void colocar_pieza(pair<int, int> pos, char tipo, EstadoTurno color, int numero_movimientos = 0);

    void retirar_pieza(pair<int, int> pos);
    void mover_pieza(pair<int, int> origen, pair<int, int> destino);

    void captura_en_passant(pair<int, int>origen, pair<int, int> destino);
    void mover_enroque(pair<int, int>origen, pair<int, int> destino);

    vector<pair<int, int>> listar_movimientos_validos(pair<int, int> casilla, EstadoTurno turno_actual) const;
    bool validar_movimiento(pair<int, int> origen, pair<int, int> destino, bool determinar_jaque = false) const;
    bool determinar_jaque(EstadoTurno color) const;

    pair<int, int> ver_peon_promocionable() const;

    bool verificar_falta_material() const;
};