#include "Configuracion.h"

Tablero Configuracion::genTablero(char modalidad){
    if(modalidad='P'){
        Tablero tab(4,5);

        tab.colocar_pieza(0,0,'R','N');
		tab.colocar_pieza(1,0,'C','N');
		tab.colocar_pieza(2,0,'A','N');
		tab.colocar_pieza(3,0,'T','N');
		tab.colocar_pieza(0,1,'P','N');

		tab.colocar_pieza(3,4,'R','B');
		tab.colocar_pieza(2,4,'C','B');
		tab.colocar_pieza(1,4,'A','B');
		tab.colocar_pieza(0,4,'T','B');
		tab.colocar_pieza(3,3,'P','B');

        return tab;
    }
    else{
        Tablero tab(5,6);

        tab.colocar_pieza(0,0,'D','N');
		tab.colocar_pieza(1,0,'R','N');
		tab.colocar_pieza(2,0,'A','N');
		tab.colocar_pieza(3,0,'C','N');
		tab.colocar_pieza(4,0,'T','N');
		tab.colocar_pieza(0,1,'P','N');
		tab.colocar_pieza(1,1,'P','N');
		tab.colocar_pieza(2,1,'P','N');
		tab.colocar_pieza(3,1,'P','N');
		tab.colocar_pieza(4,1,'P','N');

		tab.colocar_pieza(0,5,'T','N');
		tab.colocar_pieza(1,5,'C','N');
		tab.colocar_pieza(2,5,'A','N');
		tab.colocar_pieza(3,5,'R','N');
		tab.colocar_pieza(4,5,'D','N');
		tab.colocar_pieza(0,4,'P','N');
		tab.colocar_pieza(1,4,'P','N');
		tab.colocar_pieza(2,4,'P','N');
		tab.colocar_pieza(3,4,'P','N');
		tab.colocar_pieza(4,4,'P','N');

        return tab;
    } 
}