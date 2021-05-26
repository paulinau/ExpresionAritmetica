/*  
    Aritmetica.hpp
    Autor: Paulina Ugalde Carreño 
    Fecha: 19/10/2020
*/

#ifndef ListaLigada_hpp
#define ListaLigada_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Nodo{
public:
    char operacion;  //Almacenamos datos de tipo char
    Nodo *sig;       //Apuntador al nodo siguiente
};

void agregarPila(Nodo *&, char);    //Metodo para agregar elementos a la pila
void sacarPila(Nodo *&, char&);     //Metodo para sacar elementos de la pila
int prioridadExpresion(char);       //Metodo para definir las prioridades de la expresion
int prioridadPila(char);            //Metodo para definir las prioridades de la pila

#endif /* Aritmetica_hpp */