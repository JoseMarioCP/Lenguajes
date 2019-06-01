#include <iostream>
#include <string> 
#include <fstream> //libreria para poder haceer la lectura y escritura de archivos

#include "cabecera2.h"
#include "cabecera.h"

#include <stdlib.h>
//#include <time.h>

using namespace std;


//clase de la cual se crea el arreglo para almacenar los valores de las citas en los archivos
class Cita
{
public:
	string hora;
	char idCita;
	string nombre;
};


void ordenamientoHoras(char id)
{
	ofstream archivo;	//objeto para abrir el archivo en escritura
	ifstream archivoL,archivoL2; 	//objetos para abrir el archivo en lectura
	int contador=0; //llevara la cuenta sobre las citas registradas en el archivo
	string linea; //sacar la linea completa del archivo para buscar el delimitador %
	
		//abriendo los archivos dependiendo del id del barbero
		switch(id)
		{
			case '1':
				archivoL.open("archivos/barbero1.txt",ios::in);
				archivoL2.open("archivos/barbero1.txt",ios::in);
			break;
			
			case '2':
				archivoL.open("archivos/barbero2.txt",ios::in);
				archivoL2.open("archivos/barbero2.txt",ios::in);	
			break;
			
			case '3':
				archivoL.open("archivos/barbero3.txt",ios::in);
				archivoL2.open("archivos/barbero3.txt",ios::in);
			break;
			
			case '4':
				archivoL.open("archivos/barbero4.txt",ios::in);
				archivoL2.open("archivos/barbero4.txt",ios::in);	
			break;	
		}
	
	
	if(archivoL.fail())
	{
		cout<<"\nno se pudo leer el archivo";
	}

	//leyendo el archivo hasta llegar al final
	while(!archivoL.eof())
	{
		//INCREMENTADO EL CONTADOR POR CADA linea ENCONTRADO (cita registrada)
		getline(archivoL,linea);
		contador++;
	}
		archivoL.close();

		int indice=0;
		Cita c2[contador]; //arreglo de tipo Cita(clase)
			
		
	if(contador>1) //verificando si se encontro algo en el archivo
	{
		while(!archivoL2.eof())
		{	
		
			//------SACAR LOS DATOS Y ALMACENARLOS EN LOS ATRIBUTOS del arreglo en cada iteracion
			archivoL2>>c2[indice].idCita;
			archivoL2>>c2[indice].hora;
			archivoL2>>c2[indice].nombre;
			
			if(indice<contador-2)	//se verifica si aun no llega al final de numero de citas encontradas
			{
				indice++;
			}else
			{
				break;
			}
		
		}
		
		//METODO DE LA BURBUJA
		string auxiliar="";
		string nomAuxiliar="";
		for(int i=0;i<contador-1;i++)
		{
			for(int j=0;j<contador-1;j++)
			{
					//cout<<"segundo ciclo\n\n";
				if(c2[j].hora.substr(0).compare(c2[j+1].hora)==1)
				{
				auxiliar=c2[j].hora;
				nomAuxiliar=c2[j].nombre;
				
				c2[j].hora=c2[j+1].hora;
				c2[j].nombre=c2[j+1].nombre;
				
				c2[j+1].hora=auxiliar;	
				c2[j+1].nombre=nomAuxiliar;
				}
					
			}		
		}
		
	
		//ABRIENDO EL ARCHIVO PARA ESCRITURA DEPENDIENDO DEL id (parametro)		
		switch(id)
		{
			case '1':
				archivo.open("archivos/barbero1.txt",ios::out); //ABRIENDO EN ESCRITURA	
			break;
			
			case '2':
				archivo.open("archivos/barbero2.txt",ios::out); //ABRIENDO EN ESCRITURA
			break;
			
			case '3':
				archivo.open("archivos/barbero3.txt",ios::out); //ABRIENDO EN ESCRITURA
			break;
			
			case '4':
				archivo.open("archivos/barbero4.txt",ios::out); //ABRIENDO EN ESCRITURA
			break;	
		}
	
		//realizando la escritura en el archivo de donde se leyeron los datos
		//con los datos ya ordenados almacenados en el arreglo
		for(int y=0;y<contador-1;y++)
		{
			archivo<<c2[y].idCita;
			archivo<<" ";
			archivo<<c2[y].hora;
			archivo<<" ";
			archivo<<c2[y].nombre;
			//archivo<<" ";
			archivo<<"\n";
		}
		archivo.close();		
	
	
	}else
	{
		cout<<"\nno hizo el ordenamiento\n";
	}		
	
}

//verifica si la hora esta dentro del rango de servicio de la barberia
bool disponibleTurnosHorarios(string hora)
{	

	const	string primerTurnoEntrada="08:00";
	const	string primerTurnoSalida="13:45";
		
	const	string 	SegundoTurnoEntrada="16:00";
	const	string SegundoTurnoSalida="19:45";

	
	bool disponible; //controla si esta dentro del rango de servicio

			
			
			//verfica si la hora es mayor o identica a la hora de abrir en la maniaana
			if(hora.compare(primerTurnoEntrada)==1 || hora.compare(primerTurnoEntrada)==0)
			{
				
				//verfica si la hora es menor a la hora de cerrar en la maniaana
				if(hora.compare(primerTurnoSalida)==-1 || hora.compare(primerTurnoSalida)==0)
				{
					//cout<<"\ndentro del horario de servicio en la maniana\n";
					disponible=true;
				}
				else
				{
						
					//verfica si la hora es mayor o identica a la hora de abrir en la tarde
					if(hora.compare(SegundoTurnoEntrada)==1 || hora.compare(SegundoTurnoEntrada)==0)
					{
						
						//verfica si la hora es menor a la hora de cerrar en la tarde
						if(hora.compare(SegundoTurnoSalida)==-1 || hora.compare(SegundoTurnoSalida)==0)
						{
						//	cout<<"\ndentro del horario de servicio en la tarde\n";
							disponible=true;
						}else
						{
							
							
							if(hora.compare("20:00")==-1 && hora.compare(SegundoTurnoSalida)==1)
							{
								cout<<"\nLA BARBERIA ESTA POR CERRRAR, ya no se puede registrar citas faltando 15 minutos\n\n";
								disponible=false;
							}else
							{
								//cout<<"\nfuera del horario de servicio en la tarde\n";
								cout<<"\n             ------ Fuera de servicio!!  --------\n\n";
								cout<<"      horarios: MANIANA 08:00 -- 14:00   TARDE 16:00 -- 20:00   \n\n";

								disponible=false;
							}
						
					
						}	
					}	
					else
					{
						
							if(hora.compare("14:00")==-1 && hora.compare(primerTurnoSalida)==1)
							{
								cout<<"\nLA BARBERIA ESTA POR CERRAR, ya no se puede registrar citas faltando 15 minutos\n\n";
								disponible=false;
							}else
							{
								//cout<<"\nfuera del horario de servicio en la tarde\n";
								cout<<"\n               ------ Fuera de servicio!!  --------\n\n";
								cout<<"      horarios: MANIANA 08:00 -- 14:00   TARDE 16:00 -- 20:00   \n\n";

								disponible=false;
							}
		
					}
				}
			}else
			{
				
					cout<<"\n                 ------ Fuera de servicio!!  --------\n\n";
					cout<< "      horarios: MANIANA 08:00 -- 14:00   TARDE 16:00 -- 20:00   \n\n";

					disponible= false;
						
			}
		
		return disponible;	// se retorna el valor despues de hacer la verificacion

}


//se asigna un barbero disponible a una hora introducida
//ya que el cliente no especifico con que barbero deseaba la cita (idbarbero == 0) 
bool asignarBarbero(string hora,string nom)
{
	int contador=0;
	ofstream archivo;	//objeto para escribir
	ifstream archivoL;	//objeto para leer
	string linea;	//captura cada salto de linea en el archivo (lectura)
	char idBar;
	
	
		//--------------se determina que barberos estan disponibles para agregarle la cita ------------//
		
			if(disponible('1',hora)==true)
			{
					archivo.open("archivos/barbero1.txt",ios::app); //ABRIENDO EN ESCRITURA
					archivoL.open("archivos/barbero1.txt",ios::in);
					idBar='1';
			}
			else
			{
				if(disponible('2',hora)==true)
				{
					archivo.open("archivos/barbero2.txt",ios::app); //ABRIENDO EN ESCRITURA
					archivoL.open("archivos/barbero2.txt",ios::in);
					idBar='2';

				}else
				{
					if(disponible('3',hora)==true)
					{		
							archivo.open("archivos/barbero3.txt",ios::app); //ABRIENDO EN ESCRITURA
							archivoL.open("archivos/barbero3.txt",ios::in);
							idBar='3';
					}
					else{
							if(disponible('4',hora)==true)
							{
								archivo.open("archivos/barbero4.txt",ios::app); //ABRIENDO EN ESCRITURA
								archivoL.open("archivos/barbero4.txt",ios::in);
								idBar='4';
							}
					}
						
				}
			
			}
			
				while(!archivoL.eof())
				{
					//VERIFICANDO E INCREMENTADO EL CONTADOR POR CADA cita registrada en el archivo
					getline(archivoL,linea);
					contador++;
				}
				
				//------------haciendo la escritura en el archivo del barbero correspondiente----------//
			
				archivo<<contador;
				archivo<<" ";
				archivo<<hora;
				archivo<<" ";
				archivo<<nom;
				archivo<<" ";
				archivo<<"\n";
				archivo.close();
				
				ordenamientoHoras(idBar); //se realiza el ordenamiento de las citas en el archivo
				cout<<"\n     ------------ REGISTRO EXITOSO CON EL BARBERO "<<idBar<<" ------------\n\n";
			
}

//retorna verdadero si el barbero esta disponible a la hora ingresada
bool disponible(char id,string hora)
{	
	bool disponible=true; //controla si esta disponible un barbero en la hora introducida
	int contador=0; //llevara la cuenta sobre las citas registradas en el archivo
	
	ifstream archivoL,archivo; //objetos para la lectura del archivo
	string linea; //sacar la linea completa del archivo para buscar el delimitador %
	
	switch(id)
	{
		case '1':
			archivoL.open("archivos/barbero1.txt",ios::app); //ABRIENDO EN ESCRITURA	
			archivo.open("archivos/barbero1.txt",ios::app); //ABRIENDO EN ESCRITURA
		break;
		
		case '2':
			archivoL.open("archivos/barbero2.txt",ios::app); //ABRIENDO EN ESCRITURA
			archivo.open("archivos/barbero2.txt",ios::app); //ABRIENDO EN ESCRITURA
		break;
		
		case '3':
			archivoL.open("archivos/barbero3.txt",ios::app); //ABRIENDO EN ESCRITURA	
			archivo.open("archivos/barbero3.txt",ios::app); //ABRIENDO EN ESCRITURA
		break;
		
		case '4':
			archivoL.open("archivos/barbero4.txt",ios::app); //ABRIENDO EN ESCRITURA
			archivo.open("archivos/barbero4.txt",ios::app); //ABRIENDO EN ESCRITURA
		break;	
	}
	
	
	if(archivoL.fail())
	{
		cout<<"no se pudo leer el archivo";
	}
	
	//por cada salto de linea quiere decir que es una cita registrada
	while(!archivoL.eof())
	{
		getline(archivoL,linea);
		contador++;
	}
	
	archivoL.close();	//se cierra el archivo
		
	int indice=0;
	string citaPrevia,citaFinalizada;	//alamacenaran la hora depues de agregarle los 15 minutos 
	
	Cita c2[contador];	//arreglo de tipo "Cita" es la clase que contiene los atributos de cita
	
	
	if(contador>1)	//se verifica si se encontro una cita en registrada en el archivo
	{
		while(!archivo.eof())
		{	
			//------SACAR LOS DATOS Y ALMACENARLOS EN LOS ATRIBUTOS DEL OBJETO
			archivo>>c2[indice].idCita;
			archivo>>c2[indice].hora;
			archivo>>c2[indice].nombre;
			
			//se realiza el incremento de los 15 minutos 
			//false decrementa 15 minutos la hora de la cita
			//true incrementa 15 
			citaPrevia=conversion(c2[indice].hora,false);
			citaFinalizada=conversion(c2[indice].hora,true);
			
			
				
			//verificndo disponibilidad de las horas ya registradas
			
			//-----compare-- -//
			//es un metodo para comparar que cadena es mayor a otra
			//en estos casos de compara la hora ingresada con la hora ya registrada
			
			if(hora.compare(c2[indice].hora)==0)
			{
				//	cout<<" la hora "<<hora<<"  es identica a la hora "<<c2[indice].hora<<"\n";	
				disponible=false;
				break;
			}else
			{
					
				if(hora.compare(citaPrevia)==-1  || hora.compare(citaPrevia)==0) 
				{
					disponible=true;
					//cout<<" la hora "<<hora<<"  es menor a la hora "<<citaPrevia<<"\n";	
				}
				else
				{
					
					if(hora.compare(citaFinalizada)==1 || hora.compare(citaFinalizada)==0)
						{
							disponible=true;
							//	cout<<" la hora "<<hora<<"  es mayor a la hora "<<citaFinalizada<<"\n";	
						}else{
							
							//cout<<"\nsegundo break hora no mayor a la finalizada "<<citaFinalizada;
							disponible=false;
							break;
						}
				}
			}
			
			//si aun no llega al final de numero de salto de linea(citas registradas en el archivo) 
			//sigue sacando los datos de las citas para agregarlos al arreglo
			if(indice<contador-2 && disponible==true)
			{
				indice++;
			}else
			{
				break;
			}
		
		}//while
		
		
		if(disponible==true)
		{
			//cout<<"\nse puede registrar!\n";
			return disponible;
		}else
		{	
	
			//cout<<"\nNO SE PUEDE registrar!!\n";
			return disponible;
		}
		
	}else
	{
		//cout<<"\narchivo vacio\n";
		
		//no se ha encontrado ninguna cita en el archivo
		return disponible;
	}
	
}



//verifica que barberos estan disponibles a la hora ingresada para la cita 
//y retorna el numero de barberos disponibles
int otrosDisponibles(string hora)
{
	
	int barberos=0;
	
			if(disponible('1',hora)==true)
			{
					cout<<"\nel barbero 1 esta disponible a esa hora";
				barberos++;
			}
			
			if(disponible('2',hora)==true)
			{	
				cout<<"\nel barbero 2 esta disponible a esa hora";
				barberos++;
			}
			
			if(disponible('3',hora)==true)
			{
				cout<<"\nel barbero 3 esta disponible a esa hora";
				barberos++;
			}
				
			if(disponible('4',hora)==true)
			{
				cout<<"\nel barbero 4 esta disponible a esa hora";
				barberos++;
			}
	return barberos;
}



//original
void registrarCita()
{
								//-----------ESCRITURA EN EL ARCHIVO=--------------//		
	int contador=0;	
	char idBarbero;
	string horaCita;
	string linea;
	Cita cita;
	bool fueraServicio=true;
	ofstream archivo;
	ifstream archivoL;
	
	//etiqueta
	formatoHoras:
		
	cout<<"\n\nintrodusca la hora para la cita en formato de 24 hrs. \n         EJEMPLO -- 17:25 -- 09:30 \n\n\nDijite su hora: ";
	cin>>cita.hora;
		
			// ---------------- verificando el formato de las horas ---------------------//
			if(cita.hora.size()<5 || cita.hora.size()>5)
			{
				cout<<"\n------- LA HORA NO ES VALIDA ----------  \n\n" ;
				goto formatoHoras;
			}
			else{
			
			
				if(cita.hora.substr(0,2).compare("23")==1 || cita.hora.substr(3,2).compare("60")==1 || cita.hora.find(":")!=2 )
				{	
							cout<<"\n------- LA HORA NO ES VALIDA--------  \n\n\n" ;
					goto formatoHoras;
				}
			}
			
	
	//retorna true en caso de estar la hora dentro del rango de servicio de la barberia	
	//o false en caso de no estar dentro del rango
	fueraServicio=disponibleTurnosHorarios(cita.hora);
		
		
	if(fueraServicio==true)	
	{
		
		//etiqueta
			barberosDisponibles:
				
			// se verifica medieante el valor de retorno si almenos hay un barbero disponible a la hora tecleada 
			if(otrosDisponibles(cita.hora)>0)	
			{
				
				//barbero:
				cout<<"\n\nintrodusca con que barbero desea la cita: \n ";
				cin>>idBarbero;
				
				
				if(idBarbero!='1' && idBarbero!='2' && idBarbero!='3' && idBarbero!='4' &&  idBarbero!='0') 
				{
					cout<<"\n      -------------   ESE BARBERO NO EXISTE   -----------------\n\n\n";
					goto barberosDisponibles;
				
				}
				
				if(idBarbero=='0') //no se especifica con que barbero y se asignara alguno disponible
				{
							cin.ignore();
							cout<<"\n introdusca tu(s) nombre(s): ";
							getline(cin,cita.nombre);
							
							//se verifica si hay dos nombres para coloca en el espacio en blanco entre los dos un guin (-)
							int palabra=0;
							string reserva1="",reserva2="";
							while(palabra<cita.nombre.length())
							{
								if(cita.nombre.substr(palabra,1)==" ")
								{
									reserva1=cita.nombre.substr(0,palabra);
									//cout<<"primer nombre "<<reserva1<<"\n";
									reserva2=cita.nombre.substr(palabra+1);
									//cout<<"cadena de nombre "<<reserva2<<"\n";
									cita.nombre=reserva1+"-";
									cita.nombre+=reserva2;
									break;
								}
								palabra++;
							}
							
					 //se asigna la cita al primer barbero dispoonible a la hora tecleada
					asignarBarbero(cita.hora,cita.nombre);
					
				}else
				{
			
						if(disponible(idBarbero,cita.hora)==true)
						{
								
							switch(idBarbero)
							{
								case '1':
									archivo.open("archivos/barbero1.txt",ios::app); //ABRIENDO EN ESCRITURA	
									archivoL.open("archivos/barbero1.txt",ios::in);	//abriendo en lectura
									
								break;
								
								case '2':
									archivo.open("archivos/barbero2.txt",ios::app); //ABRIENDO EN ESCRITURA
									archivoL.open("archivos/barbero2.txt",ios::in); //abriendo en lectura
									
								break;
								
								case '3':
									archivo.open("archivos/barbero3.txt",ios::app); //ABRIENDO EN ESCRITURA
									archivoL.open("archivos/barbero3.txt",ios::in); //abriendo en lectura
								
								break;
								
								case '4':
									archivo.open("archivos/barbero4.txt",ios::app); //ABRIENDO EN ESCRITURA
									archivoL.open("archivos/barbero4.txt",ios::in);	//abriendo en lectura
									
								break;	
							}
							
							if(archivo.fail()){cout<<"no se pudo crear el archivo";}
							
							
							while(!archivoL.eof())
							{
								//VERIFICANDO E INCREMENTADO EL CONTADOR POR CADA salto de linea en el archivo
								getline(archivoL,linea);
								contador++;
							}
								
							//---------------- captura el nombre para agregarlo de manera correcta al archivo--------
							//se verifica si hay dos nombres para coloca en el espacio en blanco entre los dos un guin (-)
							cin.ignore();
							cout<<"\n introdusca tu(s) nombre(s): ";
							getline(cin,cita.nombre);
							
							int palabra=0;
							string reserva1="",reserva2="";
							while(palabra<cita.nombre.length())
							{
								if(cita.nombre.substr(palabra,1)==" ")
								{
									reserva1=cita.nombre.substr(0,palabra);
									//cout<<"primer nombre "<<reserva1<<"\n";
									reserva2=cita.nombre.substr(palabra+1);
									//cout<<"cadena de nombre "<<reserva2<<"\n";
									cita.nombre=reserva1+"-";
									cita.nombre+=reserva2;
									break;
								}
								palabra++;
							}
							
							// ------- realizando la escritura en el archivo----------
							archivo<<contador;
							archivo<<" ";
							archivo<<cita.hora;
							archivo<<" ";
							archivo<<cita.nombre;
							archivo<<" ";
							archivo<<"\n";
							archivo.close();
							
							
							ordenamientoHoras(idBarbero); // se ordenara las citas en el archivo
							
							cout<<"\n     ------------ REGISTRO EXITOSO con el barbero "<<idBarbero<<" ------------\n\n";
						
						}else
						{
							cout<<"\n ------NO SE PUEDE REGISTRAR - Barbero ocupado seleccione uno de los disponibles!!\n\n";
							goto barberosDisponibles;
						}
							
				} //barbero elegido por id
				
			}else
			{
				int respuesta=0;
				cout<<"\n\nLo Sentimos, NO hay ningun barbero disponible a esa hora...";
				cout<<"\nDesea escoger otra hora?? \n1-Si\n2-No";
				cin>>respuesta;
				
				if(respuesta>0 && respuesta<2)
				{
					if(respuesta==1)
					goto formatoHoras;
					
				}
				
			}
			
			
	}else
	{
		//	cout<<"\n     ------ Fuera de servicio!!  --------\n\n";
		//cout<<"     horarios manana --  08:00 a 14:00\n";
		//cout<<"     horarios  tarde --  16:00 a 20:00\n\n";
		goto formatoHoras;
		
	}
			
}

//mostrar unicamente la lista de las citas registradas por el id del barbero que se le pasa por parametro
void mostrarListasDeEspera(char id)
{
	string citaFinalizada=""; 	
		
	int contador=0; //llevara la cuenta sobre las citas registradas en el archivo
	ifstream archivoL;
	ifstream archivoL2;
	
	string linea; //sacar la linea completa del archivo para buscar el delimitador %
	
	
	switch(id)
	{
		case '1':
			archivoL.open("archivos/barbero1.txt",ios::app); //ABRIENDO EN lectura	
			archivoL2.open("archivos/barbero1.txt",ios::app);
			
		break;
		
		case '2':
			archivoL.open("archivos/barbero2.txt",ios::app); //ABRIENDO EN lectura
			archivoL2.open("archivos/barbero2.txt",ios::app);
			
		break;
		
		case '3':
			archivoL.open("archivos/barbero3.txt",ios::app); //ABRIENDO EN lectura	
			archivoL2.open("archivos/barbero3.txt",ios::app);
		
		break;
		
		case '4':
			archivoL.open("archivos/barbero4.txt",ios::app); //ABRIENDO EN ESCRITURA
			archivoL2.open("archivos/barbero4.txt",ios::app);
		
		break;
		
		//default:cout<<"\nno existe ese barbero\n";	
	}

	if(archivoL.fail())
	{
		cout<<"\nno se pudo leer el archivo de la ruta o la carpeta \"archivos\" no existe ";
		
	}

	while(!archivoL.eof())
	{
		//VERIFICANDO E INCREMENTADO EL CONTADOR POR CADA cita ENCONTRADO
		getline(archivoL,linea);
		contador++;
	}
		archivoL.close();
		
		
		int indice=0;
		
		Cita c2[contador]; //arreglo que contendra los valores de cada cita 
		
	if(contador>1)
	{
		cout<<"\n\n-------------lectura de horario del barbero "<<id<<" --------------------\n\n";
		cout<<"idCita -- horarioCita -- horaFinalizada -- nombreCliente ";
		while(!archivoL2.eof())
		{	
		
			//------SACAR LOS DATOS Y ALMACENARLOS EN LOS ATRIBUTOS DEL OBJETO
			archivoL2>>c2[indice].idCita;
			archivoL2>>c2[indice].hora;
			archivoL2>>c2[indice].nombre;
			citaFinalizada=conversion(c2[indice].hora,true);
	
			//sacar el nombre si es que tiene dos nombres al encontrar el - (guion) lo remplaza por un espacio en blanco
			int palabra=0;
			string reserva1="",reserva2="";
			while(palabra<c2[indice].nombre.length())
			{
				if(c2[indice].nombre.substr(palabra,1)=="-")
				{
					reserva1=c2[indice].nombre.substr(0,palabra);
					//cout<<"primer nombre "<<reserva1<<"\n";
					reserva2=c2[indice].nombre.substr(palabra+1);
					//cout<<"cadena de nombre "<<reserva2<<"\n";
					c2[indice].nombre=reserva1+" ";
					c2[indice].nombre+=reserva2;
					break;
				}
				palabra++;
			}
	

			cout<<"\n  "<<c2[indice].idCita;
			cout<<"   ----   "<<c2[indice].hora;
			cout<<"   ----   "<<citaFinalizada;
			cout<<"   ----   "<<c2[indice].nombre;
			
			//si un ha llegado al numeeroo de citas encontradas se incrementa para seguir leyendo
			if(indice<contador-2)
			{
				indice++;
			}else
			{
				break;
			}
		
		}
	}else
	{
			cout<<"\n\n-------------lectura de horario del barbero "<<id<<" --------------------\n\n";
			cout<<"           ------  No hay citas ------\n";
	}		
}


//mostrar las citas registradas de un barbero o todos , dependiendo de la opcion que teclee el usuario
void listaEspera()
{	

	string citaFinalizada="";  //guarda la hora en que termina una cita	
		
	int contador=0;	 //llevara la cuenta sobre las citas registradas en el archivo
	ifstream archivoL; 		//objeto para realizar la escritura
	ifstream archivoL2;		//objeto para realizar la escritura
	
	string linea; //sacar la linea completa del archivo para buscar el delimitador (salto de linea)
	
	char id; //para elegir a un barbero
	
	//etiqueta
	barbero:
		
	cout<<"\nintrodusca el id del barbero para ver su lista de espera: ";
	cin>>id;
	
		if(id!='1' && id!='2' && id!='3' && id!='4' && id!='0') 
			{
				cout<<"\n      -------------   ESE BARBERO NO EXISTE   -----------------\n\n";
				goto barbero;
			
			}
	
	
	if(id=='0')
	{
		mostrarListasDeEspera('1');
		mostrarListasDeEspera('2');
		mostrarListasDeEspera('3');
		mostrarListasDeEspera('4');
	}else
	{
			//----------------- Mostrar los datos del barbero seleccionado--------------
			switch(id)
			{
				case '1':
					archivoL.open("archivos/barbero1.txt",ios::app); //ABRIENDO EN lectura	
					archivoL2.open("archivos/barbero1.txt",ios::app);
					
				break;
				
				case '2':
					archivoL.open("archivos/barbero2.txt",ios::app); //ABRIENDO EN lectura
					archivoL2.open("archivos/barbero2.txt",ios::app);
					
				break;
				
				case '3':
					archivoL.open("archivos/barbero3.txt",ios::app); //ABRIENDO EN Lectura	
					archivoL2.open("archivos/barbero3.txt",ios::app);
				
				break;
				
				case '4':
					archivoL.open("archivos/barbero4.txt",ios::app); //ABRIENDO EN lectura
					archivoL2.open("archivos/barbero4.txt",ios::app);
				
				break;
				
				case '0':
				
				break;
				
				default:cout<<"\nno existe ese barbero\n";	
			}
		
			if(archivoL.fail())
			{
				cout<<"\nno se pudo leer el archivo de la ruta o la carpeta \"archivos\" no existe ";
				
			}
		
			while(!archivoL.eof())
			{
				//VERIFICANDO EL DELIMITADOR % E INCREMENTADO EL CONTADOR POR CADA DELIMITADOR ENCONTRADO
				getline(archivoL,linea);
				contador++;
			}
				archivoL.close();
				
				
				int indice=0;
				//cout<<"valor de contador "<<contador<<"\n";
				Cita c2[contador];
				
			if(contador>1)	//se verifica si se encontro almenos una cita registrara con el barbero seleccionado
			{
				cout<<"\n\n-------------lectura de horario del barbero "<<id<<" --------------------\n\n";
				cout<<"idCita -- horarioCita -- horaFinalizada -- nombreCliente ";
				while(!archivoL2.eof())
				{	
				
					//------SACAR LOS DATOS Y ALMACENARLOS EN LOS ATRIBUTOS DEL OBJETO
					archivoL2>>c2[indice].idCita;
					archivoL2>>c2[indice].hora;
					archivoL2>>c2[indice].nombre;
					citaFinalizada=conversion(c2[indice].hora,true);
			
			
				//sacar el nombre si es que tiene dos nombres al encontrar el - (guion) lo remplaza por un espacio en blanco
					int palabra=0;
					string reserva1="",reserva2="";
					while(palabra<c2[indice].nombre.length())
					{
						if(c2[indice].nombre.substr(palabra,1)=="-")
						{
							reserva1=c2[indice].nombre.substr(0,palabra);
							//cout<<"primer nombre "<<reserva1<<"\n";
							reserva2=c2[indice].nombre.substr(palabra+1);
							//cout<<"cadena de nombre "<<reserva2<<"\n";
							c2[indice].nombre=reserva1+" ";
							c2[indice].nombre+=reserva2;
							break;
						}
						palabra++;
					}
			
			
			
					cout<<"\n  "<<c2[indice].idCita;
					cout<<"   ----   "<<c2[indice].hora;
					cout<<"   ----   "<<citaFinalizada;
					cout<<"   ----   "<<c2[indice].nombre;
					
					//si un ha llegado al numeeroo de citas encontradas se incrementa para seguir leyendo
					if(indice<contador-2)
					{
						indice++;
					}else
					{
						break;
					}
				
				}
			}else
			{
					cout<<"\n\n-------------lectura de horario del barbero "<<id<<" --------------------\n\n";
					cout<<"           ------  No hay citas ------\n";
			}
	}//mostrar barbero por su id
			
}

