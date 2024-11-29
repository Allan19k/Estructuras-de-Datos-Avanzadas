/*
  Implementacion de un ABB con arreglos
  Estructuras de datos avanzadas 
  Nombre y Matricula: Allan Hall Solorio-358909
  Fecha de elaboracion: 10/02/24
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

const int MAX_TAMANO = 100;

struct Nodo{
    int dato;
    int izq;
    int der;
    int padre;
};

Nodo arbol[MAX_TAMANO];
int raiz = -1;
int tamano = 0;

void menu(); 
void insertarNodo(int, int); 
void mostrarArbol(int, int);
bool busqueda(int, int);
void eliminar(int, int);
int minimo(int);
int maximo(int);

void insertarDesdeArchivo(const char *nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error abriendo el archivo." << endl;
        return;
    }

    int dato;
    while (archivo >> dato) {
        insertarNodo(dato, -1);
    }

    archivo.close();
}

int main() {
    insertarDesdeArchivo("datos100.txt");
    menu();
    getch();
    return 0;
}

void menu(){
    int dato, opc, contador=0;
    
    do{
        cout << "\t.:ABB con arreglos:." << endl;
        cout << "1. Insertar un nuevo nodo" << endl;
        cout << "2. Mostrar el arbol completo" << endl;
        cout << "3. Buscar un elemento en el arbol" << endl;
        cout << "4. Eliminar un nodo del arbol" << endl;
        cout << "5. Obtener el minimo" << endl;
        cout << "6. Obtener el maximo" << endl;
        cout << "7. Salir" << endl;
        cout << "Opcion: ";
        cin >> opc;
        
        switch(opc){
            case 1: cout << "\nDigite un numero: "; 
                    cin >> dato;
                    insertarNodo(dato, -1);
                    cout << "\n";
                    system("pause");
                    break;
            case 2: cout << "\nMostrando el arbol completo:\n\n";
                    mostrarArbol(raiz, contador);
                    cout << "\n";
                    system("pause");
                    break;
            case 3: cout << "\nDigite el elemento a buscar: ";
                    cin >> dato;
                    if(busqueda(raiz, dato)){
                        cout << "\nElemento " << dato << " ha sido encontrado en el arbol";
                    }
                    else{
                        cout << "\nElemento no encontrado\n";
                    }
                    cout << "\n";
                    system("pause");
                    break;
            case 4: cout << "\nDigite un numero a eliminar: ";
                    cin >> dato;
                    eliminar(raiz, dato);
                    cout << "\n";
                    system("pause");
                    break;
            case 5: 
                {
                    int min = minimo(raiz);
                    if(min != -1){
                        cout << "\nEl minimo es: " << min;
                    } else {
                        cout << "\nEl arbol esta vacio";
                    }
                    cout << "\n";
                    system("pause");
                    break;
                }
            case 6:
                {
                    int max = maximo(raiz);
                    if(max != -1){
                        cout << "\nEl maximo es: " << max;
                    } else {
                        cout << "\nEl arbol esta vacio";
                    }
                    cout << "\n";
                    system("pause");
                    break;
                }
        }
        system("cls");
    } while(opc != 7);
}

void insertarNodo(int dato, int padre) {
    if (tamano == MAX_TAMANO) {
        cout << "Arbol lleno, no se puede insertar mas elementos." << endl;
        return;
    }

    if (raiz == -1) {
        raiz = 0;
        arbol[raiz].dato = dato;
        arbol[raiz].izq = -1;
        arbol[raiz].der = -1;
        arbol[raiz].padre = padre;
        tamano++;
        return;
    }

    int nodoActual = raiz;
    while (true) {
        if (dato <= arbol[nodoActual].dato) {
            if (arbol[nodoActual].izq == -1) {
                arbol[nodoActual].izq = tamano;
                arbol[tamano].dato = dato;
                arbol[tamano].izq = -1;
                arbol[tamano].der = -1;
                arbol[tamano].padre = nodoActual;
                tamano++;
                break;
            } else {
                nodoActual = arbol[nodoActual].izq;
            }
        } else {
            if (arbol[nodoActual].der == -1) {
                arbol[nodoActual].der = tamano;
                arbol[tamano].dato = dato;
                arbol[tamano].izq = -1;
                arbol[tamano].der = -1;
                arbol[tamano].padre = nodoActual;
                tamano++;
                break;
            } else {
                nodoActual = arbol[nodoActual].der;
            }
        }
    }
}

void mostrarArbol(int nodoActual, int nivel) {
    if (nodoActual != -1) {
        mostrarArbol(arbol[nodoActual].der, nivel + 1);
        for (int i = 0; i < nivel; i++)
            cout << "    ";
        cout << arbol[nodoActual].dato << endl;
        mostrarArbol(arbol[nodoActual].izq, nivel + 1);
    }
}

bool busqueda(int nodoActual, int valor) {
    if (nodoActual == -1)
        return false;
    if (arbol[nodoActual].dato == valor)
        return true;
    else if (valor < arbol[nodoActual].dato)
        return busqueda(arbol[nodoActual].izq, valor);
    else
        return busqueda(arbol[nodoActual].der, valor);
}

void eliminar(int nodoActual, int valor) {
    if (nodoActual == -1) {
        cout << "El valor a eliminar no se encuentra en el arbol." << endl;
        return;
    }

    if (valor < arbol[nodoActual].dato) {
        eliminar(arbol[nodoActual].izq, valor);
    } else if (valor > arbol[nodoActual].dato) {
        eliminar(arbol[nodoActual].der, valor);
    } else {
        // Caso 1: El nodo a eliminar no tiene hijos
        if (arbol[nodoActual].izq == -1 && arbol[nodoActual].der == -1) {
            if (nodoActual == raiz) {
                raiz = -1;
            } else {
                if (arbol[arbol[nodoActual].padre].izq == nodoActual) {
                    arbol[arbol[nodoActual].padre].izq = -1;
                } else {
                    arbol[arbol[nodoActual].padre].der = -1;
                }
            }
            tamano--;
        }
        // Caso 2: El nodo a eliminar tiene un hijo izquierdo
        else if (arbol[nodoActual].der == -1) {
            if (nodoActual == raiz) {
                raiz = arbol[nodoActual].izq;
            } else {
                if (arbol[arbol[nodoActual].padre].izq == nodoActual) {
                    arbol[arbol[nodoActual].padre].izq = arbol[nodoActual].izq;
                } else {
                    arbol[arbol[nodoActual].padre].der = arbol[nodoActual].izq;
                }
            }
            arbol[arbol[nodoActual].izq].padre = arbol[nodoActual].padre;
            tamano--;
        }
        // Caso 3: El nodo a eliminar tiene un hijo derecho
        else if (arbol[nodoActual].izq == -1) {
            if (nodoActual == raiz) {
                raiz = arbol[nodoActual].der;
            } else {
                if (arbol[arbol[nodoActual].padre].izq == nodoActual) {
                    arbol[arbol[nodoActual].padre].izq = arbol[nodoActual].der;
                } else {
                    arbol[arbol[nodoActual].padre].der = arbol[nodoActual].der;
                }
            }
            arbol[arbol[nodoActual].der].padre = arbol[nodoActual].padre;
            tamano--;
        }
        // Caso 4: El nodo a eliminar tiene dos hijos
        else {
            int sucesor = arbol[nodoActual].der;
            while (arbol[sucesor].izq != -1) {
                sucesor = arbol[sucesor].izq;
            }
            arbol[nodoActual].dato = arbol[sucesor].dato;
            eliminar(arbol[nodoActual].der, arbol[sucesor].dato);
        }
    }
}

int minimo(int nodoActual) {
    if (nodoActual == -1)
        return -1;
    while (arbol[nodoActual].izq != -1)
        nodoActual = arbol[nodoActual].izq;
    return arbol[nodoActual].dato;
}

int maximo(int nodoActual) {
    if (nodoActual == -1)
        return -1;
    while (arbol[nodoActual].der != -1)
        nodoActual = arbol[nodoActual].der;
    return arbol[nodoActual].dato;
}
