struct pilaAstronomica{
	
	int info;
	pilaAstronomica* sgte;
};

void push(pilaAstronomica*&, int);
int pop(pilaAstronomica*&);

int main(){
	
	pilaAstronomica* a = NULL;
	pilaAstronomica* b = NULL;
	
	FILE* N1 = fopen("n1.dat","rb+");
	FILE* N2 = fopen("n2.dat","rb+");
	
	a = leerNumero(N1);
	b = leerNumero(N2);
	
	fclose(N1); fclose(N2);
	
	pilaAstronomica* c = sumarNumeros(a,b);
	mostrarNumero(c);
}

pilaAstronomica* sumarNumeros(pilaAstronomica* a, pilaAstronomica* b){
	
	pilaAstronomica* c = NULL;
	pilaAstronomica* aux1 = NULL;
	pilaAstronomica* aux2 = NULL;
	
	int variableEnteraA = 0;
	int variableEnteraB = 0;
	int resultado = 0;
	
	while(a != NULL){
		int entero = pop(a);
		push(aux1,a);
		}
	while(b != NULL){
		int entero = pop(b);
		push(aux2,b);
		}
		
	while(aux1 != NULL){
		variableEnteraA = variableEnteraA * 10;
		int entero = pop(aux1);
		variableEnteraA += entero;
	}
	while(aux2 != NULL){
		variableEnteraB = variableEnteraB * 10;
		int entero = pop(aux2);
		variableEnteraB += entero;
	}
	resultado = variableEnteraA + variableEnteraB;
	
	while(resultado > 0){
		int digito = (resultado % 10);
		push(c,digito);
		resultado = resultado / 10;
		}
	
	return c;
}
