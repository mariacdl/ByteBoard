#define _USE_MATH_DEFINES 
#include "VistaPartida.h"
#include "freeglut.h"
#include <cmath> 


void VistaPartida::actualizar_camara(EstadoTurno turno_actual) {
    if (turno_actual != ultimo_turno) {
        esperando_giro = true;
        frames_espera = 0;
        ultimo_turno = turno_actual;
    }

    if (esperando_giro) {
        frames_espera++;
        if (frames_espera >= delay_frames) {
            esperando_giro = false;
        }
    }
    else { 
        angulo_camara_objetivo = (turno_actual == NEGRO) ? 180.0f : 0.0f;
        float velocidad = 0.05f;
        angulo_camara += (angulo_camara_objetivo - angulo_camara) * velocidad;
    }

    float rad = angulo_camara * M_PI / 180.0f; // Convertimos grados a radianes
    float camX = 10.0f * sin(rad);             // Se define la posicion de la camara
    float camZ = 10.0f * cos(rad);

    gluLookAt(camX, 10.0f, camZ, // Posición de la cámara (Y=10.0f)
        0.0f, 0.0f, 0.0f,        // Punto al que mira
        0.0f, 1.0f, 0.0f);       // Vector 'up'


    GLfloat luzPos[] = { camX, 10.0f, camZ, 0.0f }; // Posición de la luz
    glLightfv(GL_LIGHT0, GL_POSITION, luzPos);   
    
}