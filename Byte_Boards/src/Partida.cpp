#include "Partida.h"
#include "Tablero.h"
#include "Pieza.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

bool Partida::mover(int de_x, int de_y, int para_x, int para_y) {
    if(verificar_movimiento(de_x,de_y,para_x,para_y)){
        Tablero copia = tablero;

        tablero.mover_pieza(de_x, de_y, para_x, para_y);

        //Si la jugada deja al rey en jaque el movimiento no es válido
        if(det_jaque(tablero.ver_pieza(para_x,para_y)->ver_color())){
            tablero = copia;
            return false;
        }
        
        //Detecta si hay algún peón que esté disponible para la captura al paso en la siguiente jugada
        if(tablero.ver_pieza(para_x,para_y)->ver_tipo()=='P' && abs(para_y-de_y)==2){
            peon_passant={para_x,para_y};
        }
        else{
            peon_passant={-1,-1};
        }

        int extremo_opuesto;
        if(tablero.ver_pieza(para_x,para_y)->ver_color()=='B'){
            extremo_opuesto=0;
        }
        else{
            extremo_opuesto=(modalidad=='P') ? 4 : 5;
        }

        //Promoción del peón
        if(tablero.ver_pieza(para_x,para_y)->ver_tipo()=='P' && para_y==extremo_opuesto){
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

    Pieza* torre=tablero.ver_pieza(pos_torre.first,pos_torre.second);
    Pieza* rey=tablero.ver_pieza(pos_rey.first,pos_rey.second);

    //Determinar ni el rey ni la torre se hayan movido durante el juego
    if(!(torre->ver_tipo()=='T' && torre->ver_numero_movimientos() == 0 && rey->ver_tipo()=='R' && rey->ver_numero_movimientos() == 0)){
        return false;
    }

    //Determinar si el rey está en jaque
    if(det_jaque(color)){
        return false;
    }

    int dir=(pos_torre.first-pos_rey.first)/abs(pos_torre.first-pos_rey.first);
    
    //Determinar si hay obstáculos en el camino
    for(int i=1;i<abs(pos_torre.first-pos_rey.first);i++){
        if(tablero.ver_pieza(pos_rey.first+i*dir,pos_rey.second)->ver_tipo() != '0'){
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
	Pieza* pieza = tablero.ver_pieza(de_x,de_y);
    return pieza->validar_movimiento(de_x, de_y, para_x, para_y, tablero);
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
            if(tablero.ver_pieza(x,y)->ver_color()==color_opuesto){
                vector<pair<int, int>> movimientos_validos=listar_movimientos_validos(x,y);

                for(int i=0;i<movimientos_validos.size();i++){
                    Pieza* p_final=tablero.ver_pieza(movimientos_validos[i].first,movimientos_validos[i].second);

                    if(p_final->ver_color()==color && p_final->ver_tipo()=='R'){
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
            if(tablero.ver_pieza(x,y)->ver_color()==color){
                vector<pair<int, int>> movimientos_validos=listar_movimientos_validos(x,y);
                //cout << tablero.ver_pieza(x, y).ver_tipo() << endl;
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
    else {
       // cout << "Evaluando tablas" << endl;
        Tablero copia = tablero;
        //Decterminar si existen movimientos válidos
        for (int x = 0; x < tablero.ver_ancho(); ++x) {
		    for (int y = 0; y < tablero.ver_largo(); ++y) {
                if(tablero.ver_pieza(x,y)->ver_color() == turno_actual){
                    vector<pair<int, int>> movimientos_validos = listar_movimientos_validos(x,y);
                    //cout << tablero.ver_pieza(x, y).ver_tipo()<<endl;
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


bool Partida::jugar(int de_x, int de_y, int para_x, int para_y){
    if(tablero.ver_pieza(de_x,de_y)->ver_color()==turno_actual){
        if(mover(de_x,de_y,para_x,para_y)){
            alternar_turno();
            return true;
        }
        else{
            cout << "Movimiento invalido para: " << tablero.ver_pieza(de_x, de_y)->ver_tipo() << endl;
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
    Pieza* pieza = tablero.ver_pieza(promocion.first, promocion.second);
    if(promocion.first!=-1){
        if (pieza->ver_color() == 'B') {
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
        int pos_x = promocion.first;
        int pos_y = promocion.second;
        tablero.colocar_pieza(pos_x, pos_y, tipo, pieza->ver_color(), pieza->ver_numero_movimientos());
        promocion={-1,-1};
        return true;
    }
    return false;
}

const Tablero& Partida::ver_tablero() const {
    return tablero;
}

char Partida::ver_modalidad() const {
    return modalidad;
}