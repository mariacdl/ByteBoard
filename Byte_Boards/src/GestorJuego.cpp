#include <iostream>
#include "GestorJuego.h"
#include "freeglut.h"

void GestorJuego::procesarClick(int x, int y) {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);
    int centroY = alto / 2;

    if (estado == MENU_TABLERO) {
        //área clic para elegir tablero 4x5
        int y_inicio_4x5 = centroY - 60;
        int y_fin_4x5 = centroY + 30;
        //área clic para elegir tablero speed chess
        int y_inicio_speed = centroY + 50;
        int y_fin_speed = centroY + 160;
        //botón 4x5
        if (y >= y_inicio_4x5 && y <= y_fin_4x5) {
            modoSeleccionado = 'P';
            estado = MENU_MODO_JUEGO;
        }
        //botón speed chess
        else if (y >= y_inicio_speed && y <= y_fin_speed) {
            modoSeleccionado = 'S';
            estado = MENU_MODO_JUEGO;
        }
    }
    else if (estado == MENU_MODO_JUEGO) {
        //diferentes áreas de clic
        int y_inicio_2player = centroY - 60;
        int y_fin_2player = centroY + 30;
        int y_inicio_IA = centroY + 50;
        int y_fin_IA = centroY + 170;
        int y_inicio_volver = centroY - 280;
        int y_fin_volver = centroY - 170;
        //botón ciencias vs letras
        if (y >= y_inicio_2player && y <= y_fin_2player) {
            tipoJuego = 1;
            estado = EN_JUEGO;
            partida = new Partida(modoSeleccionado, 'B');
            dibujantetablero = new DibujanteTablero(partida->ver_tablero(), modoSeleccionado);
            cout << "Partida inciada" << endl;
        }
        //botón vs IA
        else if (y >= y_inicio_IA && y <= y_fin_IA) {
            tipoJuego = 2;
            estado = EN_JUEGO;
        }
        //botón para volver
        else if (y >= y_inicio_volver && y <= y_fin_volver) {
            estado = MENU_TABLERO;
        }
    }
    else if (estado == PAUSA) {
        //diferentes áreas de clic
        int y_inicio_renaudar = centroY - 40;
        int y_fin_renaudar = centroY + 50;
        int y_inicio_salir = centroY + 70;
        int y_fin_salir = centroY + 200;
        //botón para salir
        if (y >= y_inicio_salir && y <= y_fin_salir) {
            tipoJuego = 1;
            estado = MENU_TABLERO;
        }
        //botón renaudar
        else if (y >= y_inicio_renaudar && y <= y_fin_renaudar) {
            estado = EN_JUEGO;
        }
    }
    else if (estado == PROMOCION_SPEED) {
        int yBoton = alto - y;  //invertir Y si el origen está abajo
        char prom = '0';

        if (x >= 200 && x <= 600) {
            if (yBoton >= 400 && yBoton <= 500)
                prom = 'D';
            else if (yBoton >= 300 && yBoton <= 400)
                prom = 'T';
            else if (yBoton >= 200 && yBoton <= 280)
                prom = 'A';
            else if (yBoton >= 100 && yBoton <= 180)
                prom = 'C';
        }
        if (prom != '0') {
            if (partida->promocionar(prom)) {
                estado = EN_JUEGO;
                //Detectar fin de la partida
                char fin = partida->det_fin();

                if (fin == 'B') {
                    cout << "Victoria para las letras" << endl;
                    estado = VICTORIA_LETRAS;
                }
                else if (fin == 'N') {
                    cout << "Victoria para las ciencias" << endl;
                    estado = VICTORIA_CIENCIAS;
                }
                else if (fin == 'T') {
                    cout << "Tablas" << endl;
                    estado = TABLAS;
                }
            }
        }
    }
    else if (estado == PROMOCION_4x5) {
        int yBoton = alto - y;  // invertir Y si el origen está abajo
        char prom = '0';

        if (x >= 200 && x <= 600) {
            if (yBoton >= 400 && yBoton <= 500)
                prom = 'T';
            else if (yBoton >= 240 && yBoton <= 300)
                prom = 'A';
            else if (yBoton >= 160 && yBoton <= 220)
                prom = 'C';
        }
        if (prom != '0') {
            if (partida->promocionar(prom)) {
                estado=EN_JUEGO;
                //Detectar fin de la partida
                char fin = partida->det_fin();

                if (fin == 'B') {
                    cout << "Victoria para las letras" << endl;
                    estado=VICTORIA_LETRAS;
                }
                else if (fin == 'N') {
                    cout << "Victoria para las ciencias" << endl;
                    estado=VICTORIA_CIENCIAS;
                }
                else if (fin == 'T') {
                    cout << "Tablas" << endl;
                    estado=TABLAS;
                }
            }
        }
    }
    else if (estado == EN_JUEGO) {
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

        float origenX = -((partida->ver_tablero().ver_ancho() * dibujantetablero->getTam()) / 2.0f);
        float origenZ = -((partida->ver_tablero().ver_largo()* dibujantetablero->getTam()) / 2.0f);
        columna = (int)((posX - origenX) / dibujantetablero->getTam());
        fila = (int)((posZ - origenZ) / dibujantetablero->getTam());

        if (fila >= 0 && fila < partida->ver_tablero().ver_largo() &&
            columna >= 0 && columna < partida->ver_tablero().ver_ancho()) {
            if (!fichaSeleccionada) {
                fichaSeleccionada = true;
                columnaSeleccionada = columna;
                filaSeleccionada = fila;
                mostrarPlanoSeleccion = true;
            }
            else {
                bool alternar = false;
                Pieza pieza1 = partida->ver_tablero().getPieza(columnaSeleccionada, filaSeleccionada);
                Pieza pieza2 = partida->ver_tablero().getPieza(columna, fila);

                //Enroque
                if (pieza1.ver_tipo() == 'R' &&
                    (columna == columnaSeleccionada - 2 || columna == columnaSeleccionada + 2) &&
                    fila == filaSeleccionada &&
                    pieza1.ver_color() == partida->ver_turno()) {
                    if (partida->jugar(pieza1.ver_color())) {
                        alternar = true;
                    }
                }
                //Movimiento simple
                else {
                    if (partida->jugar(columnaSeleccionada, filaSeleccionada, columna, fila)) {
                        alternar = true;
                    }

                    if (partida->getPromocion().first != -1) {
                        estado=(partida->ver_modalidad() == 'P') ? PROMOCION_4x5 : PROMOCION_SPEED;
                    }
                }
                if (alternar && estado == EN_JUEGO) {
                    //Detectar fin de la partida
                    char fin = partida->det_fin();

                    if (fin == 'B') {
                        cout << "Victoria para las letras" << endl;
                        estado=VICTORIA_LETRAS;
                    }
                    else if (fin == 'N') {
                        cout << "Victoria para las ciencias" << endl;
                        estado=VICTORIA_CIENCIAS;
                    }
                    else if (fin == 'T') {
                        cout << "Tablas" << endl;
                        estado=TABLAS;
                    }
                }
                fichaSeleccionada = false;
                mostrarPlanoSeleccion = false;
                columnaSeleccionada = -1;
                filaSeleccionada = -1;
            }
        }
    }
    else if (estado == VICTORIA_CIENCIAS || estado == VICTORIA_LETRAS || estado == TABLAS) {
    estado = MENU_TABLERO;
    return;
    }
    glutPostRedisplay();
}

void GestorJuego::procesarTecla(unsigned char key) {
    if (key == 27) { // 27 = ESC ; pausar en medio del juego
        if (estado == EN_JUEGO)
            estado=PAUSA;
        else if (estado == PAUSA)
            estado=EN_JUEGO;
        else if (estado == VICTORIA_CIENCIAS || estado == VICTORIA_LETRAS || estado == TABLAS) {
            estado = MENU_TABLERO;
        }
        glutPostRedisplay();
    }
}

void GestorJuego::dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (estado == MENU_TABLERO)
    {
        dibujantemenus.dibujarMenuTablero();
    }
    else if (estado == MENU_MODO_JUEGO) {
        dibujantemenus.dibujarMenuModoJuego();
    }
    else if (estado == PAUSA) {
        dibujantemenus.dibujarMenuPausa();
    }
    else if (estado == PROMOCION_SPEED) {
        dibujantemenus.dibujarMenuPromSpeed();
    }
    else if (estado == PROMOCION_4x5) {
        dibujantemenus.dibujarMenuProm4x5();
    }
    else if (estado == VICTORIA_CIENCIAS) {
        dibujantemenus.dibujarMenuVicCiencias();
    }
    else if (estado == VICTORIA_LETRAS) {
        dibujantemenus.dibujarMenuVicLetras();
    }
    else if (estado == TABLAS) {
        dibujantemenus.dibujarMenuTablas();
    }
    else if (estado == EN_JUEGO) {
    gluPerspective(40.0, glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 150.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    char turnoActual = partida->ver_turno();//inicia la espera antes de cambiar de turno
    static char ultimoTurno = turnoActual;
    if (turnoActual != ultimoTurno) {
        esperandoGiro = true;
        framesEspera = 0;
        ultimoTurno = turnoActual;
    }
    if (esperandoGiro) {
        framesEspera++;
        if (framesEspera >= delayFrames) {
            esperandoGiro = false;
        }
    }
    if (!esperandoGiro) {
        anguloCamaraObjetivo = (turnoActual == 'N') ? 180.0f : 0.0f;
    }
    if (!esperandoGiro) {
        float velocidad = 0.05f;
        anguloCamara += (anguloCamaraObjetivo - anguloCamara) * velocidad;
    }

    float rad = anguloCamara * 3.14159f / 180.0f; //convertimos grados a radianes
    float camX = 10.0f * sin(rad);//se define la posicion de la camara
    float camZ = 10.0f * cos(rad);
    gluLookAt(camX, 10.0f, camZ,  
        0.0f, 0.0f, 0.0f,    
        0.0f, 1.0f, 0.0f);

    GLfloat luzPos[] = { camX, 10.0f, camZ, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, luzPos);
    dibujantetablero->dibujarTablero();

    if (mostrarPlanoSeleccion) {
        dibujantetablero->dibujarSeleccion(filaSeleccionada, columnaSeleccionada);
        }
    }
    glutSwapBuffers();
}

GestorJuego::~GestorJuego() {
    delete dibujantetablero;
    delete partida;
}
