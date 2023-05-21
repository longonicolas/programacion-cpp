/* 
Requisitos jugador convocado: 1) Nativo del pais convocante 2) Menor de 30 3) No haber jugado en ninguna otra selección 

edadDelCandidato: recibe fecha de nacimiento, retorna edad -- ya esta hecha
jugoEnOtraSeleccion: retorna verdadero si jugo en otra seleccion -- solo hay que escribir su prototipo 

Hipotesis de trabajo: La info de los jugadores esta en dos archivos, "archivoJugadores" y "archivoSeleccionDondeJugo". La idea es cargar los datos relevantes de cada archivo
a una lista enlazada por jugador (y cada nodo tendra su id, fecha de nacimiento y pais)
*/

#include <iostream>
#include <cstring>
using namespace std;

struct archivoJugadores{
	
	int idJugador;
	char nombre[50+1];
	int fechaNacimiento;
	char nacionalidad[50+1];
	int cantGoles;
};
struct archivoSeleccionDondeJugo{
	
	int idJugador;
	char paisDondeJugo[50+1];
};
struct tipoJugador{
	
	int idJugador;
	int fechaNacimiento;
	char nacionalidad[50+1];
};
struct nodoJugador{
	
	tipoJugador info;
	nodoJugador* sgte;
};

struct nodoSeleccion{
	
	archivoSeleccionDondeJugo info;
	nodoSeleccion* sgte;
};

bool jugoEnOtraSeleccion(int, char[], nodoSeleccion*);

int main(){
	
	FILE* archivoJugador = fopen("archivoJugadores.dat","rb");
	FILE* archivoSelecciones = fopen("archivoSelecciones.dat","rb");
	
	
	return 0;
}

void cargarDatosEnMemoria(FILE* archivoJugador, FILE* archivoSelecciones, nodoSeleccion* listaSelecciones, nodoJugador* listaJugadores){
	
	archivoJugadores arch1;
	archivoSeleccionDondeJugo arch2;
	
	tipoJugador a;
	
	//lectura archivo1
	fseek(archivoJugador,0,SEEK_SET);
	
	while(fread(&arch1,sizeof(arch1),1,archivoJugador)){
		
		a.fechaNacimiento = arch1.fechaNacimiento;
		a.idJugador = arch1.idJugador;
		strcpy(a.nacionalidad,arch1.nacionalidad);
		
	//	insertarNodo(listaJugadores,a);
	}
	fclose(archivoJugador);
	
	//lectura archivo2
	fseek(archivoSelecciones,0,SEEK_SET);
	
	while(fread(&arch2,sizeof(arch2),1,archivoSelecciones)){
		
	//	insertarNodo(listaSelecciones,arch2);
	}
	fclose(archivoSelecciones);	
	
}

bool jugoEnOtraSeleccion(int idJugador, char pais[], nodoSeleccion* listaSelecciones){
	
	nodoSeleccion* aux = listaSelecciones;
	
	while(aux != NULL){
		if(idJugador == aux->info.idJugador){
			if(strcmp(aux->info.paisDondeJugo,pais) == 0)
				return true;
			else
				return false;	
			}
		aux = aux->sgte;			
		}

	return false;
}

bool puedeSerCitado(int idJugador, char pais[], nodoSeleccion* listaSelecciones, nodoJugador* listaJugadores){
	
	nodoJugador* aux = listaJugadores;
	
	while(aux != NULL){
		
		if(aux->info.idJugador == idJugador){
			if((edadDelJugador(aux->info.fechaNacimiento) < 30) && (jugoEnOtraSeleccion(idJugador,pais,listaSelecciones) == false))
				return true;
				
			else
				return false;
				
			}
			
	 aux = aux->sgte;
	}
	return false;
}



