struct tipoCabina{
	
	int horaRegistro;
	char patente[10+1];
	int tipoVehiculo;
};
struct tipoCabinaMixta{
	
	int horaRegistro;
	char patente[10+1];
	int tipoVehiculo;
	char tipoDePago; // M manual, T telepase
};

int main(){
	
	FILE* manual1; 
	FILE* manual2; 
	FILE* tele1; 
	FILE* tele2;
	FILE* mixta1;
	FILE* mixta2;
	FILE* archivoApareado;
	
	return 0;
}


void aparearArchivos(FILE* manual1, FILE* manual2, FILE* tele1, FILE* tele2, FILE* mixta1, FILE* mixta2, FILE* archivoApareado){
	
	tipoCabina cabM1, cabM2, cabT1, cabT2;
	tipoCabinaMixta mix1, mix2, final;
	
	fread(&cabM1,sizeof(cabM1),1,manual1);
	fread(&cabM2,sizeof(cabM2),1,manual2);
	fread(&cabT1,sizeof(cabT1),1,tele1);
	fread(&cabT2,sizeof(cabT2),1,tele2);
	fread(&mix1,sizeof(mix1),1,mixta1);
	fread(&mix2,sizeof(mix2),1,mixta2);
	
	
	while(!feof(manual1) && !feof(manual2) && !feof(tele1) && !feof(tele2) && !feof(mixta1) && !feof(mixta2)){
		
		if(cabM1.horaRegistro < cabM2.horaRegistro && cabM1.horaRegistro < cabT1.horaRegistro &&
		   cabM1.horaRegistro < cabT2.horaRegistro && cabM1.horaRegistro < mix1.horaRegistro && 
		   cabM1.horaRegistro < mix2.horaRegistro){
			
			final.horaRegistro = cabM1.horaRegistro;
			strcpy(final.patente,cabM1.patente);
			final.tipoVehiculo = cabM1.tipoVehiculo;
			final.tipoDePago = 'M';
			
			fwrite(&final,sizeof(final),1,archivoApareado);
			fread(&cabM1,sizeof(cabM1),1,manual1);
			}
		
		else if(cabM2.horaRegistro < cabT1.horaRegistro && cabM2.horaRegistro < cabT2.horaRegistro && cabM2.horaRegistro < mix1.horaRegistro
				&& cabM2.horaRegistro < mix2.horaRegistro){
					
				final.horaRegistro = cabM2.horaRegistro;
				strcpy(final.patente,cabM2.patente);
				final.tipoVehiculo = cabM2.tipoVehiculo;
				final.tipoDePago = 'M';
				
				fwrite(&final,sizeof(final),1,archivoApareado);
				fread(&cabM2,sizeof(cabM2),1,manual2);
				}
		
		else if(cabT1.horaRegistro < cabT2.horaRegistro && cabT1.horaRegistro < mix1.horaRegistro && cabT1.horaRegistro < mix2.horaRegistro){
			
				final.horaRegistro = cabT1.horaRegistro;
				strcpy(final.patente,cabT1.patente);
				final.tipoVehiculo = cabT1.tipoVehiculo;
				final.tipoDePago = 'T';
				
				fwrite(&final,sizeof(final),1,archivoApareado);
				fread(&cabT1,sizeof(cabT1),1,tele1);		
				}
		
		else if(cabT2.horaRegistro < mix1.horaRegistro && cabT2.horaRegistro < mix2.horaRegistro){
			
				final.horaRegistro = cabT2.horaRegistro;
				strcpy(final.patente,cabT2.patente);
				final.tipoVehiculo = cabT2.tipoVehiculo;
				final.tipoDePago = 'T';
				
				fwrite(&final,sizeof(final),1,archivoApareado);
				fread(&cabT2,sizeof(cabT2),1,tele2);		
				}
		
		else if(mix1.horaRegistro < mix2.horaRegistro){
			
				final = mix1;
				fwrite(&final,sizeof(final),1,archivoApareado);
				fread(&mix1,sizeof(mix1),1,mixta1);		
				}
		
		else{
			final = mix2;
			fwrite(&final,sizeof(final),1,archivoApareado);
			fread(&mix2,sizeof(mix2),1,mixta2);	
			}				
		}
		
	while(!feof(manual1)){
		
		final.horaRegistro = cabM1.horaRegistro;
		strcpy(final.patente,cabM1.patente);
		final.tipoVehiculo = cabM1.tipoVehiculo;
		final.tipoDePago = 'M';		
		
		fwrite(&final,sizeof(final),1,archivoApareado);
		fread(&cabM1,sizeof(cabM1),1,manual1);	
		}
		
	while(!feof(manual2)){
		
		final.horaRegistro = cabM2.horaRegistro;
		strcpy(final.patente,cabM2.patente);
		final.tipoVehiculo = cabM2.tipoVehiculo;
		final.tipoDePago = 'M';		
		
		fwrite(&final,sizeof(final),1,archivoApareado);
		fread(&cabM2,sizeof(cabM2),1,manual2);	
		}
		
	while(!feof(tele1)){
		
		final.horaRegistro = cabT1.horaRegistro;
		strcpy(final.patente,cabT1.patente);
		final.tipoVehiculo = cabT1.tipoVehiculo;
		final.tipoDePago = 'T';		
		
		fwrite(&final,sizeof(final),1,archivoApareado);
		fread(&cabT1,sizeof(cabT1),1,tele1);	
		}	
			
	while(!feof(tele2)){
		
		final.horaRegistro = cabT2.horaRegistro;
		strcpy(final.patente,cabT2.patente);
		final.tipoVehiculo = cabT2.tipoVehiculo;
		final.tipoDePago = 'T';		
		
		fwrite(&final,sizeof(final),1,archivoApareado);
		fread(&cabT2,sizeof(cabT2),1,tele2);	
		}

	while(!feof(mixta1)){
		
		final = mix1;	
		fwrite(&final,sizeof(final),1,archivoApareado);
		fread(&mix1,sizeof(mix1),1,mixta1);	
		}		
				
	while(!feof(mixta2)){
		
		final = mix2;	
		fwrite(&final,sizeof(final),1,archivoApareado);
		fread(&mix2,sizeof(mix2),1,mixta2);	
		}		
		
}
