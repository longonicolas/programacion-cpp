struct tipoArchivo{
	
	int nroVuelo;
	char ciudad[10+1];
	char empresa[10+1];
	int duracionViaje;
	char horaArriboOPartida[20+1];
	char arriboOPartida;
};
struct nodo{
	
	tipoArchivo info;
	nodo* sgte;
};

nodo* insertarOrdenado(nodo*&, tipoArch);
tipoArch pop(nodo*&);

nodo* llenarLista(FILE* archivoVuelos){
	
	nodo* lista = NULL;
	tipoArchivo arch;
	
	archivoVuelos = fopen("horarios.dat",rb);
	fseek(archivoVuelos,0,SEEK_SET);
	
	while(fread(&arch,sizeof(arch),1,archivoVuelos)){
		
		insertarOrdenado(lista,arch);
	}
	fclose(archivoVuelos);
	return lista;
}

void actualizarTablero(nodo* lista){
	
	nodo* aux1 = lista;
	char horaActual[20+1];
	
	strcpy(horaActual,getDate());
	
	for(int i=0; i<10; i++){
		if(strcmp(horaActual,aux1->info.horaArriboOPartida) >= 0){
			pop(aux1);
			}	
		}
}

void mostrarVuelos(nodo* lista){
	
	nodo* aux = lista;
	
	while(aux != NULL){
		
		actualizarTablero(aux);
		for(int i=0; i<10; i++){
			if(aux != NULL){
			
			cout<<aux->info.nroVuelo;
			cout<<aux->info.horaArriboOPartida;
			cout<<aux->info.ciudad;
			cout<<aux->info.arriboOPartida;
			cout<<aux->info.empresa;
			cout<<aux->info.duracionViaje;
			
			aux = aux->sgte;
				}
			else
				return;
			}
			
		}
}


