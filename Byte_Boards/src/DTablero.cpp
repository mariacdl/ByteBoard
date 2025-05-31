#include "DTablero.h"
#include "freeglut.h"
#include <iostream>


void DTablero::dibujar()
{
    float tamCasilla = tam;

    glPushMatrix();
    glTranslatef(-columnas * tam / 2.0f, 0.0f, -filas * tam / 2.0f); // Centra el tablero en el origen para que quede simétrico

    dibujarMarco(tamCasilla, filas, columnas); //dibuja el marco

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            bool esBlanca = (i + j) % 2 != 0;// Alterna blanco y negro
            glColor3f(esBlanca ? 1.0f : 0.0f, esBlanca ? 1.0f : 0.0f, esBlanca ? 1.0f : 0.0f);

            glPushMatrix();
            glTranslatef((columnas - 1 - j) * tam, 0.0, i * tam);// Posiciona la casilla en el tablero (j invertido para rotar el tablero visualmente)
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
}

void DTablero::dibujarMarco(float tamCasilla, int filas, int columnas) {
    
    float grosor = tamCasilla * 0.3f;// grosor del marco exterior
    float alto = tamCasilla * 0.01f; // altura del marco
    float tableroAncho = (columnas * tamCasilla);
    float tableroLargo = (filas * tamCasilla);

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

void DTablero::dibujarSeleccion(int fila, int columna) {
    float tam = getTam();  // tamaño de cada casilla
    float origenX = -((getColumnas() * tam) / 2.0f);
    float origenZ = -((getFilas() * tam) / 2.0f);

    float posX = origenX + columna * tam;
    float posZ = origenZ + fila * tam;

    glPushMatrix();
    glTranslatef(posX + tam / 2.0f, 0.01f, posZ + tam / 2.0f);  // posicionar el plano por encima del tablero
    glColor3f(0.0f, 1.0f, 0.0f);  

    glBegin(GL_QUADS);//plano con tamaño de casilla
    glVertex3f(-tam / 2.0f, 0.0f, -tam / 2.0f);
    glVertex3f(-tam / 2.0f, 0.0f, tam / 2.0f);
    glVertex3f(tam / 2.0f, 0.0f, tam / 2.0f);
    glVertex3f(tam / 2.0f, 0.0f, -tam / 2.0f);
    glEnd();

    glPopMatrix();
}

