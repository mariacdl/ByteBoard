#include "Tablero.h"
#include "Pieza.h"
#include "Peon.h"
#include "Torre.h"
#include "Alfil.h"
#include "Rey.h"
#include "Caballo.h"
#include "Dama.h"
#include "Estados.h"
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

Tablero::Tablero(TipoJuego m) : modalidad(m), largura((m == JUEGO_4x5) ? 4 : 5), altura((m == JUEGO_4x5) ? 5 : 6) {
    vista_tablero = new VistaTablero(m);
    lista_piezas.resize(largura * altura, nullptr); // Inicializa con punteros nulos

    if (modalidad == JUEGO_4x5) {
        colocar_pieza({ 0, 0 }, 'R', NEGRO);
        //colocar_pieza({ 0, 1 }, 'C', NEGRO);
        //colocar_pieza({ 0, 2 }, 'A', NEGRO);
        colocar_pieza({ 0, 3 }, 'T', NEGRO);
        colocar_pieza({ 1, 0 }, 'P', NEGRO);

        colocar_pieza({ 4, 3 }, 'R', BLANCO);
        //colocar_pieza({ 4, 2 }, 'C', BLANCO);
        //colocar_pieza({ 4, 1 }, 'A', BLANCO);
        colocar_pieza({ 4, 0 }, 'T', BLANCO);
        //colocar_pieza({ 3, 3 }, 'P', BLANCO);
    }
    else {
        colocar_pieza({ 0, 0 }, 'D', NEGRO);
        colocar_pieza({ 0, 1 }, 'R', NEGRO);
        colocar_pieza({ 0, 2 }, 'A', NEGRO);
        colocar_pieza({ 0, 3 }, 'C', NEGRO);
        colocar_pieza({ 0, 4 }, 'T', NEGRO);
        for (int i = 0; i < 5; i++) colocar_pieza({ 1, i }, 'P', NEGRO);

        colocar_pieza({ 5, 0 }, 'T', BLANCO);
        colocar_pieza({ 5, 1 }, 'C', BLANCO);
        colocar_pieza({ 5, 2 }, 'A', BLANCO);
        colocar_pieza({ 5, 3 }, 'R', BLANCO);
        colocar_pieza({ 5, 4 }, 'D', BLANCO);  // 4 5
        for (int i = 0; i < 5; i++) colocar_pieza({ 4, i }, 'P', BLANCO);
    }
}


Tablero::Tablero(const Tablero& otro)
    : modalidad(otro.modalidad), largura(otro.largura), altura(otro.altura) {
    vista_tablero = new VistaTablero(*otro.vista_tablero);
    lista_piezas.resize(largura * altura, nullptr);
    for (int i = 0; i < lista_piezas.size(); ++i) {
        if (otro.lista_piezas[i] != nullptr)
            // Queria poner un constructor de copia pero ia ser un infierno implementarlo aqui
            lista_piezas[i] = otro.lista_piezas[i]->clonar(); 
    }
}

Tablero::~Tablero() {
    delete vista_tablero;
    for (auto pieza : lista_piezas) delete pieza;
}

void Tablero::dibujar(pair<int, int> casilla_seleccionada, EstadoTurno turno_actual) {
    vista_tablero->dibujar_tablero(*this);
    vista_tablero->dibujar_seleccion(casilla_seleccionada, *this);
    vista_tablero->dibujar_movimientos(casilla_seleccionada, *this, turno_actual);

}

const VistaTablero& Tablero::ver_vista_tablero() const { return *vista_tablero; }
int Tablero::ver_altura() const { return altura; }
int Tablero::ver_largura() const { return largura; }
char Tablero::ver_modalidad() const { return modalidad; }

Pieza* Tablero::ver_pieza(pair<int, int> pos) const {
    int indice = largura * pos.first + pos.second;
    if (indice < 0 || indice >= largura * altura)
        return nullptr;
    else 
        return lista_piezas[largura * pos.first + pos.second];
}

void Tablero::colocar_pieza(pair<int, int> pos, char tipo, EstadoTurno color, int numero_movimientos) {
    int indice = largura * pos.first + pos.second;
    lista_piezas[indice] = nullptr;

    Pieza* nueva = nullptr;
    switch (tipo) {
    case 'P': nueva = new Peon(color); break;
    case 'T': nueva = new Torre(color); break;
    case 'A': nueva = new Alfil(color); break;
    case 'C': nueva = new Caballo(color); break;
    case 'D': nueva = new Dama(color); break;
    case 'R': nueva = new Rey(color); break;
    default: nueva = nullptr;
    }
    lista_piezas[indice] = nueva;
}

void Tablero::colocar_pieza(pair<int, int> origen, pair<int, int> destino) {
    int indice_origen = largura * origen.first + origen.second;
    int indice_destino = largura * destino.first + destino.second;

    lista_piezas[indice_origen]->incrementar_movimiento();
    lista_piezas[indice_destino] = lista_piezas[indice_origen];
    
    lista_piezas[indice_origen] = nullptr;
}

void Tablero::retirar_pieza(pair<int, int> pos) {
    int indice = largura * pos.first + pos.second;
    lista_piezas[indice] = nullptr;
}

void Tablero::mover_pieza(pair<int, int> origen, pair<int, int> destino) {
    Pieza* pieza_origen = ver_pieza(origen);
    Pieza* pieza_destino = ver_pieza(destino);

    cout << "Moviendo " << pieza_origen->ver_tipo() << pieza_origen->ver_color();
    cout << " desde (" << origen.first << ", " << origen.second << ")";
    cout << "para (" << destino.first << ", " << destino.second << ")";
    cout << endl;

    // Al capturar en passat, retira el peon
    if (pieza_origen->ver_tipo() == 'P')
        captura_en_passant(origen, destino);

    // Captura normal
    else if (pieza_destino)
        retirar_pieza(destino);
    
    // Al hacer enroque mueve la torre
    if (pieza_origen->ver_tipo() == 'R')
        mover_enroque(origen, destino);

    // Movimiento normal
    if (pieza_origen)
        colocar_pieza(origen, destino);
}

bool Tablero::validar_movimiento(pair<int, int> origen, pair<int, int> destino, bool determinar_jaque) const {
    Pieza* pieza = ver_pieza(origen);
    if (pieza == nullptr) 
        return false;
    else
        return  pieza->validar_movimiento(origen, destino, *this, determinar_jaque);
}

vector<pair<int, int>> Tablero::listar_movimientos_validos(pair<int, int> casilla, EstadoTurno turno_actual) const {
    vector<pair<int, int>> movimientos_validos;

    // Verificar si la pieza es del jugador
    Pieza* pieza = ver_pieza(casilla);
    if (pieza->ver_color() != turno_actual)
        return movimientos_validos; 

    for (int x = 0; x < altura; ++x) {
        for (int y = 0; y < largura; ++y) {
            pair<int, int> destino = { x, y };

            // Primero verificar si el movimiento es válido en sí (sin considerar jaque)
            if (validar_movimiento(casilla, destino)) {
                // Simular movimiento en una copia profunda del tablero
                Tablero copia = *this;
                copia.mover_pieza(casilla, destino);

                // Si después del movimiento el rey propio NO queda en jaque
                if (!copia.determinar_jaque(turno_actual)) 
                    movimientos_validos.push_back(destino);
            }
        }
    }
    cout << "Movimientos validos para " << pieza->ver_tipo() << pieza->ver_color();
    for (auto m : movimientos_validos)
        cout << " (" << m.first << ", " << m.second << ")";
    cout << endl;
    return movimientos_validos;
}

bool Tablero::determinar_jaque(EstadoTurno color) const {
    pair<int, int> pos_rey = { -1, -1 };

    // Buscar la posición del rey del color actual
    for (int i = 0; i < lista_piezas.size(); ++i) {
        Pieza* pieza = lista_piezas[i];
        if (pieza != nullptr) {
            if (pieza->ver_color() == color && pieza->ver_tipo() == 'R') {
                pos_rey = { i / largura, i % largura };
                break;
            }
        }
    }

    // Si no se encontró el rey, no hay jaque
    if (pos_rey.first == -1)
        return false;

    // Buscar todas las piezas enemigas
    // Par pieza y posicion de pieza enemiga
    vector<pair<Pieza*, pair<int, int>>> lista_pieza_posicion_enemiga; 
    for (int i = 0; i < lista_piezas.size(); ++i) {
        Pieza* pieza = lista_piezas[i];
        if (pieza != nullptr) {
            if (pieza->ver_color() != color) {
                pair<int, int> pos_enemiga = { i / largura, i % largura };
                lista_pieza_posicion_enemiga.push_back({ pieza, pos_enemiga });
            }
        }
    }

    // Verificar si alguna pieza enemiga puede capturar al rey
    for (const auto& pieza_posicion_enemiga : lista_pieza_posicion_enemiga) {
        const Pieza* pieza = pieza_posicion_enemiga.first;
        const pair<int, int>& pos_enemiga = pieza_posicion_enemiga.second;


        if (validar_movimiento(pos_enemiga, pos_rey, true))
            return true; // El rey está en jaque
    }

    // Ninguna pieza enemiga amenaza al rey
    return false;
}

const vector<Pieza*>& Tablero::listar_piezas() const {
    return lista_piezas;
}

void Tablero::captura_en_passant(pair<int, int>origen, pair<int, int> destino) {
    Pieza* pieza = ver_pieza(origen);

    int direccion = (pieza->ver_color() == BLANCO) ? -1 : 1;
    pair<int, int> pos_peon_avance_doble = { destino.first - direccion, destino.second };

    Pieza* peon_avance_doble = ver_pieza(pos_peon_avance_doble);
    if (peon_avance_doble != nullptr)
        if(peon_avance_doble->ver_tipo() == 'P' && 
            peon_avance_doble->ver_numero_movimientos() == 1 &&
            peon_avance_doble->ver_color() != pieza->ver_color())
            retirar_pieza(pos_peon_avance_doble);
}

void Tablero::mover_enroque(pair<int, int>origen, pair<int, int> destino) {
    Pieza* rey = ver_pieza(origen);

    // Verificar si es enroque
    if (origen.first == destino.first && abs(destino.second - origen.second) == 2) {

        // Enroque corto a la derecha
        bool es_enroque_corto = (destino.second - origen.second > 0);

        int fila = origen.first;

        pair<int, int> origen_torre;
        pair<int, int> destino_torre;

        if (es_enroque_corto) {
            // Enroque corto 
            origen_torre = { fila, ver_largura() - 1 };              // torre en la esquina derecha
            destino_torre = { fila, origen.second + 1 };             // torre justo al lado derecho del rey antes de enroque
        }
        else {
            // Enroque largo 
            origen_torre = { fila, 0 };                              // torre en la esquina izquierda
            destino_torre = { fila, origen.second - 1 };             // torre justo al lado izquierda del rey antes de enroque
        }

        Pieza* torre = ver_pieza(origen_torre);

        if (torre != nullptr)
            if(torre->ver_tipo() == 'T' && torre->ver_numero_movimientos() == 0 && torre->ver_color() == rey->ver_color())
                mover_pieza(origen_torre, destino_torre);
    }
}