// Estructura: Lista de obras sociales que tiene un vector de dos posiciones (casos positivos y negativos), este vector tiene otro vector de dos posiciones (tipo de test A y B)
// que posee dentro un nodo a una lista enlazada con los datos de todas las personas que se encuentren en cada una de las 4 situaciones

#include <iostream>
#include <cstring>
using namespace std;

struct archivoHisopados{
	
	int DNI;
	char apeYNom[30+1];
	int fechaNacimiento;
	char domicilio[30+1];
	int centroDeTesteo;
	int tipoDeTest; // 0 Antigeno, 1 PCR
	char obraSocial[10+1];
	int cantDosisVacuna;
	int fechaDeContactoEstrecho;
	int resultadoTest; //0 (negativo) o 1 (positivo)
};

//lista mas interna, de pacientes
struct tipoPaciente{
	
	int DNI;
	char apeYNom[30+1];
	int fechaNacimiento;
	char domicilio[30+1];
};

struct nodoPacientes{
	
	tipoPaciente info;
	nodoPacientes* sgte;
};

//lista secundaria, de casos positivos y negativos

struct vec{
	int contador;
	nodoPacientes* nodo;
};


struct vecResultado{
	int contador;
	vec vectorTest[2];  //0 Antigeno, 1 PCR
};

//lista principal, de obras sociales
struct tipoListaPrincipal{
	
	char obraSocial[10+1];
	int contador;
	vecResultado vector[2]; //0 (negativo) o 1 (positivo)
};
struct nodoListaPrincipal{
	
	tipoListaPrincipal info;
	nodoListaPrincipal* sgte;
};

nodoListaPrincipal* buscar(nodoListaPrincipal*, tipoListaPrincipal);
nodoListaPrincipal* insertarOrdenado(nodoListaPrincipal*&, tipoListaPrincipal);
nodoPacientes* insertarOrdenadoB(nodoPacientes*&, tipoPaciente);

nodoListaPrincipal* cargarEstructura(FILE* archTesteos){
	
	nodoListaPrincipal* listaPrincipal = NULL;
	tipoListaPrincipal li;
	
	archivoHisopados a;
	tipoPaciente paciente;
	
	while(fread(&a,sizeof(a),1,archTesteos)){
		
		strcpy(li.obraSocial,a.obraSocial);
		
		nodoListaPrincipal* aux1 = buscar(listaPrincipal, li); //busca por obra social
		if(aux1 == NULL){
			insertarOrdenado(listaPrincipal,li);
		}
		
		paciente.DNI = a.DNI;
		paciente.fechaNacimiento = a.fechaNacimiento;
		strcpy(paciente.apeYNom,a.apeYNom);
		strcpy(paciente.domicilio,a.domicilio);
		
		nodoListaPrincipal* aux2 = buscar(listaPrincipal, li); //busca por obra social
		aux2->info.contador++;
		aux2->info.vector[a.resultadoTest].contador++;
		aux2->info.vector[a.resultadoTest].vectorTest[a.tipoDeTest].contador++;
		
		nodoPacientes* aux3 = aux2->info.vector[a.resultadoTest].vectorTest[a.tipoDeTest].nodo;
		insertarOrdenadoB(aux3,paciente); //inserta por DNI
		
	}
	
	return listaPrincipal;
}

void imprimirListado (nodoListaPrincipal* lista){
	
	nodoListaPrincipal* aux1 = lista;
	int i,j;
	
	
	while(aux1 != NULL){
		
		cout<<"Obra social: "<<aux1->info.obraSocial<<endl;
		cout<<"Total hisopados: "<<aux1->info.contador<<endl;
		cout<<"Casos positivos"<<endl<<endl;
		

			
		cout<<"Total negativos: "<<aux1->info.vector[0].contador<<endl;
	
			cout<<"Total antigeno: "<<aux1->info.vector[0].vectorTest[0].contador<<endl;
			cout<<"Datos pacientes: "<<endl<<endl;
				nodoPacientes* aux2 = aux1->info.vector[0].vectorTest[0].nodo;
					while(aux2 != NULL){
						cout<<"NOMBRE: "<<aux2->info.apeYNom<<endl;
						cout<<"DNI: "<<aux2->info.DNI<<endl;
						cout<<"DOMICILIO: "<<aux2->info.domicilio<<endl;
						cout<<"FECHA NACIMIENTO: "<<aux2->info.fechaNacimiento<<endl<<endl;
						
						aux2 = aux2->sgte;
						}
						
			cout<<"Total PCR: "<<aux1->info.vector[0].vectorTest[1].contador<<endl;
			cout<<"Datos pacientes: "<<endl<<endl;
				nodoPacientes* aux3 = aux1->info.vector[0].vectorTest[1].nodo;
					while(aux3 != NULL){
						cout<<"NOMBRE: "<<aux3->info.apeYNom<<endl;
						cout<<"DNI: "<<aux3->info.DNI<<endl;
						cout<<"DOMICILIO: "<<aux3->info.domicilio<<endl;
						cout<<"FECHA NACIMIENTO: "<<aux3->info.fechaNacimiento<<endl<<endl;
						
						aux3 = aux3->sgte;
						}	
			
		cout<<"Total positivos: "<<aux1->info.vector[1].contador<<endl;
		
			cout<<"Total antigeno: "<<aux1->info.vector[1].vectorTest[0].contador<<endl;
			cout<<"Datos pacientes: "<<endl<<endl;
				nodoPacientes* aux4 = aux1->info.vector[1].vectorTest[0].nodo;
					while(aux4 != NULL){
						cout<<"NOMBRE: "<<aux4->info.apeYNom<<endl;
						cout<<"DNI: "<<aux4->info.DNI<<endl;
						cout<<"DOMICILIO: "<<aux4->info.domicilio<<endl;
						cout<<"FECHA NACIMIENTO: "<<aux4->info.fechaNacimiento<<endl<<endl;
						
						aux4 = aux4->sgte;
						}
						
			cout<<"Total PCR: "<<aux1->info.vector[1].vectorTest[1].contador<<endl;
			cout<<"Datos pacientes: "<<endl<<endl;
				nodoPacientes* aux5 = aux1->info.vector[1].vectorTest[1].nodo;
					while(aux5 != NULL){
						cout<<"NOMBRE: "<<aux5->info.apeYNom<<endl;
						cout<<"DNI: "<<aux5->info.DNI<<endl;
						cout<<"DOMICILIO: "<<aux5->info.domicilio<<endl;
						cout<<"FECHA NACIMIENTO: "<<aux5->info.fechaNacimiento<<endl<<endl;
						
						aux5 = aux5->sgte;
						}			

					
		aux1 = aux1->sgte;
	}
}


nodoListaPrincipal* buscar(nodoListaPrincipal* nod, tipoListaPrincipal v){
	
	nodoListaPrincipal* aux = nod;
	
	while(aux != NULL && aux->info.obraSocial != v.obraSocial){
		aux=aux->sgte;
		}
	return aux;
}

nodoListaPrincipal* insertarOrdenado(nodoListaPrincipal*& nod, tipoListaPrincipal v){
	
	nodoListaPrincipal* nuevo = new nodoListaPrincipal();
	nuevo->info = v;
	nuevo->sgte = NULL;
	nodoListaPrincipal* ant = NULL;
	nodoListaPrincipal* actual = nod;

	while(actual != NULL && strcmp(actual->info.obraSocial,v.obraSocial) != 0){
		
		ant = actual;
		actual = actual->sgte;
	}
	
	if(ant == NULL)
	nod = nuevo;
	
	else
	ant->sgte = nuevo;
	
	nuevo->sgte = actual;
	
	return nuevo;
}

nodoPacientes* insertarOrdenadoB(nodoPacientes*& nod, tipoPaciente v){
	
	nodoPacientes* nuevo = new nodoPacientes();
	nuevo->info = v;
	nuevo->sgte = NULL;
	nodoPacientes* ant = NULL;
	nodoPacientes* actual = nod;

	while(actual != NULL && actual->info.DNI < v.DNI){
		
		ant = actual;
		actual = actual->sgte;
	}
	
	if(ant == NULL)
	nod = nuevo;
	
	else
	ant->sgte = nuevo;
	
	nuevo->sgte = actual;
	
	return nuevo;	
}

