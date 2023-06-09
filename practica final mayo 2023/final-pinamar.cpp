struct tipoArchivo{
	
	char localidad[20+1];
	int nroLista;
	int votos;
};
struct vector{
	char nombreLocalidad[20+1];
};

int main(){
	
	vector vec[4];
	
	vec[0].nombreLocalidad = "Pinamar";
	vec[1].nombreLocalidad = "Carilo";
	vec[2].nombreLocalidad = "Ostende";
	vec[3].nombreLocalidad = "Valeria del mar";
	
	FILE* archivo = fopen("votos.dat",rb+);
	fseek(archivo,0,SEEK_SET);
		
	return 0;
}

int llenarMatriz(FILE* archivo, vector vec[]){
	
	tipoArchivo arch;
	int matriz[4][5];
	
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			matriz[i][j] = 0;
		}
	}
	
	while(fread(&arch,sizeof(arch),1,archivo)){
		
		for(int i=0; i<4; i++){
			if(strcmp(vec[i].nombreLocalidad,arch.localidad) == 0){
				matriz[i][arch.nroLista-1] += arch.votos;
				}
			}
		}
	return matriz;	
}

void imprimirResultados(int matriz[][5], vector vec[]){
	
	int totalVotos = 0;
	float porcentaje;
	int votos[5];
	
	int listaConMasVotos = 0; int nroListaConMasVotos = 0;
	int segundaListaConMasVotos = 0; int nroSegundaListaConMasVotos = 0;
	for(int i=0; i<5; i++){
		votos[i] = 0;
		}
	
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			cout<<"Total votos lista "<<j+1<<"en la localidad "<<vec[i].nombreLocalidad<<": "<<matriz[i][j];
			totalVotos += matriz[i][j];
			votos[j] += matriz[i][j];
			}
		}
	
	for(int i=0; i<5; i++){
		cout<<"Total votos lista "<<i+1<<": "<<votos[i];
		
		porcentaje = (votos[i] / totalVotos) * 100;
		cout<<"Porcentaje de la lista respecto al total de votos: "<<porcentaje<<"%";
		
		if(votos[i] > listaConMasVotos){
			segundaListaConMasVotos = listaConMasVotos; nroSegundaListaConMasVotos = nroListaConMasVotos;			
			listaConMasVotos = votos[i]; nroListaConMasVotos = i+1;
			}
			
		else if(votos[i] > segundaListaConMasVotos && votos[i] <= listaConMasVotos)
			segundaListaConMasVotos = votos[i];
			nroSegundaListaConMasVotos = i+1;
		}
	cout<<"Total votos validos: "<<totalVotos;
	
	float porcentajeL1 = (listaConMasVotos/totalVotos) * 100;
	float porcentajeL2 = (segundaListaConMasVotos/totalVotos) * 100;
	if(porcentajeL1 > 50 || porcentajeL1 - porcentajeL2 >= 10){
		cout<<"lista ganadora: "<<nroListaConMasVotos;
		}
	else{
		cout << "Listas que pasan a balotaje: " << nroListaConMasVotos << " " << nroSegundaListaConMasVotos;
		}

}
