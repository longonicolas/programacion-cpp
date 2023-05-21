#include <iostream>
using namespace std;

struct Nodo{
	int info;
	Nodo* sgte;
};
struct nodoVector{
	int info[1024];
	nodoVector* sgte;
};

int main(){
	
	FILE* f;
	int vectorDeNumeros[128];
	Nodo* lista = NULL;
	

	f = fopen("archivonumeros.dat","rb");
	fseek(f,0,SEEK_SET);
	sumarNumerosDesdeArchivoA(f);
	
	sumarNumerosDesdeArchivoB(vectorDeNumeros);
	sumarNumerosDesdeArchivoC(lista);
	
	
	return 0;
}

int sumarNumerosDesdeArchivoA(FILE* f){
	
	int a, acumulador;
	acumulador = 0;
		while(fread(&a,sizeof(int),1,f)){
		acumulador += a;	
		}
		
	fclose(f);
	return acumulador;
}

int sumarNumerosDesdeArchivoB(int vec[]){
	
	int acumulador = 0;
	
	for(int i=0; i<128; i++){
		acumulador += vec[i];
	}
	return acumulador;
}

int sumarNumerosDesdeArchivoC(Nodo* lista){
	
	int acumulador = 0;
	Nodo* aux = lista;
	
	while(aux != NULL){
		acumulador+= aux->info;
		aux = aux->sgte;
	}
	return acumulador;
}

int sumarNumerosDesdeArchivoFinal(nodoVector* listaDeVectores){
	
	int acumulador = 0;
	nodoVector* aux = listaDeVectores;
	
	while (aux != NULL){
		
		for(int i=0; i<128; i++){
			acumulador += aux->info.vector[i];
		}
		aux = aux->sgte;
	}
	
}

