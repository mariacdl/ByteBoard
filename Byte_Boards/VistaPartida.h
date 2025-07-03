#pragma once
#include <Estados.h>

class VistaPartida {

	float angulo_camara = 0.0f;         // ángulo actual
	float angulo_camara_objetivo = 0.0f; // hacia dónde rotar
	bool esperando_giro = false;        // indica si está esperando para girar
	int frames_espera = 0;              // contador de frames
	const int delay_frames = 20;        // 0.5 segundo ya que es 25msx20=0.5s

	EstadoTurno ultimo_turno = BLANCO;

public:
	void actualizar_camara(EstadoTurno turno_actual);
};

