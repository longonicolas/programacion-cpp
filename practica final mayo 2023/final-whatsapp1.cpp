#include <iostream>
using namespace std;

struct tipoConversacion{
	
	int idConversacion;
	char nombre[30+1];
	bool notificar; //0 notificaciones desactivadas, 1 activadas
	bool vistaPrevia; //0 sin vista previa, 1 con
};
struct nodo{
	
	tipoConversacion info;
	nodo* sgte;
}
struct tipoVector{
	
	int idUsuario;
	char nombreContacto[30+1];
	bool bloqueado; //0 no bloqueado, 1 bloqueado
};
struct Mensaje{
	char msj[300+1];
};

void notificarMensajeRecibido(nodo* listaConversaciones, tipoVector contactos[], int cantContactos, int idConver, int idUsuario, Mensaje mensaje){
	
	nodo* aux = listaConversaciones;
	
	while(aux != NULL){
		if(aux->info.idConversacion == idConver){
			for(int i=0; i<cantContactos; i++){
				if(contactos[i].idUsuario == idUsuario){
					if(aux->info.notificar == 0 || contactos[i].bloqueado == 1)
						return; //no se emite el mensaje
						
					else{
						if(aux->info.nombre == ""){ //es un particular
						
							if(aux->info.vistaPrevia == 0){ //sin vista previa
								if(contactos[i].nombreContacto == ""){  //no lo tiene agendado
									string x = numeroTelefonicoUsuario(contactos[i].idUsuario);
									emitirMensaje(x,"Nuevo mensaje");
									return;
									}
								else{ //agendado
									emitirMensaje(contactos[i].nombreContacto,"Nuevo mensaje");
									return;
									}
								}
								
							else{ //con vista previa
								if(contactos[i].nombreContacto == ""){
									string x = numeroTelefonicoUsuario(contactos[i].idUsuario);
									string y = vistaPrevia(mensaje);
									emitirMensaje(x,y);
									return;
									}
								else{
									string y = vistaPrevia(mensaje);
									emitirMensaje(contactos[i].nombreContacto,y);
									return;
									}
								}	
							}
							
						else{ //es un grupo
							if(aux->info.vistaPrevia == 0){
								if(contactos[i].nombreContacto == ""){
									string x = numeroTelefonicoUsuario(contactos[i].idUsuario);
									emitirMensaje(aux->info.nombre,"Nuevo mensaje de" + x);
									return;
									}
								else{
									emitirMensaje(aux->info.nombre,"Nuevo mensaje de" + contactos[i].nombreContacto);
									return;
									}
								}
							
							else{
								if(contactos[i].nombreContacto == ""){
									string x = numeroTelefonicoUsuario(contactos[i].idUsuario);
									string y = vistaPrevia(mensaje);
									emitirMensaje(aux->info.nombre,x + y);
									return;
									}
								else{
									string y = vistaPrevia(mensaje);
									emitirMensaje(aux->info.nombre,contactos[i].nombreContacto + y);
									return;
									}
								
								}
							
							}
							
					}
				}
			}
		}
		aux = aux->sgte;
		}
		
	
	cout<<"No se ha podido enviar el mensaje";
	return;
}
