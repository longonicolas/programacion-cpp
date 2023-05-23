struct vector{
	
	char nombreCandidato[20+1];
	char nombreLista[20+1];
};
struct vectorAuxiliar{
	
	char nombreCandidato[20+1];
	char nombreLista[20+1];
	int puntaje;	
};

void ordenarVector(vectorAuxiliar[], int);

vector generarListaConsejerosDocentes(vector docentes[], int votos1, int votos2, int votos3){
	
	vector ganadores[5];
	vectorAuxiliar aux[15];
	int i;

		for(i=0; i<5; i++){
			aux[i].puntaje = votos1 / i+1;
			strcpy(aux[i].nombreCandidato,docentes[i].nombreCandidato);
			strcpy(aux[i].nombreLista,docentes[i].nombreLista);
			}
		for(i=0; i<5; i++){
			aux[i+5].puntaje = votos2 / i+1;
			strcpy(aux[i+5].nombreCandidato,docentes[i+5].nombreCandidato);
			strcpy(aux[i+5].nombreLista,docentes[i+5].nombreLista);			
			}
		for(i=0;i<5;i++){
			aux[i+10].puntaje = votos2 / i+1;
			strcpy(aux[i+10].nombreCandidato,docentes[i+10].nombreCandidato);
			strcpy(aux[i+10].nombreLista,docentes[i+10].nombreLista);				
			}
		
		ordenarVector(aux,15); //ordena por puntaje de mayor a menor
		for(i=0;i<5;i++){
			strcpy(ganadores[i].nombreCandidato,aux[i].nombreCandidato);
			strcpy(ganadores[i].nombreLista,aux[i].nombreLista);
		}
		
		return ganadores;
}
