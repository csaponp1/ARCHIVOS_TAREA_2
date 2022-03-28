#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include<stdlib.h>
#include<conio.h>

using namespace std;

const char *nombre_archivo = "archivo.dat";
const char *temporal = "temp.dat";

struct Estudiante{
	int codigo;
	char nombre[50];
	char apellido[50];
	char direccion[50];
	int telefono;
};
void crear();
void leer();
void actualizar();
void eliminar();
void consultar();
int consultar1(int &cod);

main(){
	
	int op;
	bool ciclo = true;

	do
	{
	cout<<"-------------------BIENVENIDO AL COLEGIO LA BENDICION-----------------------"<<endl;
	cout<<"1. Crear estudiante"<<endl;
	cout<<"2. Leer registros"<<endl;
	cout<<"3. Modificar Registros"<<endl;
	cout<<"4. Borrar Estudiante"<<endl;
	cout<<"5. Consultar "<<endl;
	cout<<"6. Salir"<<endl;
	cout<<"ELIJA...!!"<<endl;
	cin>>op;
	
		switch(op){
			
			case 1:
				crear();
				break;

			case 2:
				leer(); 
				break;

			case 3:
				actualizar();
				break;

			case 4:
				eliminar();
				break;

			case 5:
				consultar();
				break;

			case 6:
				ciclo = false;
				break;

			default:
				cout<<"opcion invalida. Verifique!"<<endl;
		}
	} while (ciclo!=0);
	

	
system("pause");
}


void crear(){
	leer();
	FILE *archivo = fopen(nombre_archivo,"ab");
	char continuar;
	int respuesta;
	int id=0,cod=0;
	Estudiante estudiante, *p_estudiante=&estudiante;
	string nombre,apellido,direccion;
	
	do{
		fflush(stdin);
			
			do{
				cout<<"Ingrese Codigo:";
				cin>>cod;
				respuesta=consultar1(cod);
			}while (respuesta==1);
			p_estudiante->codigo=cod;
			cin.ignore();
			
			cout<<"Ingrese Nombres:";
			getline(cin,nombre);
			strcpy(p_estudiante->nombre,nombre.c_str());
			
			cout<<"Ingrese Apellidos:";
			getline(cin,apellido);
			strcpy(p_estudiante->apellido,apellido.c_str());

			cout<<"Ingrese Direccion: ";
			getline(cin,direccion);
			strcpy(p_estudiante->direccion,direccion.c_str());
			
			cout<<"Ingrese Telefono:";
			cin>>p_estudiante->telefono;
			cin.ignore();
			delete [] p_estudiante->nombre;
			delete [] p_estudiante->apellido;
			delete [] p_estudiante->direccion;
			fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		
		cout<<"Desea Agregar otro Estudiante (s/n):";
		cin>>continuar;
	}while(continuar=='s' || continuar=='S');
	fclose(archivo);

	leer();
	
	}

void leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo = fopen(nombre_archivo,"w+b");
	}
	Estudiante estudiante,*p_estudiante=&estudiante;
	int id=0;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"id"<<"|"<<"Codigo"<<"|"<<"Nombres"<<"|"<<"Apellidos"<<"|"<<"Direccion"<<"|"<<"Telefono"<<endl;
	do{
		cout<<"_____________________________________________________________________"<<endl;
		
cout<<id<<" | "<<p_estudiante->codigo<<" | "<<p_estudiante->nombre<<" | "<<p_estudiante->apellido<<" | "<<p_estudiante->direccion<<" | "<<p_estudiante->telefono<<endl;
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}

void actualizar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	int id;
	Estudiante estudiante,*p_estudiante=&estudiante;
	string nombre,apellido,direccion;
	cout<<"Ingrese el Id a Modificar:";
	cin>>id;
	fseek(archivo,id *sizeof(Estudiante),SEEK_SET);
			
			cout<<"Ingrese Codigo:";
			cin>>p_estudiante->codigo;
			cin.ignore();
			
			cout<<"Ingrese Nombres:";
			getline(cin,nombre);
			strcpy(p_estudiante->nombre,nombre.c_str());

			cout<<"Ingrese Apellidos:";
			getline(cin,apellido);
			strcpy(p_estudiante->apellido,apellido.c_str());

			cout<<"Ingrese direccion:";
			getline(cin,direccion);
			strcpy(p_estudiante->direccion,direccion.c_str());
			
			cout<<"Ingrese Telefono:";
			cin>>p_estudiante->telefono;
			cin.ignore();

			delete [] p_estudiante->nombre;
			delete [] p_estudiante->apellido;
			delete [] p_estudiante->direccion;
			fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		fclose(archivo);
	leer();
	
}

void eliminar(){

	int cod=0, id;

	FILE *archivo= fopen(nombre_archivo,"rb");
	FILE *temp=	fopen(temporal,"wb");
		if(!archivo)
			archivo=fopen(nombre_archivo,"wb");
	Estudiante estudiante, *p_estudiante=&estudiante;
	consultar();
	cout<<"digite el codigo a eliminar/ingrese 0 si no desea eliminar"<<endl;
	cin>>cod;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	do
	{
		if(p_estudiante->codigo!=cod){
			fwrite(&estudiante,sizeof(Estudiante),1,temp);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	} while (feof(archivo)==0);
	fclose(archivo);
	fclose(temp);
	remove(nombre_archivo);
	rename(temporal,nombre_archivo);
	cout<<"\nRegistro eliminado!!!!!!"<<endl;
	getch();
};


void consultar(){

	int id=0, cod;

	system("cls");
	FILE *archivo = fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo=fopen(nombre_archivo,"w+b");
	}
	
	Estudiante estudiante, *p_estudiante=&estudiante;
	cout<<"Ingrese el codigo: "<<endl;
	cin>>cod;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
		do
		{
			if(p_estudiante->codigo==cod){
				cout<<"id"<<"|"<<"Codigo"<<"|"<<"Nombre"<<"|"<<"Apellidos"<<"|"<<"Direccion"<<"|"<<"Telefono"<<endl;
				cout<<"_________________________________________________________________________________________________"<<endl;
				cout<<id<<" | "<<p_estudiante->codigo<<" | "<<p_estudiante->nombre<<" | "<<p_estudiante->apellido<<" | "<<p_estudiante->direccion<<" | "<<p_estudiante->telefono<<endl;
			}
			fread(&estudiante,sizeof(Estudiante),1,archivo);
			id+=1;
		} while (feof(archivo)==0);
	
	fclose(archivo);
}

int consultar1(int &cod){
	
	FILE *archivo = fopen(nombre_archivo,"rb");
	Estudiante estudiante;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	do
			{	
			if(estudiante.codigo==cod){
				
				cout<<"Codigo ya existe!!!"<<endl;
				return 1;
				
			}			
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	} while (feof(archivo)==0);
		

}
