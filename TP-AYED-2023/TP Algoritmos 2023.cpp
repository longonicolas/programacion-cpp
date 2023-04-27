#include <iostream>
#include <cstring>
#include <cstdio>
#define max_nombre 10
#define max_comensales 40
#define max_mesas 100

using namespace std;

struct pedidos{
	
	int codigoPlato;
	int cantidad;
	int idComensal;
};

struct productos{
	
	int idProducto;
	int precio;
	char nombreProducto[30+1];
};

struct nodoProductos{
	
	productos info;
	nodoProductos* sgte;
};

//*********** structs para las listas y sublistas de cierres de mesa *************


struct tipoLista{
	
	int idComensal;
	char nombreProducto[30+1];
	int precio;
	int idProducto;
	int cantidad;
	int totalComensal;
};

struct nodo{
	
	tipoLista info;
	nodo* sgte;
};

struct vectorAuxiliar{
	
	char nombreProducto[30+1];
	int precio;
	int cantidad;
};

struct tipoEstadistica{
	
	int idProducto;
	int cantidad;	
};

struct nodoEstadistica{
	
	tipoEstadistica info;
	nodoEstadistica* sgte;
};

struct vectorEstadistica{
	
	nodoEstadistica* lista;
};


void cargaDePedidos(int, nodoProductos*);
void solicitudDeCierre(int, nodoProductos*, vectorEstadistica[]);
void mostrarMesa(nodo*);
void cierreDeCaja(vectorEstadistica[], nodoProductos*, int[], int);

nodoProductos* insertarOrdenadoProductos(nodoProductos*&, productos);
nodoProductos* buscarProducto(nodoProductos*, productos);

nodo* insertarOrdenado(nodo*&, tipoLista);
nodoEstadistica* insertarOrdenadoEstadisticas(nodoEstadistica*&, tipoEstadistica);
tipoEstadistica pop(nodoEstadistica*&);


void recorrerArchivo(int);
void ordenamientoBurbuja(vectorAuxiliar[], int);


int main(){
	
	int decision = -1;
	int mesa;
	
	nodoProductos* listaDeProductos = NULL; //Lista donde se van a cargar nombre, precio e ID de cada plato
	productos prod;
	
	FILE* x = fopen("precios.dat","rb");
	
	if(x == NULL){
	cout<<"Error al abrir el archivo"<<endl;
	return -1;
	} //verificamos que el archivo se abrio correctamente
	
	while(fread(&prod,sizeof(productos),1,x)){  //cargamos todos los productos y su información en una estructura auxiliar
												//de forma ordenada para su posterior lectura
		insertarOrdenadoProductos(listaDeProductos,prod);
	}
	fseek(x,0,SEEK_SET); //dejamos el puntero apuntando al inicio del inventario
	fclose(x);
	
	vectorEstadistica vector[max_mesas]; //vector donde se van a cargar las estadisticas por mesa
	for(int i = 0; i < max_mesas; i++){ //lo inicializamos vacio
		vector[i].lista = NULL;
	}
	
	int vecPosicion[max_mesas];
	int contador = 0;
	int j = 0;
	
	//menu que redirige a las distintas funciones
	while(decision != 0){
		
		cout<<"1- Cargar pedidos"<<endl;
		cout<<"2- Cerrar mesa"<<endl;
		cout<<"3- Ver contenido mesa"<<endl;	
		cout<<"4- Cierre de caja"<<endl;		
		cout<<"0- Finalizar"<<endl;
		cin>>decision;
		
		if(decision == 1){
		
		cout<<"Introducir numero de mesa"<<endl;
		cin>>mesa;
		cargaDePedidos(mesa,listaDeProductos);
		}
		
		if(decision == 2){
		
		cout<<"Introducir numero de mesa"<<endl;
		cin>>mesa;
		solicitudDeCierre(mesa,listaDeProductos,vector);
		cout<<endl;
		
		vecPosicion[j] = mesa;
		j++;
		contador++;
		}
		
		if(decision == 3){
		
		cout<<"Introducir numero de mesa"<<endl;
		cin>>mesa;
		recorrerArchivo(mesa);
		cout<<endl;
		}
		
		if(decision == 4){
		cierreDeCaja(vector,listaDeProductos,vecPosicion,contador);
		cout<<endl;
		}		
				
		
	}

	return 0;
}

void cargaDePedidos(int numMesa, nodoProductos* listaDeProductos){
	
	char nombreArchivo[max_nombre];
	
	sprintf(nombreArchivo, "mesa%d.dat", numMesa); //con esta funcion, el nombre del archivo se llamará "mesaxx.dat" siendo xx
													//el numero que se ingresa por teclado
	FILE* archivo = fopen(nombreArchivo, "ab+");
	
	if(archivo == NULL){
		cout<<"Error al abrir el archivo"<<endl;
		return;
	} //verificamos que el archivo se abrio correctamente
	
	
	//*******carga del pedido*********
	pedidos p;
	productos p2;
		
		cout<<"codigo del plato"<<endl;
		cin>>p.codigoPlato;
		
		p2.idProducto = p.codigoPlato;
		nodoProductos* aux = buscarProducto(listaDeProductos, p2);
		
		if(aux == NULL){ //verificamos a traves de listaDeProductos (que fue cargada en main) si el codigo del plato corresponde a uno existente
			while(aux == NULL){
			cout<<"codigo ingresado incorrecto"<<endl;
			cout<<"codigo del plato"<<endl;
			cin>>p.codigoPlato;
			
			p2.idProducto = p.codigoPlato;
			aux = buscarProducto(listaDeProductos, p2);
			}
		}
		
		cout<<"cantidad"<<endl;
		cin>>p.cantidad;
		
		if(p.cantidad < 1){
			while(p.cantidad < 1){
			cout<<"error en la cantidad de platos ingresada"<<endl;
			cout<<"Ingresar cantidad"<<endl;
			
			cin>>p.cantidad;
			}
		} 
		
		cout<<"id comensal"<<endl;
		cin>>p.idComensal;
		
		fwrite(&p,sizeof(pedidos),1,archivo);
		fclose(archivo);
		
		cout<<endl;
}

void solicitudDeCierre(int numMesa, nodoProductos* listaDeProductos, vectorEstadistica vector[]){
	
	char nombreArchivo[max_nombre];
	nodo* listaPrincipal = NULL;
	
	sprintf(nombreArchivo, "mesa%d.dat", numMesa);
	FILE* archivo = fopen(nombreArchivo, "rb");
	
	if(archivo == NULL){
		cout<<"Error al abrir el archivo"<<endl;
		return;
	} //verificamos que el archivo se abrio correctamente
	fseek(archivo,0,SEEK_SET); //leemos el archivo desde el inicio
	
	pedidos p;	
	tipoLista l;
	tipoEstadistica est;
	productos prod;

	while(fread(&p,sizeof(pedidos),1,archivo)){
		
		l.idComensal = p.idComensal;
		l.idProducto = p.codigoPlato;
		l.cantidad = p.cantidad;
		
		prod.idProducto = l.idProducto;
		
		nodoProductos* x = buscarProducto(listaDeProductos,prod); //buscamos la info restante del producto en la lista de productos
		strcpy(l.nombreProducto,x->info.nombreProducto);
		l.precio = x->info.precio;
		
		est.idProducto = p.codigoPlato;
		est.cantidad = p.cantidad;
		
		insertarOrdenado(listaPrincipal,l); //insertamos la info por orden de idComensal en listaPrincipal
		
		//****** para procesar las estadisticas ****
		insertarOrdenadoEstadisticas(vector[numMesa-1].lista,est); //insertamos ordenadamente por idProducto en la lista
																	 //de determinada posicion del vector para las estadisticas al final del dia
		}
	
	fseek(archivo,0,SEEK_SET); //dejamos el archivo en el inicio
	fclose(archivo);
	remove(nombreArchivo); //eliminamos el archivo

	mostrarMesa(listaPrincipal);
}

void mostrarMesa(nodo* listaPrincipal){
	
	nodo* aux = listaPrincipal;
	vectorAuxiliar vec[max_comensales];

	int control = aux->info.idComensal;
	
	int i;
	int contador = 0;
	int totalComensal = 0;
	int totalMesa = 0;
	
	while(aux != NULL){

		if(aux->info.idComensal != control){ //mostramos la info del comensal anterior (anterior en relacion al que apunta el nodo de la lista actualmente)
			cout<<"id Comensal: "<<control<<endl;
			
			for(i = 0; i < contador; i++){
				cout<<"Nombre del plato: "<<vec[i].nombreProducto<<endl;
				cout<<"cantidad: "<<vec[i].cantidad<<endl;
				cout<<"precio: "<<vec[i].cantidad * vec[i].precio<<endl;
				cout<<endl;
				
				totalComensal += (vec[i].cantidad) * (vec[i].precio);
				totalMesa += (vec[i].cantidad) * (vec[i].precio);
			}
			cout<<"Total comensal: "<<totalComensal<<endl;
			cout<<endl;
			
			totalComensal = 0;
			contador = 0;
			control = aux->info.idComensal;
		}
		
		vec[contador].cantidad = aux->info.cantidad;
		vec[contador].precio = aux->info.precio;
		strcpy(vec[contador].nombreProducto,aux->info.nombreProducto);
		contador++;
		
		aux = aux->sgte;
	}
	
	if(aux == NULL){
			cout<<"id Comensal: "<<control<<endl;
			
			for(i = 0; i < contador; i++){
				cout<<"Nombre del plato: "<<vec[i].nombreProducto<<endl;
				cout<<"cantidad: "<<vec[i].cantidad<<endl;
				cout<<"precio: "<<vec[i].cantidad * vec[i].precio<<endl;
				cout<<endl;
				
				totalComensal += (vec[i].cantidad) * (vec[i].precio);
				totalMesa += (vec[i].cantidad) * (vec[i].precio);
			}
			cout<<"Total comensal: "<<totalComensal<<endl;
			cout<<endl;
	}
	
	cout<<"Total mesa: "<<totalMesa;
	cout<<endl;
	
}

void cierreDeCaja(vectorEstadistica vector[], nodoProductos* listaDeProductos, 	int vecPosicion[], int contador){
	
	productos produ;
	int totalDia = 0;
	int i = 0;
	int mesa;
	
	vectorAuxiliar ranking[3];
	
	for(i=0; i < 3; i++){
		ranking[i].cantidad = 0;
	}
	
	for(int i=0; i<contador; i++){
		
		while(vector[vecPosicion[i]-1].lista != NULL){
			
			tipoEstadistica aux = pop(vector[vecPosicion[i]-1].lista);
			produ.idProducto = aux.idProducto;
			nodoProductos* x = buscarProducto(listaDeProductos, produ);
			
			for(int j=0; j<3; j++){ //analizamos los 3 productos mas vendidos
    			if(strcmp(ranking[j].nombreProducto,x->info.nombreProducto) == 0){
        			ranking[j].cantidad += aux.cantidad;
        			break; // el producto ya estaen el ranking, no hace falta seguir buscando
    			}
    			else if(ranking[j].cantidad < aux.cantidad){  //el producto no estaba en el ranking y es mas vendido que el actual en esta posicion
        												
        			bool yaAgregado = false;
        			for(int k = 0; k < j; k++){
            			if(strcmp(ranking[k].nombreProducto,x->info.nombreProducto) == 0){
                			yaAgregado = true;
                			break;
            			}
        			}
        		if(!yaAgregado){
            	// si el producto no fue agregado en otra posicion lo agregamos en esta
            		strcpy(ranking[j].nombreProducto,x->info.nombreProducto);
            		ranking[j].cantidad = aux.cantidad;
            		break;
        			}
    		}
		}
				ordenamientoBurbuja(ranking,3);
				totalDia += (aux.cantidad) * (x->info.precio);
			}
		
		if(mesa != vecPosicion[i])
		cout<<"Mesa: "<<vecPosicion[i]<<endl;
			
		cout<<"Producto mas vendido: "<<ranking[0].nombreProducto<<endl;
		cout<<"Segundo producto mas vendido: "<<ranking[1].nombreProducto<<endl;	
		cout<<"Tercer producto mas vendido: "<<ranking[2].nombreProducto<<endl;		
		cout<<endl;		
		mesa = vecPosicion[i];
		}
	
	cout<<"Total del dia: "<<totalDia;
	
	}
	

nodoProductos* insertarOrdenadoProductos(nodoProductos*& nod, productos prod){
	
	nodoProductos* nuevo = new nodoProductos();
 	nuevo->info = prod;
 	nuevo->sgte = NULL;
 	nodoProductos* ant = NULL;
 	nodoProductos* actual = nod;
 
 	while(actual != NULL && actual->info.idProducto < prod.idProducto){
 		
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

nodoProductos* buscarProducto(nodoProductos* nod, productos prod){
	
 nodoProductos* aux = nod;

while(aux != NULL && aux->info.idProducto != prod.idProducto){
	
 aux=aux->sgte;
 
 }
 return aux;
}

nodo* insertarOrdenado(nodo*& nod, tipoLista com){

	nodo* nuevo = new nodo();
 	nuevo->info = com;
 	nuevo->sgte = NULL;
 	nodo* ant = NULL;
 	nodo* actual = nod;
 
 	while(actual != NULL && actual->info.idComensal < com.idComensal){
 		
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

nodoEstadistica* insertarOrdenadoEstadisticas(nodoEstadistica*& nod, tipoEstadistica est){
	
	
	nodoEstadistica* nuevo = new nodoEstadistica();
 	nuevo->info = est;
 	nuevo->sgte = NULL;
 	nodoEstadistica* ant = NULL;
 	nodoEstadistica* actual = nod;
 
 	while(actual != NULL && actual->info.idProducto < est.idProducto){
 		
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

tipoEstadistica pop(nodoEstadistica*& nod){
	
	tipoEstadistica x; 
 
	nodoEstadistica* p = nod; 
 
	x = nod->info; 
 
	nod = p->sgte; 

 	delete p; 
 	return x; 	
}

void recorrerArchivo(int numMesa){
	
	char nombreArchivo[max_nombre];
	pedidos p;
	
	sprintf(nombreArchivo, "mesa%d.dat", numMesa);
	FILE* archivo = fopen(nombreArchivo, "rb");
	
	if(archivo == NULL){
		cout<<"Error al abrir el archivo"<<endl;
		return;
	} //verificamos que el archivo se abrio correctamente
	fseek(archivo,0,SEEK_SET); //leemos el archivo desde el inicio
	
	while(fread(&p,sizeof(pedidos),1,archivo)){
		
		cout<<"codigo del plato: "<<p.codigoPlato<<endl;;
		cout<<"cantidad: "<<p.cantidad<<endl;
		cout<<"id comensal: "<<p.idComensal<<endl;
		}

	fseek(archivo,0,SEEK_SET); //dejamos el archivo en el inicio
	fclose(archivo);	
}

void ordenamientoBurbuja(vectorAuxiliar ranking[], int n){
	
	for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2-i; j++){
        if(ranking[j].cantidad < ranking[j+1].cantidad){
            vectorAuxiliar temp = ranking[j];
            ranking[j] = ranking[j+1];
            ranking[j+1] = temp;
        	}
    	}
	}	
}
