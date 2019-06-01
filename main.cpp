#include <iostream>
#include <string>
#include <fstream>

#include "cabecera.h"
#include "cabecera2.h"
//#include "ordenamiento.cpp"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;


void menu()
{
	
	char opcion=0;
	string menu="\n\n\n\n           -------------   REGISTRO DE CITAS PARA BARBERIA   --------------";
			menu+="\n            horarios: MANIANA 08:00 -- 14:00   TARDE 16:00 -- 20:00   ";
			menu+="\n\n\nEliga una opcion del menu:\n\n     1-registrar cita";
			menu+="\n     2-ver lista de espera de un barbero\n     3-salir\n\nOpcion: ";
	
	
	do{
		
		
		menu:
			cout<<menu;
			cin>>opcion;
			
			
				if(opcion!='1' && opcion!='2' && opcion!='3') 
				{
					cout<<"\n      -------------   Opcion no valida del menu principal  -----------------\n\n\n";
					goto menu;
				
				}
			
	
			switch(opcion)
			{
				case '1': 
					registrarCita();
								
				break;
									
				case '2': 
					listaEspera();
				break;
									
				case '3': 
					cout<<"\nSaliendo\n";
									
				break;
									
				default: cout<<"\n\n     ---------- OPCION NO VALIDA DEL MENU PRINCIPAl -----------\n";
									
			}
								
	}while(opcion!='3');
		
}


int main(int argc, char** argv) 
{
	menu();
	
	system("PAUSE");
	return 0;
}
