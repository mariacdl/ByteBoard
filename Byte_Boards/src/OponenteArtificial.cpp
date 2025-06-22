#include "OponenteArtificial.h"
#include "Pieza.h"
#include <cmath>
#include <random>
#include <limits>
#include <iostream>

using namespace std;

EstadoTurno OponenteArtificial::ver_color() const {
    return color;
}


// Asigna puntuación a una jugada simple (por pieza capturada)
int OponenteArtificial::puntuar_jugada(Tablero& tablero, pair<int, int> origen, pair<int, int> destino) {
    Pieza* destino_pieza = tablero.ver_pieza(destino);
    if (!destino_pieza) return 0;

    switch (destino_pieza->ver_tipo()) {
    case 'P': return 10;
    case 'C': return 30;
    case 'A': return 30;
    case 'T': return 50;
    case 'D': return 90;
    case 'R': return 1000; // Capturar rey debería terminar juego
    default: return 0;
    }
}

// Explora todas las jugadas posibles y elige una buena
pair<pair<int, int>, pair<int, int>> OponenteArtificial::elegir_proxima_jugada(Tablero& tablero) {
    vector<pair<pair<int, int>, pair<int, int>>> mejores_jugadas;
    int mejor_puntaje = std::numeric_limits<int>::min();

    cout << "Avaliando jugadas posibles" << endl;

    for (int x = 0; x < tablero.ver_altura(); ++x) {
        for (int y = 0; y < tablero.ver_largura(); ++y) {
            pair<int, int> origen = { x, y };
            Pieza* pieza = tablero.ver_pieza(origen);
            if (pieza && pieza->ver_color() == color) {
                auto destinos = tablero.listar_movimientos_validos(origen, color);
                for (auto& destino : destinos) {
                    int puntaje = puntuar_jugada(tablero, origen, destino);
                    if (puntaje > mejor_puntaje) {
                        mejor_puntaje = puntaje;
                        mejores_jugadas.clear();
                        mejores_jugadas.push_back({ origen, destino });
                    }
                    else if (puntaje == mejor_puntaje) {
                        mejores_jugadas.push_back({ origen, destino });
                    }
                }
            }
        }
    }

    // Elegir aleatoriamente entre las mejores si hay varias
    if (!mejores_jugadas.empty()) {
        random_device rd;
        mt19937 gen(rd());

        if (temperatura > 0.1f && mejores_jugadas.size() > 1) {
            uniform_int_distribution<> dis(0, mejores_jugadas.size() - 1);
            return mejores_jugadas[dis(gen)];
        }
        else {
            return mejores_jugadas[0]; // determinista
        }
    }

    // Si no hay movimientos válidos (debería significar jaque mate o ahogado)
    return { {-1, -1}, {-1, -1} };
}
