﻿#include "Oponente.h"
#include "Pieza.h"
#include <vector>
#include <cstdlib> // Para randomizacion

int Oponente::puntuar_jugada(Tablero& tablero, pair<int, int> origen, pair<int, int> destino) {
    vector<Pieza*> piezas = tablero.listar_piezas();
    int ancho = tablero.ver_ancho();
    int index_destino = destino.second * ancho + destino.first;
    Pieza* objetivo = piezas[index_destino];

    // Asignar valor a la pieza capturada (puedes refinar esto)
    switch (objetivo->ver_tipo()) {
    case 'P': return 1;
    case 'C': return 3;
    case 'A': return 3;
    case 'T': return 5;
    case 'D': return 9;
    case 'R': return 100;
    default: return 0;
    }
}

pair<pair<int, int>, pair<int, int>> Oponente::elegir_proxima_jugada(Tablero& tablero) {
    //vector<pair<pair<int, int>, pair<int, int>>> todas_las_jugadas;

    //vector<Pieza*> piezas = tablero.listar_piezas();
    //int ancho = tablero.ver_ancho();
    //int largo = tablero.ver_largo();

    //int mejor_puntaje = -1;
    //pair<pair<int, int>, pair<int, int>> mejor_jugada = { {-1, -1}, {-1, -1} };

    //for (int y = 0; y < largo; ++y) {
    //    for (int x = 0; x < ancho; ++x) {
    //        Pieza* pieza = piezas[y * largo + x];
    //        if (pieza->ver_color() == color) {
    //            auto movimientos = tablero.listar_movimientos_validos(x, y);
    //            for (auto& destino : movimientos) {
    //                int puntaje = puntuar_jugada(tablero, { x, y }, destino);
    //                if (puntaje > mejor_puntaje) {
    //                    mejor_puntaje = puntaje;
    //                    mejor_jugada = { {x, y}, destino };
    //                }
    //            }
    //        }
    //    }
    //}

    //if (todas_las_jugadas.empty()) {
    //    return { {-1, -1}, {-1, -1} }; // No hay jugadas v�lidas
    //}

    //return mejor_jugada;
}