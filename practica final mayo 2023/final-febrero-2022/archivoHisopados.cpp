#include <iostream>

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

void cargarHisopado(FILE*);
void mostrarHisopados(FILE*);

int main(){
	
	FILE* p;
	int decision;
	
	cout<<"1- Mostrar hisopados"<<endl;
	cout<<"2- Cargar un hisopado"<<endl;
	cin>>decision;
	
	switch(decision){
		
		case 1:
		p = fopen("hisopados.dat", "rb");
		mostrarHisopados(p);
		break;
		
		case 2:
		p = fopen("hisopados.dat", "rb+");
		cargarHisopado(p);
		break;
	}
	
	return 0;
}

void mostrarHisopados(FILE* p){
	
	archivoHisopados persona;
	
		while(fread(&persona,sizeof(persona),1,p)){
		
		cout<<"NOMBRE: "<<persona.apeYNom<<endl;
		cout<<"DNI: "<<persona.DNI<<endl;
		cout<<"fecha nacimiento:"<<persona.fechaNacimiento<<endl;
		cout<<"Tipo de test"<<persona.tipoDeTest<<endl;
		cout<<"Resultado"<<persona.resultadoTest<<endl;
	}
	
	fclose(p);
	
}

void cargarHisopado(FILE* p){
	
	archivoHisopados persona;
	
	//como antes usamos cin, utilizamos cin.ignore() para limpiar el baffer
	cin.ignore();
	
	cout<<"Nombre hisopado"<<endl;
	cin.getline(persona.apeYNom,30);
	
	cout<<"DNI"<<endl;
	cin>>persona.DNI;
	
	cout<<"fecha nacimiento (ENTERO)"<<endl;
	cin>>persona.fechaNacimiento;
	
	cout<<"Tipo de test"<<endl;
	cin>>persona.tipoDeTest;
	
	cout<<"Resultado"<<endl;
	cin>>persona.resultadoTest;
	
	//ponemos el puntero al final del archivo con fseek para que se guarde al final del archivo
	fseek(p,0,SEEK_END);
	fwrite(&persona,sizeof(persona),1,p);
	fclose(p);
	}
	
