#include "DibujanteTablero.h"
#include "freeglut.h"

void DibujanteTablero::dibujarTablero() {
    glPushMatrix();
    glTranslatef(-tablero.ver_ancho() * tam / 2.0f, 0.0f, -tablero.ver_largo() * tam / 2.0f); // Centra el tablero en el origen para que quede simétrico

    dibujarMarco(); //dibuja el marco

    for (int i = 0; i < tablero.ver_largo(); i++)
    {
        for (int j = 0; j < tablero.ver_ancho(); j++)
        {
            bool esBlanca = (i + j) % 2 != 0;// Alterna blanco y negro
            glColor3f(esBlanca ? 1.0f : 0.0f, esBlanca ? 1.0f : 0.0f, esBlanca ? 1.0f : 0.0f);

            glPushMatrix();
            glTranslatef((tablero.ver_ancho() - 1 - j) * tam, 0.0, i * tam);// Posiciona la casilla en el tablero (j invertido para rotar el tablero visualmente)
            // Dibuja la casilla como un cuadrado (quad)
            glBegin(GL_QUADS);
            glVertex3f(0, 0, 0);
            glVertex3f(tam, 0, 0);
            glVertex3f(tam, 0, tam);
            glVertex3f(0, 0, tam);
            glEnd();
            glPopMatrix();
        }
    }
    glPopMatrix();

    dibujantepiezas->dibujar(tam);
}

void DibujanteTablero::dibujarMarco() {
    float grosor = tam * 0.3f;// grosor del marco exterior
    float alto = tam * 0.01f; // altura del marco
    float tableroAncho = (tablero.ver_ancho() * tam);
    float tableroLargo = (tablero.ver_largo() * tam);

    float x0 = 0.0f;
    float z0 = 0.0f;
    float x1 = tableroAncho;
    float z1 = tableroLargo;

    glColor3f(0.25f, 0.13f, 0.03f);

    glBegin(GL_QUADS); // Lado inferior
    glVertex3f(x0 - grosor, 0, z0 - grosor);
    glVertex3f(x1 + grosor, 0, z0 - grosor);
    glVertex3f(x1, alto, z0);
    glVertex3f(x0, alto, z0);
    glEnd();
    glBegin(GL_QUADS);// Lado superior
    glVertex3f(x0 - grosor, 0, z1 + grosor);
    glVertex3f(x1 + grosor, 0, z1 + grosor);
    glVertex3f(x1, alto, z1);
    glVertex3f(x0, alto, z1);
    glEnd();
    glBegin(GL_QUADS);// Lado izquierdo
    glVertex3f(x0 - grosor, 0, z0 - grosor);
    glVertex3f(x0 - grosor, 0, z1 + grosor);
    glVertex3f(x0, alto, z1);
    glVertex3f(x0, alto, z0);
    glEnd();
    glBegin(GL_QUADS);// Lado derecho
    glVertex3f(x1 + grosor, 0, z0 - grosor);
    glVertex3f(x1 + grosor, 0, z1 + grosor);
    glVertex3f(x1, alto, z1);
    glVertex3f(x1, alto, z0);
    glEnd();
}

void DibujanteTablero::dibujarSeleccion(int fila, int columna, GLfloat r, GLfloat g, GLfloat b) {
    float origenX = -((tablero.ver_ancho() * tam) / 2.0f);
    float origenZ = -((tablero.ver_largo() * tam) / 2.0f);

    float posX = origenX + columna * tam;
    float posZ = origenZ + fila * tam;

    glPushMatrix();
    glTranslatef(posX + tam / 2.0f, 0.01f, posZ + tam / 2.0f);  // posicionar el plano por encima del tablero
    glColor3f(r, g, b);

    glBegin(GL_QUADS); //plano con tamaño de casilla
    glVertex3f(-tam / 2.0f, 0.0f, -tam / 2.0f);
    glVertex3f(-tam / 2.0f, 0.0f, tam / 2.0f);
    glVertex3f(tam / 2.0f, 0.0f, tam / 2.0f);
    glVertex3f(tam / 2.0f, 0.0f, -tam / 2.0f);
    glEnd();

    glPopMatrix();
}

void DibujanteTablero::dibujarMovimientos(int fila, int columna) {
    const vector<pair<int, int>>& lista_jugadas_validas = tablero.listar_movimientos_validos(columna, fila);
    for (const auto& jugada_valida : lista_jugadas_validas) {
        dibujarSeleccion(jugada_valida.second, jugada_valida.first, 1.0f, 1.0f, 0.0f);
    }
}

float DibujanteTablero::getTam() const {
    return tam;
}