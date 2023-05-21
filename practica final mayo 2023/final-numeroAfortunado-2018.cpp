#include <iostream>
using namespace std;

struct nodo{
	
	char info;
	nodo* sgte;
};

void push(nodo*&, char);
char pop(nodo*&);
nodo* cargarNombre(char[], int);
nodo* cargarNombre2();
int numeroAfortunado(nodo*);

int main(){
	
	nodo* pila = NULL;
	
	pila = cargarNombre2();
	
	int x = numeroAfortunado(pila);
	cout<<x;
	
	return 0;
}

/*nodo* cargarNombre(char nombre[], int largoNombre){
	
	nodo* pila = NULL;
	int i;
	
	for(i = 0; i<largoNombre; i++){
		push(pila,nombre[i]);
		}
	return pila;
}*/

//otra forma

nodo* cargarNombre2(){
	
	int largoNombre;
	char nombre[100+1];
	nodo* pila = NULL;
	
	cout<<"Ingresar cantidad de letras de su nombre"<<endl;
	cin>>largoNombre;
	cin.ignore();
		
	cout<<"Ingresar nombre"<<endl;
	cin.getline(nombre,100+1);
	cin.ignore();
	
	for(int i=0; i<largoNombre; i++){
		cout<<nombre[i]<<endl;
		push(pila,nombre[i]);
	}
	
	return pila;
}

int numeroAfortunado(nodo* pila){
	
	int acumulador = 0;
	char a;
	int digito1 = 0, digito2 = 0, digito3 = 0;
	int numeroAfortunado = 0;
	
	while(pila != NULL){
		
		a = pop(pila);
		acumulador += (a - 'A' + 1);
	}
	
	digito1 = acumulador / 100;
	digito2 = (acumulador / 10) % 10;
	digito3 = acumulador % 10;
	
	numeroAfortunado = digito1+digito2+digito3;
	
	if(numeroAfortunado >= 10){
		
		digito1 = numeroAfortunado / 100;
		digito2 = (numeroAfortunado / 10) % 10;
		digito3 = numeroAfortunado % 10;
		
		numeroAfortunado = digito1+digito2+digito3;
		
		return numeroAfortunado;
	}
	
	return numeroAfortunado;
	
}

void push(nodo*& pila, char v){
	
	nodo* p = new nodo();
	p ->info = v;
	p->sgte = pila;
	pila = p;
	
	return;
}

char pop(nodo*& pila){
	
	char x;
	nodo* p = pila;
	x = p ->info;
	pila = p->sgte;
	
	delete p;
	return x;
}


