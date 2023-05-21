
struct vehiculoSospechoso{
	
	char patente[10+1];
	char delito[50+1];
	char horaDelito[10+1];
};
struct tipoNodoVehiculos{
	
	char patente[10+1];
	char horaDeRegistro[10+1];
};
struct nodoVehiculos{
	
	tipoNodoVehiculos info;
	nodoVehiculos* sgte;
};
struct vectorDeRecorridos{
	
	char nombreZona[30+1];
	nodoVehiculos* nodo;
};
struct tipoNodoRecorrido{
	
	char nombreZona[30+1];
	char horaDeRegistro[10+1];
};
struct nodoRecorrido{
	
	tipoNodoRecorrido info;
	nodoRecorrido* sgte;
};
struct recorridoVehiculoSospechoso{
	
	char patente[10+1];
	char delito[50+1];
	nodoRecorrido* nodo;
};


recorridoVehiculoSospechoso recorrido(vehiculoSospechoso vehiculo, vectorDeRecorridos vec[]){
	
	recorridoVehiculoSospechoso sospechoso;
	sospechoso.nodo = NULL;
	tipoNodoRecorrido a;
	
	nodoVehiculos* aux1 = NULL;
	
	for(int i=0; i<10; i++){
		aux1 = vec[i].nodo;
		while(aux1 != NULL){
			
			if(strcmp(vehiculo.patente,aux1->info.patente) == 0){
					strcpy(a.nombreZona,vec[i].nombreZona);
					strcpy(a.horaDeRegistro,aux1->info.horaDeRegistro);
					insertarOrdenado(sospechoso.nodo,a); //inserta por hora de registro
				}
			aux1 = aux1->sgte;
			}
		}
	
	strcpy(sospechoso.patente,vehiculo.patente);
	strcpy(sospechoso.delito,vehiculo.delito);
	return sospechoso;
}
