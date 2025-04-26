#include "tablero.h"
#include "freeglut.h"

Tablero::Tablero(int filas, int columnas, double tam)
    : filas(filas), columnas(columnas), tam(tam) {}

void Tablero::dibujar() 
{
    float tamCasilla = tam;

    //Centrar el tablero en la ventana
    float offsetX = -((columnas * tam) / 2.0f);
    float offsetZ = -((filas * tam) / 2.0f);
    glTranslatef(offsetX, 0.0f, offsetZ);

    dibujarMarco(tamCasilla, filas, columnas);

    for (int i = 0; i < filas; i++) 
    {
        for (int j = 0; j < columnas; j++) 
        {
            bool esBlanca = (i + j) % 2 == 0;
            if (esBlanca)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);

            glPushMatrix();
            glTranslatef(j * tam, 0.0, i * tam);
            glBegin(GL_QUADS);
            glVertex3f(0, 0, 0);
            glVertex3f(tam, 0, 0);
            glVertex3f(tam, 0, tam);
            glVertex3f(0, 0, tam);
            glEnd();
            glPopMatrix();
        }
    }
}
void Tablero::dibujarMarco(float tamCasilla, int filas, int columnas) {
    
    float grosor = tamCasilla * 0.3f;
    float alto = tamCasilla * 0.01f;
    float tableroAncho = (columnas * tamCasilla);
    float tableroLargo = (filas * tamCasilla);

    float x0 = 0.0f;
    float z0 = 0.0f;
    float x1 = tableroAncho;
    float z1 = tableroLargo;

    glColor3f(0.25f, 0.13f, 0.03f);

    glBegin(GL_QUADS);
    glVertex3f(x0 - grosor, 0, z0 - grosor);
    glVertex3f(x1 + grosor, 0, z0 - grosor);
    glVertex3f(x1, alto, z0);
    glVertex3f(x0, alto, z0);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(x0 - grosor, 0, z1 + grosor);
    glVertex3f(x1 + grosor, 0, z1 + grosor);
    glVertex3f(x1, alto, z1);
    glVertex3f(x0, alto, z1);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(x0 - grosor, 0, z0 - grosor);
    glVertex3f(x0 - grosor, 0, z1 + grosor);
    glVertex3f(x0, alto, z1);
    glVertex3f(x0, alto, z0);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(x1 + grosor, 0, z0 - grosor);
    glVertex3f(x1 + grosor, 0, z1 + grosor);
    glVertex3f(x1, alto, z1);
    glVertex3f(x1, alto, z0);
    glEnd();
}