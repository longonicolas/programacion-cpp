struct tipoNodo{
	
	int dniCliente;
	char nombre[30+1];	
};
struct nodo{
	
	tipoNodo info;
	nodo* sgte;	
};
struct tipoMatriz{
	
	int cantidadVendida;
	nodo* listaDeClientes;
};

nodo* insertarOrdenado(nodo*&, tipoNodo);

int obtenerPosFilaEnMatriz(int diaDelMes){
	return diaDelMes-1;
}

int obtenerPosColumnaEnMatriz(vector electrodomesticos[], char codigoElectrodomestico[6+1]){
	
	int posicionColumna;
	for(int i = 0; i<2500; i++){
		if(strcmp(codigoElectrodomestico,vec[i].codigoElectrodomestico) == 0){
			posicionColumna = i;
			return posicionColumna;
			}
		}
}

void cargarMatriz(FILE* ventas, vector electrodomesticos[], tipoMatriz matriz[][2500]){
	
	tipoArchivo arch;
	tipoNodo a;
	
	while(fread(&arch,sizeof(arch),1,ventas)){
		
		int fila = obtenerPosFilaEnMatriz(arch.diaDelMes);
		int columna = obtenerPosColumnaEnMatriz(vector,arch.codigoElectrodomestico);
		
		a.dniCliente = arch.dniCliente;
		strcpy(a.nombre,arch.nombreCliente);
		
		matriz[fila][columna].cantidadVendida += arch.cantidadVendida;
		insertarOrdenado(matriz[fila][columna].nodo,a);
		}
}

void mostrarClientes(int fila, int columna, tipoMatriz matriz[][2500]){
	

	cout<<"Cantidad de ventas dia "<<fila+1<<": "<<matriz[fila][columna].cantidadVendida;
	
	nodo* aux = matriz[fila][columna].nodo;
	cout<<"Clientes del dia: "
	
	while(aux != NULL){
		cout<<"DNI: "<<aux->info.dniCliente;
		aux = aux->sgte;
	}
				
}




