/*  
    Aritmetica.cpp
    Autor: Paulina Ugalde Carreño 
    Fecha: 19/10/2020
    Programa: Implemente la estructura de pilas para que acepte una frase (expresión aritmética) 
    en  notación de infija la convierta a postfija y la evalue, debera poder utilizar como operandos
    los digitos de 0 al 9 y los operadores; suma (+) resta (-), multiplicación (*), división (/), 
    potencia (^), así como el uso de paréntesis para modificar la jerarquía de las operaciones.
*/

#include "Aritmetica.hpp"
#include<iostream>
#include<string.h>
#include<math.h>
#include<cstdlib>

using namespace std;


int main(){
    Nodo *pila=NULL;                       //La pila se encuentra vacía
    string entrada="", aux="", salida="";  //Strings donde almacenaremos nuestras funciones in y post
    int i, k=0, j=0, l=0, prioridadP, prioridadE, op1=0, op2=0, res=0, resultado=0;

    cout << "\nIngresa una operacion: "; getline(cin, entrada);
    cout<<"Notacion infija: "<<entrada<<endl;
    
    //Recorremos nuestra expresion infija para formar nuestra expresion postfija
    for(i=0; i<entrada.length(); i++){ //(3*4)/(3+1) infija  *^+-/(
        if(entrada[i]>='0' & entrada[i]<='9')   //Si es un numero, que se guarde en nuestro string
            aux=aux+entrada[i];
        else{
            if(pila==NULL){                     //Si la pila está vacía se agrega automaticamente el operador a la pila
                agregarPila(pila, entrada[i]);  
                prioridadP = prioridadPila(entrada[i]);
            }else{  //Si la pila no esta vacia, tenemos que ir comparando prioridades
                prioridadE = prioridadExpresion(entrada[i]);
                if(entrada[i] == ')'){  //Se sacaban hasta encontrar un paréntesis izquierdo
                    do{
                        sacarPila(pila, entrada[i]);
                        aux = aux + entrada[i];
                    }while(entrada[i] != '(');
                }else if(prioridadE>prioridadP){ //Si la prioridad de la expresion es mayor que la de la pila, se agregan los elementos a la pila
                    agregarPila(pila, entrada[i]);
                    prioridadP = prioridadPila(entrada[i]);
                }else if(prioridadE<=prioridadP){ //Si es menor o igual, se saca un elemento de la pila, se concatena y se agrega a la pila el nuevo elemento
                    sacarPila(pila, entrada[k]);
                    aux = aux + entrada[k];
                    agregarPila(pila, entrada[i]);
                }
            }
        }
    }

    //Sacamos los elementos restantes de la pila y los concatenamos a nuestro string
    while(pila!=NULL){ 
        sacarPila(pila, entrada[j]);
        aux = aux + entrada[j];
    }

    //Eliminar elemento ( de la cadena 
    for(i=0; i<aux.length(); i++){
        if(aux[i] != '('){
            salida = salida + aux[i];
        }
    }

    cout<<"Notacion Postfija: "<<salida<<endl;

    //Evaluar la funcion postfija
    pila=NULL;
    // 0123456789  meten a la pila +*/ sacan 
    for(i=0; i<salida.length(); i++){  
        if(salida[i]>='0' & salida[i]<='9'){ //Si es numero se agrega a la pila
            agregarPila(pila, salida[i]);
        }else{                               //Sino, lo sacamos
            sacarPila(pila, salida[k]);      //Ocupamos op2 y op1 para ir haciendo las operaciones entre los numeros
            op2 = salida[k]; 
            sacarPila(pila, salida[l]);     
            op1 = salida[l]; 

            switch (salida[i]){              //En el caso de tener cualquiera de estos operadores, se realiza la operacion correspondiente
                case '^' : res = pow((op1-48),(op2-48)); break;
                case '/' : res = (op1-48)/(op2-48); break;
                case '*' : res = (op1-48)*(op2-48); break;
                case '+' : res = (op1-48)+(op2-48); break;
                case '-' : res = (op1-48)-(op2-48); break;
            }
            //NOTA: es importante señalar que como nuestra pila guarda los caracteres char, trabajamos las operaciones en
            //      codigo ASCII y es por ello que hacemos uso de la suma y la resta (dependiendo del caso) del 48, que es
            //      el 0 en este codigo
            agregarPila(pila, (res+48));
        }
    }

    //Sacamos los elementos restantes de la pila
    while(pila !=NULL){
        sacarPila(pila, salida[l]);
        resultado = salida[l]-48;
    }

    //Imprimimos el resultado
    cout<<"Resultado: "<<resultado<<endl;
    return 0;
}

int prioridadPila(char opdor){
  switch (opdor){
	case '(': return 0; case '^': return 3;	case '/': return 2;
	case '*': return 2; case '+': return 1;	case '-': return 1;
  }
  return 0;
}

int prioridadExpresion(char opdor){
  switch (opdor){
	case '(': return 5; 	case '^': return 4;	case '/': return 2;
	case '*': return 2; 	case '+': return 1;	case '-': return 1;
  }
 return 0;
}

void agregarPila(Nodo *&pila, char dato){
    Nodo *nod = new Nodo(); //Creamos un nodo
    nod->operacion = dato;  //Le ponemos como operacion el dato que le mandamos
    nod->sig = pila;        //Recorremos la posicion del siguiente nodo
    pila = nod;             //La pila apuntara al nodo
}

void sacarPila(Nodo *&pila, char &dato){
    Nodo *aux = pila;        //Creamos una variable auxiliar
    dato = aux->operacion;   //Tomar el valor de operacion
    pila = aux->sig;         //Que pila nos señale al siguiente nodo
    delete aux;              //Eliminar memoria
}