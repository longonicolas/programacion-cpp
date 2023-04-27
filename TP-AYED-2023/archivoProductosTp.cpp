#include <iostream>

using namespace std;

struct precios{
	
	int idProducto;
	int precio;
	char nombreProducto[30+1];
};

void cargarProducto(FILE*);
void mostrarInventario(FILE*);

int main(){
	
	FILE* p;
	int decision;
	
	cout<<"1- Mostrar productos y precios"<<endl;
	cout<<"2- Cargar un producto"<<endl;
	cin>>decision;
	
	switch(decision){
		
		case 1:
		p = fopen("precios.dat", "rb");
		mostrarInventario(p);
		break;
		
		case 2:
		p = fopen("precios.dat", "rb+");
		cargarProducto(p);
		break;
	}
	
	return 0;
}

void mostrarInventario(FILE* p){
	
	precios prod;
	
		while(fread(&prod,sizeof(precios),1,p)){
		
		cout<<prod.nombreProducto<<endl;
		cout<<"Id del producto: "<<prod.idProducto<<endl;
		cout<<"Precio: "<<prod.precio<<endl;
		cout<<endl;
	}
	
	fclose(p);
	
}

void cargarProducto(FILE* p){
	
	precios producto;
	
	//como antes usamos cin, utilizamos cin.ignore() para limpiar el baffer
	cin.ignore();
	
	cout<<"Nombre producto"<<endl;
	cin.getline(producto.nombreProducto,30);
	
	cout<<"id Producto"<<endl;
	cin>>producto.idProducto;
	
	cout<<"Precio"<<endl;
	cin>>producto.precio;
	
	//ponemos el puntero al final del archivo con fseek para que se guarde al final del archivo
	fseek(p,0,SEEK_END);
	fwrite(&producto,sizeof(precios),1,p);
	fclose(p);
	}
	
