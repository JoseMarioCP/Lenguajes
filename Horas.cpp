#include <iostream>
#include <string> 
#include <sstream>
#include "cabecera.h"

using namespace std;

//sacar los caracteres que representan las horas
string Hora_numero(string hora)
{
	int posicion=0;
	
	for(int i=0;i<hora.size();i++)
	{
		if(hora.substr(i,1)==":")
		{
			posicion=i;
		}
	}
	
	return hora.substr(0,posicion);
	
}

//sacar los caracteres que representan los minutos
string Minutos_numero(string hora)
{
	int posicion=0;
	
	for(int i=0;i<hora.size();i++)
	{
		if(hora.substr(i,1)==":")
		{
			posicion=i;
		}
	}
	
	return hora.substr(posicion+1);
	
}


//sumarle los 15 minutos que dura la cita
string conversion(string tiempo,bool Incrementa)
{
	stringstream stream1,stream2; //objetos para poder hacer la conversion de string a entero
	int H=0,M=0;
	string hora,minuto;
	hora=Hora_numero(tiempo); //llama al metodo que saca los caracteres que representan las horas
	minuto=Minutos_numero(tiempo); //llama al metodo que saca los caracters que representan los minutos
	
		//string to int
		stream1.str("");
		stream1.str(hora);	//se le pasa la cadena que tiene las horas
		stream1 >> H;	//la conversion se guarda en una variable de tipo int
		
		stream2.str(" ");
		stream2.str(minuto);
		stream2 >> M;
		
		
		//------de acuerdo al valor del parametro "Incrementa" se sumara los 15 minutos o se restara-----
		
		if(Incrementa==true)
			M=M+15;
		if(Incrementa==false)
			M=M-15;
		
		int minutosSobrados=0;	//guarda los minutos que se sumaran o restaran dependiendo de la hora en cuestion
		
		
		if(M>=60)		//se verifica que los minutos no pasen de 60
		{
			if(H>=23)	// se verifica que las horas no pasen de 24 
			{
				H=0;
				minutosSobrados=M-60;
				M=0;
				M=M+minutosSobrados;
			}
			else
			{
				H++;
				minutosSobrados=M-60;
				M=0;
				M=M+minutosSobrados;
			}
		}else{
		
			if(M<0)
			{
				H--;
		
				M=60+M;
			}
			
			if(M==0)
			{
				H--;
				
				M=0;
			}
		}
	
		if(H>=10)
		{
			
			stringstream ss;
			ss << H;
			hora= ss.str();			
		}else{
			
	
			stringstream ss;
			ss << H;
			hora="0";
			hora+= ss.str();			
		}
	
		if(M>=10)
		{
			stringstream ss2;
			ss2 << M;
			minuto= ss2.str();
				
		}else
		{
			stringstream ss2;
			ss2 << M;
			minuto="0";
			minuto+= ss2.str();
				
		}
	
	
	return hora+":"+minuto;
	
}


