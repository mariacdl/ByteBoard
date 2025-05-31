#include "Partida.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Partida::Partida(char modalidad, char color_jugador1):tablero(Tablero(0,0)) {
    Configuracion config;
    this->modalidad = modalidad;
    this->color_jugador1 = color_jugador1;
    tablero=config.genTablero(modalidad);
}

bool Partida::mover(int de_x, int de_y, int para_x, int para_y) {
    if(verificar_movimiento(de_x,de_y,para_x,para_y)){
        Tablero copia=tablero;

        //Captura al paso
        if(det_passant(de_x,de_y,para_x,para_y)){
            tablero.retirar_pieza(para_x,de_y);
        }

        tablero.mover_pieza(de_x, de_y, para_x, para_y);

        //Si la jugada deja al rey en jaque el movimiento no es válido
        if(det_jaque(tablero.getPieza(para_x,para_y).ver_color())){
            tablero=copia;
            return false;
        }
        
        //Detecta si hay algún peón que esté disponible para la captura al paso en la siguiente jugada
        if(tablero.getPieza(para_x,para_y).ver_tipo()=='P' && abs(para_y-de_y)==2){
            peon_passant={para_x,para_y};
        }
        else{
            peon_passant={-1,-1};
        }

        int extremo_opuesto;
        if(tablero.getPieza(para_x,para_y).ver_color()=='B'){
            extremo_opuesto=0;
        }
        else{
            extremo_opuesto=(modalidad=='P') ? 4 : 5;
        }

        //Promoción del peón
        if(tablero.getPieza(para_x,para_y).ver_tipo()=='P' && para_y==extremo_opuesto){
            promocion={para_x,para_y};
        }

        return true;
    }
    return false;
}

bool Partida::enrocar(char color){
    pair<int,int> pos_torre;
    pair<int,int> pos_rey;

    if(color=='0'){
        return false;
    }

    if(modalidad=='P'){
        pos_torre=(color=='B') ? make_pair(0, 4) : make_pair(3, 0);
        pos_rey=(color=='B') ? make_pair(3, 4) : make_pair(0, 0);
    }
    else{
        pos_torre=(color=='B') ? make_pair(0, 5) : make_pair(4, 0);
        pos_rey=(color=='B') ? make_pair(3, 5) : make_pair(1, 0);
    }

    Pieza torre=tablero.getPieza(pos_torre.first,pos_torre.second);
    Pieza rey=tablero.getPieza(pos_rey.first,pos_rey.second);

    //Determinar ni el rey ni la torre se hayan movido durante el juego
    if(!(torre.ver_tipo()=='T' && torre.ver_numero_movimiento()==0 && rey.ver_tipo()=='R' && rey.ver_numero_movimiento()==0)){
        return false;
    }

    //Determinar si el rey está en jaque
    if(det_jaque(color)){
        return false;
    }

    int dir=(pos_torre.first-pos_rey.first)/abs(pos_torre.first-pos_rey.first);
    
    //Determinar si hay obstáculos en el camino
    for(int i=1;i<abs(pos_torre.first-pos_rey.first);i++){
        if(tablero.getPieza(pos_rey.first+i*dir,pos_rey.second).ver_tipo()!='0'){
            return false;
        }
    }

    Tablero copia=tablero;

    tablero.mover_pieza(pos_rey.first,pos_rey.second,pos_rey.first+2*dir,pos_rey.second);
    tablero.mover_pieza(pos_torre.first,pos_torre.second,pos_rey.first+dir,pos_rey.second);

    //Determinar si el rey queda en jaque tras el enroque
    if(det_jaque(color)){
        tablero=copia;
        return false;
    }
    return true;
}

void Partida::alternar_turno() {
    turno_actual = (turno_actual == 'B') ? 'N' : 'B';
}

char Partida::ver_turno() const {
    return turno_actual;
}

bool Partida::verificar_movimiento(int de_x, int de_y, int para_x, int para_y) {
	Pieza partida = tablero.getPieza(de_x,de_y);
	Pieza destino = tablero.getPieza(para_x,para_y); // Hipotetico, puede estar libre

	// Verificar si movimiento est� dentro del tablero
	if (para_x < 0 || para_x >= tablero.ver_ancho() || para_y < 0 || para_y >= tablero.ver_largo()) {
		return false;
	}

    //Verificar si en la posición final se encuentra el rey
    if (destino.ver_tipo() == 'R' && destino.ver_color() == partida.ver_color()) {
        return false;
    }

	// Verificar si movimiento es para la misma casilla
	if (para_x == de_x && para_y == de_y) {
		return false;
	}

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento es valido para la pieza
	switch (partida.ver_tipo()) {
	case 'A': // Alfil
		if (abs(dx) != abs(dy))
			return false;
		{
			int paso_x = dx / abs(dx);
			int paso_y = dy / abs(dy);
			int x = de_x + paso_x;
			int y = de_y + paso_y;
			while (x != para_x) {
				if (tablero.getPieza(x,y).ver_tipo() != '0') return false; // Obst�culo
				x += paso_x;
				y += paso_y;
			}
		}
		break;

	case 'C': // Caballo
		if (!((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)))
			return false;
		break;

	case 'T': // Torre
		if (dx != 0 && dy != 0)
			return false;
		{
			int paso_x = (dx == 0) ? 0 : dx / abs(dx);
			int paso_y = (dy == 0) ? 0 : dy / abs(dy);
			int x = de_x + paso_x;
			int y = de_y + paso_y;
			while (x != para_x || y != para_y) {
				if (tablero.getPieza(x,y).ver_tipo() != '0') return false;
				x += paso_x;
				y += paso_y;
			}
		}
		break;

	case 'D': // Dama
		if (!(dx == 0 || dy == 0 || abs(dx) == abs(dy)))
			return false;
		{
			int paso_x = (dx == 0) ? 0 : dx / abs(dx);
			int paso_y = (dy == 0) ? 0 : dy / abs(dy);
			int x = de_x + paso_x;
			int y = de_y + paso_y;
			while (x != para_x || y != para_y) {
				if (tablero.getPieza(x,y).ver_tipo() != '0') return false;
				x += paso_x;
				y += paso_y;
			}
		}
		break;

	case 'R': // Rey
		if (abs(dx) > 1 || abs(dy) > 1)
			return false;
		break;

	case 'P': { // Pe�n
		int direccion = (partida.ver_color() == 'B') ? -1 : 1;
		int fila_inicial = (partida.ver_color() == 'B') ? tablero.ver_largo()-2 :  1;

		// Movimiento simple hacia adelante
		if (dx == 0 && dy == direccion && destino.ver_tipo() == '0') return true;

		// Movimiento doble desde la fila inicial
		if (dx == 0 && dy == 2 * direccion && de_y == fila_inicial && destino.ver_tipo() == '0' && modalidad == 'P') {
			// Verificar que la celda intermedia tambi�n est� vac�a
			int y_intermedia = de_y + direccion;
			if (tablero.getPieza(de_x,y_intermedia).ver_tipo() == '0')
				return true;
		}

        // Captura en diagonal
        if (abs(dx) == 1 && dy == direccion && destino.ver_tipo() != '0') {
            return true;
        }

        //Captura al paso
        if(det_passant(de_x,de_y,para_x,para_y)){
            return true;
        }
		return false;
		break;
		}
	default:
		return false;
	}
    return true;
}

vector<pair<int, int>> Partida::listar_movimientos_validos(int position_x, int position_y) {
	vector<pair<int, int>> movimientos_validos;
	for (int x = 0; x < tablero.ver_ancho(); ++x) {
		for (int y = 0; y < tablero.ver_largo(); ++y) {
			if (verificar_movimiento(position_x, position_y, x, y)) {
				movimientos_validos.emplace_back(x, y);
			}
		}
	}
	return movimientos_validos;
}

bool Partida::det_jaque(char color){
    char color_opuesto= (color=='B') ? 'N' : 'B';

    for (int x = 0; x < tablero.ver_ancho(); ++x) {
		for (int y = 0; y < tablero.ver_largo(); ++y) {
            if(tablero.getPieza(x,y).ver_color()==color_opuesto){
                vector<pair<int, int>> movimientos_validos=listar_movimientos_validos(x,y);

                for(int i=0;i<movimientos_validos.size();i++){
                    Pieza p_final=tablero.getPieza(movimientos_validos[i].first,movimientos_validos[i].second);

                    if(p_final.ver_color()==color && p_final.ver_tipo()=='R'){
                      return true;
                    }
                }   
            }
        }
    }
    return false;
}

bool Partida::det_jaque_mate(char color){
    //cout << "Evaluando jaque mate" << endl;
    Tablero copia=tablero;

    if(!det_jaque(color)){
        return false;
    }

    for (int x = 0; x < tablero.ver_ancho(); ++x) {
		for (int y = 0; y < tablero.ver_largo(); ++y) {
            if(tablero.getPieza(x,y).ver_color()==color){
                vector<pair<int, int>> movimientos_validos=listar_movimientos_validos(x,y);
                //cout << tablero.getPieza(x, y).ver_tipo() << endl;
                for(int i=0; i<movimientos_validos.size(); i++){
                    if(mover(x,y,movimientos_validos[i].first,movimientos_validos[i].second)){
                        //cout << movimientos_validos[i].first<<" "<< movimientos_validos[i].second << endl;
                        tablero=copia;
                        return false;
                    }
                }
            } 
        }
    }
    return true;
}

char Partida::det_fin(){
    //Detectar jaque mate
    if(det_jaque_mate(turno_actual)){
        return turno_actual;
    }
    //Detectar tablas
    else{
       // cout << "Evaluando tablas" << endl;
        Tablero copia=tablero;
        //Decterminar si existen movimientos válidos
        for (int x = 0; x < tablero.ver_ancho(); ++x) {
		    for (int y = 0; y < tablero.ver_largo(); ++y) {
                if(tablero.getPieza(x,y).ver_color()==turno_actual){
                    vector<pair<int, int>> movimientos_validos=listar_movimientos_validos(x,y);
                    //cout << tablero.getPieza(x, y).ver_tipo()<<endl;
                    for(int i=0; i<movimientos_validos.size(); i++){
                        if(mover(x,y,movimientos_validos[i].first,movimientos_validos[i].second)){
                            tablero=copia;
                            return '0';
                        }
                    }
                } 
            }
        }
        if(enrocar(turno_actual)){
            tablero=copia;
            return '0';
        }
        return 'T';
    }
}

bool Partida::det_passant(int de_x, int de_y, int para_x, int para_y){
    Pieza pieza=tablero.getPieza(de_x,de_y);
    int dx = para_x - de_x;
	int dy = para_y - de_y;
    int direccion = (pieza.ver_color() == 'B') ? -1 : 1;

    if(abs(dx)==1 && dy==direccion && pieza.ver_tipo()=='P' && para_x==peon_passant.first && de_y==peon_passant.second){
        return true;
    }
    return false;
}

bool Partida::jugar(int de_x, int de_y, int para_x, int para_y){
    if(tablero.getPieza(de_x,de_y).ver_color()==turno_actual){
        if(mover(de_x,de_y,para_x,para_y)){
            alternar_turno();
            return true;
        }
        else{
            cout << "Movimiento invalido para: " << tablero.getPieza(de_x, de_y).ver_tipo() << endl;
            return false;
        }
    }
    cout << "Esta intentando mover una pieza que no es suya" << endl;
    return false;
}

//Sobrecarga para enroque
bool Partida::jugar(char color){
    if(color==turno_actual){
        if(enrocar(color)){
            peon_passant={-1,-1};
            alternar_turno();
            return true;
        }
        else{
            cout << "Intento de enroque invalido" << endl;
            return false;
        }
    }
    cout << "No puede realizar un enroque correspondiente al equipo contrario" << endl;
    return false;
}

pair<int,int> Partida::getPromocion(){
    return promocion;
}
bool Partida::promocionar(char tipo){
    if(promocion.first!=-1){
        if (tablero.getPieza(promocion.first, promocion.second).ver_color() == 'B') {
            for (int i = 0; i < promocionesB.size(); i++) {
                if (promocionesB[i] == tipo) {
                    cout << "No se puede promocionar el peon a una pieza a la que ya se ha promocionado otro anteriormente" << endl;
                    return false;
                }
            }
            promocionesB.push_back(tipo);
        }
        else {
            for (int i = 0; i < promocionesN.size(); i++) {
                if (promocionesN[i] == tipo) {
                    cout << "No se puede promocionar el peon a una pieza a la que ya se ha promocionado otro anteriormente" << endl;
                    return false;
                }
            }
            promocionesN.push_back(tipo);
        }
        tablero.colocar_pieza(promocion.first,promocion.second,tipo,tablero.getPieza(promocion.first,promocion.second).ver_color(),tablero.getPieza(promocion.first,promocion.second).ver_numero_movimiento());
        promocion={-1,-1};
        return true;
    }
    return false;
}

Tablero Partida::ver_tablero() {
    return tablero;
}

char Partida::ver_modalidad() {
    return modalidad;
}