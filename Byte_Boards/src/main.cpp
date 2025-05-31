#include "freeglut.h"
#include "DTablero.h"
#include <iostream>
#include "DMenu.h"
#include"DFichas.h"
#include "Partida.h"

//Creación de las clases principales
DTablero tablero(0,0,0);
DMenu menu;
Partida partida('0','0');

// Para manejar selección
bool fichasInicializadas = false;
bool fichaSeleccionada = false;
bool mostrarPlanoSeleccion = false;
int filaSeleccionada = -1;
int columnaSeleccionada = -1;

void OnDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    EstadoJuego estado = menu.getEstado();

    if (estado == MENU_TABLERO || estado == MENU_MODO_JUEGO || estado == PAUSA||estado==PROMOCION||estado == VICTORIA_CIENCIAS || estado == VICTORIA_LETRAS) {
        menu.dibujarMenu(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    }
    else if (estado == EN_JUEGO) {
        gluPerspective(40.0, glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 150.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if (partida.ver_turno() == 'N') {
            gluLookAt(0, 10, -10,
                0, 0, 0,
                0, 1, 0);
            GLfloat luzPos[] = { 1.0f, 10.0f, -10.0f, 0.0f }; // luz desde detrás del jugador
            glLightfv(GL_LIGHT0, GL_POSITION, luzPos);
        }
        else {
            gluLookAt(0, 10, 10,
                0, 0, 0,
                0, 1, 0);
            GLfloat luzPos[] = { 1.0f, 10.0f, 10.0f, 0.0f }; // luz desde detrás del jugador
            glLightfv(GL_LIGHT0, GL_POSITION, luzPos);
        }
        tablero.dibujar();

        //  Dibujar todas las fichas
        for (int x = 0;x<tablero.getColumnas();x++) {
            for (int y = 0; y < tablero.getFilas(); y++) {
                Pieza pieza = partida.ver_tablero().getPieza(x, y);
                if (pieza.ver_tipo() == 'P') {
                    DFichas* dibujante_pieza=(pieza.ver_color()=='B') ? static_cast<DFichas*>(new PeonCiencias(x,y,true)) : static_cast<DFichas*>(new PeonLetras(x, y, true));
                    dibujante_pieza->dibujar(tablero);
                }
                else if (pieza.ver_tipo() == 'T') {
                    DFichas* dibujante_pieza = (pieza.ver_color() == 'B') ? static_cast<DFichas*>(new TorreCiencias(x, y, true)) : static_cast<DFichas*>(new TorreLetras(x, y, true));
                    dibujante_pieza->dibujar(tablero);
                }
                else if (pieza.ver_tipo() == 'C') {
                    DFichas* dibujante_pieza = (pieza.ver_color() == 'B') ? static_cast<DFichas*>(new CaballoCiencias(x, y, true)) : static_cast<DFichas*>(new CaballoLetras(x, y, true));
                    dibujante_pieza->dibujar(tablero);
                }
                else if (pieza.ver_tipo() == 'A') {
                    DFichas* dibujante_pieza = (pieza.ver_color() == 'B') ? static_cast<DFichas*>(new AlfilCiencias(x, y, true)) : static_cast<DFichas*>(new AlfilLetras(x, y, true));
                    dibujante_pieza->dibujar(tablero);
                }
                else if (pieza.ver_tipo() == 'R') {
                    DFichas* dibujante_pieza = (pieza.ver_color() == 'B') ? static_cast<DFichas*>(new ReyCiencias(x, y, true)) : static_cast<DFichas*>(new ReyLetras(x, y, true));
                    dibujante_pieza->dibujar(tablero);
                }
                else if (pieza.ver_tipo() == 'D') {
                    DFichas* dibujante_pieza = (pieza.ver_color() == 'B') ? static_cast<DFichas*>(new ReinaCiencias(x, y, true)) : static_cast<DFichas*>(new ReinaLetras(x, y, true));
                    dibujante_pieza->dibujar(tablero);
                }
            }
        }

        if (mostrarPlanoSeleccion) {
            tablero.dibujarSeleccion(filaSeleccionada, columnaSeleccionada);
        }   
    }

    glutSwapBuffers();
}

void OnMouseClick(int button, int state, int x, int y) {
    static bool inicio_juego = true;
    char prom = '0';

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        menu.procesarClick(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), &prom);
        EstadoJuego estado = menu.getEstado();

        if (prom != '0') {
            partida.promocionar(prom);
            prom = '0';
        }
        if (estado == EN_JUEGO) {
            if (inicio_juego) {
                partida = Partida(menu.getModoSeleccionado(), 'B');
                tablero = (menu.getModoSeleccionado() == 'P') ? DTablero(5, 4, 1.5) : DTablero(6, 5, 1.3);
                inicio_juego = false;
                cout << "Partida inciada"<<endl;
                return;
            }

            //  Gestión del clic en el tablero
            GLint viewport[4];
            GLdouble modelview[16], projection[16];
            GLfloat winX, winY, winZ;
            GLdouble posX, posY, posZ;

            glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
            glGetDoublev(GL_PROJECTION_MATRIX, projection);
            glGetIntegerv(GL_VIEWPORT, viewport);

            winX = (float)x;
            winY = (float)viewport[3] - (float)y;
            glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
            gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

            int fila = -1, columna = -1;

            float origenX = -((tablero.getColumnas() * tablero.getTam()) / 2.0f);
            float origenZ = -((tablero.getFilas() * tablero.getTam()) / 2.0f);
            columna = (int)((posX - origenX) / tablero.getTam());
            fila = (int)((posZ - origenZ) / tablero.getTam());

            if (fila >= 0 && fila < tablero.getFilas() &&
                columna >= 0 && columna < tablero.getColumnas()) {

                if (!fichaSeleccionada) {
                    fichaSeleccionada = true;
                    columnaSeleccionada = columna;
                    filaSeleccionada = fila;
                    mostrarPlanoSeleccion = true;
                }
                else {
                    Pieza pieza1 = partida.ver_tablero().getPieza(columnaSeleccionada,filaSeleccionada);
                    Pieza pieza2 = partida.ver_tablero().getPieza(columna, fila);

                    //Enroque
                    if (pieza1.ver_color() == pieza2.ver_color() && ((pieza1.ver_tipo() == 'R' && pieza2.ver_tipo() == 'T') || (pieza1.ver_tipo() == 'T' && pieza2.ver_tipo() == 'R'))) {
                        partida.jugar(pieza1.ver_color());
                    }
                    //Movimiento simple
                    else {
                        partida.jugar(columnaSeleccionada, filaSeleccionada, columna, fila);

                        if (partida.getPromocion().first != -1) {
                            menu.iniciarPromocion();
                        }
                    }
                    //Detectar fin de la partida
                    char fin = partida.det_fin();
                    if (fin == 'B') {
                        menu.setEstado(VICTORIA_LETRAS);
                    }
                    else if (fin == 'N') {
                        menu.setEstado(VICTORIA_CIENCIAS);
                    }
                    else if (fin == 'T') {
                        menu.setEstado(TABLAS);
                    }
                    fichaSeleccionada = false;
                    mostrarPlanoSeleccion = false;
                    columnaSeleccionada = -1;
                    filaSeleccionada = -1;
                }
            }
        }
        if (estado == PAUSA || estado == EN_JUEGO || estado == PROMOCION) {
            inicio_juego = false;
        }
        else {
            inicio_juego = true;
        }
    }
    glutPostRedisplay();
}



void OnKeyboard(unsigned char key, int x, int y) {
    if (key == 27) { // 27 = ESC ; pausar en medio del juego
        if (menu.getEstado() == EN_JUEGO)
            menu.setEstado(PAUSA);
        else if (menu.getEstado() == PAUSA)
            menu.setEstado(EN_JUEGO);
        glutPostRedisplay();
    }
}
void OnTimer(int value) {
    glutTimerFunc(25, OnTimer, 0);
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutCreateWindow("Ajedrez");

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

    glutDisplayFunc(OnDraw);
    glutMouseFunc(OnMouseClick);
    glutKeyboardFunc(OnKeyboard);
    glutTimerFunc(25, OnTimer, 0);//llamar en 25ms
    glutMainLoop();
    return 0;
}
