// ej: matrizCurso[0][1] = 5 -> El primer alumno de la estructura tiene un 5 en el segundo parcial
//ej: vec[2].legajo = 4555 -> Es el legajo del tercer alumno del vector (y supongo que del tercer alumno de la matriz), el tercer legajo mas chico.

struct vectorSituaciones{
	
	char nombreYApellido[40+1];
	char situacionAcademica[20+1];
};

void situacionAcademicaDelCurso(int matrizCurso[][7], tipoVector vec[]){
	
	vectorSituaciones vector[60];

	int i, j;
	
	for(i=0; i<60; i++){
		
		strcpy(vector[i].nombreYApellido, vec[i].nombreYApellido);
		
		
		if( (matrizCurso[i][0] >= 8 && matrizCurso[i][1] >= 8) || 
		    (matrizCurso[i][0] >= 8 && matrizCurso[i][1] < 8 && matrizCurso[i][3] >= 8) || 
		    (matrizCurso[i][0] < 8 && matrizCurso[i][1] >= 8 && matrizCurso[i][2] >= 8) ){
			strcpy(vector[i].situacionAcademica,"Promocionado");
			}
		
		else if( (matrizCurso[i][0] >= 6 || matrizCurso[i][2] >= 6 || matrizCurso[i][4] >= 6) && 
		         (matrizCurso[i][1] >= 6 || matrizCurso[i][3] >= 6 || matrizCurso[i][5] >= 6) && (matrizCurso[i][6] >= 6) ){
					strcpy(vector[i].situacionAcademica,"Regularizado");
				}
		else{
			strcpy(vector[i].situacionAcademica,"No aprobado");
			}
		//ahora tengo un vector de 60 posiciones con los nombres y situacion academica de todos los alumnos del curso, solo queda ordenarlo por nombre 
		
		vectorSituaciones aux;
		
		for(i=0; i<(60-1); i++){
			for(j=0; j<(60-1)-i; j++){
				
				if(strcmp(vector[j+1].nombreYApellido, vector[j].nombreYApellido) < 0 ){
					
					aux = vector[j+1];
					vector[j+1] = vector[j];
					vector[j] = aux;
					}
				}
			}
		
		
	}
}
