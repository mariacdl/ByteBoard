#pragma once

#include "freeglut.h"
#include "DTablero.h"

class DFichas {
protected:
    int fila, columna;
    bool esBlanca;

public:
    DFichas(int columna, int fila, bool blanca):  columna(columna), fila(fila), esBlanca(blanca) {}

    virtual char getTipo() const = 0;

    int getFila() const { return fila; }
    int getColumna() const { return columna; }
    bool blanca() const { return esBlanca; }
    //metodo para cambiar coordenadas
    void setCoordenadas(int nuevaColumna, int nuevaFila) {
        fila = nuevaFila;
        columna = nuevaColumna;
    }
    virtual void dibujar(const DTablero& tablero) = 0;//permite que cada ficha defina su forma en pantalla
    virtual ~DFichas() {}
};
// Peón de ciencias
class PeonCiencias : public DFichas {
public:
    PeonCiencias(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'P'; }// Letra identificadora
    char promocionar(int x, int y);
};
//Torre de ciencias
class TorreCiencias : public DFichas {
public:
    TorreCiencias(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}

    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'T'; }// Letra identificadora
};
//caballo de ciencias
class CaballoCiencias : public DFichas {
public:
    
    CaballoCiencias(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'C'; }// Letra identificadora
};
//Alfil de ciencias
class AlfilCiencias : public DFichas {
public:
    AlfilCiencias(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}

    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'A'; }// Letra identificadora
};
//Rey de ciencias
class ReyCiencias : public DFichas {
public:
    ReyCiencias(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'R'; }
};
//Reina de ciencias
class ReinaCiencias : public DFichas {
public:
    ReinaCiencias(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'D'; }
};
//Peón de letras
class PeonLetras : public DFichas {
public:
    PeonLetras(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}

    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'p'; }// Letra identificadora
};
//Torre de letras
class TorreLetras : public DFichas {
public:
    TorreLetras(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}

    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 't'; }// Letra identificadora
};
//Caballo de letras
class CaballoLetras : public DFichas {
public:

    CaballoLetras(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'c'; }// Letra identificadora
};
//Alfil de letras
class AlfilLetras : public DFichas {
public:
    AlfilLetras(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}

    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'a'; }// Letra identificadora
};
//Rey de letras
class ReyLetras : public DFichas {
public:
    ReyLetras(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'r'; }
};
//Reina de letras
class ReinaLetras : public DFichas {
public:
    ReinaLetras(int columna, int fila, bool blanca) : DFichas(columna, fila, blanca) {}
    void dibujar(const DTablero& tablero) override;
    char getTipo() const override { return 'q'; }
};
