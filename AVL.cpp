/*
  Balanceo de arboles binarios 
  Estructuras de datos avanzadas 
  Nombre y Matricula: Allan Hall Solorio-358909 y Jorge Alejandro Beltran Rosales-348635
  Fecha de elaboracion: 17/02/24
*/

#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std; 

struct Nodo{
	int dato;
	Nodo *der;
	Nodo *izq;
	Nodo *padre;
};
// Prototipos de las funciones 
void menu(); 
Nodo *crearNodo(int, Nodo *);
void insertarNodo(Nodo *&, int,Nodo * );
void mostrarArbol(Nodo *, int);
bool busqueda(Nodo *, int, int&, int&);
void eliminar(Nodo *, int);
void eliminarNodo(Nodo *);
void reemplazar(Nodo *, Nodo *);
void destruirNodo(Nodo *);
Nodo *minimo(Nodo *);
Nodo *maximo(Nodo *);
int obtenerAltura(Nodo *);
int factorEquilibrio(Nodo *);

Nodo *arbol= NULL; 


int main(){
	
	menu();
	getch();
	
	return 0;
}

//Funcion del menu
void menu(){
	int dato,opc, contador=0;
	
	do{
		cout<<"\t.:Balanceo de arboles binarios:."<<endl;
		cout<<"1. Insertar un nuevo nodo"<<endl;
		cout<<"2. Mostrar el arbol completo"<<endl;
		cout<<"3. Buscar un elemento en el arbol"<<endl;
		cout<<"4. Eliminar un nodo del arbol"<<endl;
		cout<<"5. Obtener el minimo"<<endl;
		cout<<"6. Obtener el maximo"<<endl;
		cout<<"7. Obtener la altura del arbol"<<endl;
		cout<<"8. Obtener el factor de equilibrio del arbol"<<endl;
		cout<<"9. Salir"<<endl;
		cout<<"Opcion: "; cin>>opc;
		
		switch(opc){
			case 1: cout<<"\nDigite el nodo a insertar: "; 
			        cin>>dato;
			        insertarNodo(arbol,dato, NULL); //Insertar un nuevo nodo
			        cout<<"\n";
			        system("pause");
			        break;
			        
	        case 2: cout<<"\nMostrando el arbol completo...\n\n";
	                mostrarArbol(arbol, contador);
	                cout<<"\n";
	                system("pause");
	                break;
	                
	        case 3: {
				    int alturaNodo= 0;
				    int feNodo= 0;
				    
				    cout<<"\nDigite el nodo a buscar: "; cin>>dato;
	                if(busqueda(arbol,dato, alturaNodo, feNodo)){
	                	cout<<"\nNodo "<<dato<<" a sido encontrado en el arbol"<<endl;;
	                	cout<<"\nSu altura es de: "<<alturaNodo<<endl;
	                	cout<<"\nY su factor de equilibro es de: "<<feNodo<<endl;
					}
					else{
						cout<<"\nElemento no encontrado\n";
					}
					cout<<"\n";
					system("pause");
					break;
			        }
					
			case 4: cout<<"\nDigite un nodo a eliminar: ";
			        cin>>dato;
			        eliminar(arbol, dato);
			        cout<<"\n";
			        system("pause");
			        break;
			        
			case 5: {
			        Nodo *min = minimo(arbol);
			        if(min!=NULL){
			        	cout<<"\nEl minimo es: "<<min->dato;
					}else{
						cout<<"\nEl arbol esta vacio";
						cout<<"\n";
					}
					cout<<"\n";
					system("pause");
					break;
				    }
					
			case 6: {
			        Nodo *max = maximo(arbol);
			        if(max!=NULL){
			        	cout<<"\nEl maximo es: "<<max->dato;
					}else{
						cout<<"\nEl arbol esta vacio";
						cout<<"\n";
					}
					cout<<"\n";
					system("pause");
					break;
				    }
					
			case 7: {
			        int altura = obtenerAltura(arbol);
			        if(arbol!=NULL){
			           cout << "\nLa altura del arbol es: " <<altura<<endl;
                       cout << "\n";	
					}else{
						cout<<"\nEl arbol esta vacio"<<endl;
						cout<<"\n";
					}
                    system("pause");
                    break;
				    }
				    
			case 8: {
			        int fe= factorEquilibrio(arbol);
			        if(arbol!=NULL){
			          cout<<"\nEl Factor de Equilibrio del arbol es: "<<fe<<endl;
				      cout<<"\n";	
					}else{
						cout<<"\nEl arbol esta vacio"<<endl;
						cout<<"\n";
					}
				    system("pause");
				    break;
				    }
		}
		system("cls");
	}while(opc!=9);
}

// Funcion para crear un nuevo nodo
Nodo *crearNodo(int n, Nodo *padre){
	Nodo *nuevo_nodo= new Nodo();
	
	nuevo_nodo->dato=n;
	nuevo_nodo->der= NULL;
	nuevo_nodo->izq=NULL;
	nuevo_nodo->padre=padre;
	
	return nuevo_nodo; 
}

void insertarNodo(Nodo *&arbol, int n, Nodo *padre) {
    if (arbol == NULL) {
        Nodo *nuevo_nodo = crearNodo(n, padre);
        arbol = nuevo_nodo;
    } else {
        int valorRaiz = arbol->dato;
        if (n < valorRaiz) {
            insertarNodo(arbol->izq, n, arbol);
        } else {
            insertarNodo(arbol->der, n, arbol);
        }

        // Después de la inserción, verificar y ajustar el equilibrio
        int fe = factorEquilibrio(arbol);

        // Caso de rotación simple a la izquierda
        if (fe < -1 && n < arbol->izq->dato) {
            // Rotación simple a la derecha
            Nodo *nuevoArbol = arbol->izq;
            arbol->izq = nuevoArbol->der;
            nuevoArbol->der = arbol;
            arbol = nuevoArbol;
        }

        // Caso de rotación simple a la derecha
        if (fe > 1 && n > arbol->der->dato) {
            // Rotación simple a la izquierda
            Nodo *nuevoArbol = arbol->der;
            arbol->der = nuevoArbol->izq;
            nuevoArbol->izq = arbol;
            arbol = nuevoArbol;
        }

        // Caso de rotación doble a la izquierda-derecha
        if (fe < -1 && n > arbol->izq->dato) {
            // Rotación simple a la izquierda en el subárbol izquierdo
            Nodo *subArbolIzq = arbol->izq;
            arbol->izq = subArbolIzq->der;
            subArbolIzq->der = arbol->izq->izq;
            arbol->izq->izq = subArbolIzq;

            // Rotación simple a la derecha en el árbol principal
            Nodo *nuevoArbol = arbol->izq;
            arbol->izq = nuevoArbol->der;
            nuevoArbol->der = arbol;
            arbol = nuevoArbol;
        }

        // Caso de rotación doble a la derecha-izquierda
        if (fe > 1 && n < arbol->der->dato) {
            // Rotación simple a la derecha en el subárbol derecho
            Nodo *subArbolDer = arbol->der;
            arbol->der = subArbolDer->izq;
            subArbolDer->izq = arbol->der->der;
            arbol->der->der = subArbolDer;

            // Rotación simple a la izquierda en el árbol principal
            Nodo *nuevoArbol = arbol->der;
            arbol->der = nuevoArbol->izq;
            nuevoArbol->izq = arbol;
            arbol = nuevoArbol;
        }
    }
}


// Funcion para mostrar el arbol completo 
void mostrarArbol(Nodo *arbol, int cont){
	if(arbol==NULL){ //Si el arbol esta vacio
	      return;
		
	}
	else{
		mostrarArbol(arbol->der, cont+1);
		for(int i=0; i<cont; i++){
			cout<<"     ";
		}
		cout<<arbol->dato<<endl;
		mostrarArbol(arbol->izq, cont+1);
	}
}

// Funcion para buscar un elemento en el arbol
bool busqueda(Nodo *arbol, int n, int &alturaNodo, int &feNodo){
	if(arbol==NULL){
		return false;
	}
	else if(arbol->dato==n){ // si el nodo es igual al elemento
		alturaNodo = obtenerAltura(arbol);
        feNodo = factorEquilibrio(arbol);
		return true;
	}
	else if(n<arbol->dato){
		return busqueda(arbol->izq,n, alturaNodo, feNodo);
	}
	else{
		return busqueda(arbol->der,n, alturaNodo, feNodo);
	}
}

// Eliminar un nodo del arbol
void eliminar(Nodo *arbol, int n){
	if(arbol==NULL){
		return; // no haces nada
	}
	else if(n < arbol->dato){ //si el valor es menor 
		eliminar(arbol->izq, n); // busca por la izq
	}
	else if(n> arbol->dato){ // si es mayor
		eliminar(arbol->der, n); // busca por la derecha
	}
	else{ // si ya encontraste el valor
		eliminarNodo(arbol);
	}
}

// Funcion para reemplazar 2 nodos 
void reemplazar(Nodo *arbol, Nodo *nuevoNodo){
	if(arbol->padre){ // arbol->padre hay que asignarle su nuevo hijo
		if(arbol->dato == arbol->padre->izq->dato){
			arbol->padre->izq= nuevoNodo; 
		}
		else if(arbol->dato== arbol->padre->der->dato){
			arbol->padre->der= nuevoNodo;
		}
	}
	if(nuevoNodo){ // Procedemos a asignarle su nuevo padre
	   nuevoNodo->padre= arbol->padre; 
	}
}

// Funcion para destruir nodo
void destruirNodo(Nodo *nodo){
	nodo->izq= NULL;
	nodo->der= NULL;
	
	delete nodo;
}

// Funcion para eliminar el nodo encontrado 
void eliminarNodo(Nodo *nodoEliminar){
	if(nodoEliminar->izq && nodoEliminar->der){ // si el nodo tiene hijo izq y derecho
		Nodo *menor= minimo(nodoEliminar->der);
		nodoEliminar->dato= menor->dato;
		eliminarNodo(menor);
	}
    else if(nodoEliminar->izq){ // Si tiene hijo izq
    	reemplazar(nodoEliminar, nodoEliminar->izq);
    	destruirNodo(nodoEliminar);
	}
	else if(nodoEliminar->der){ // Si tiene hijo derecho
		reemplazar(nodoEliminar, nodoEliminar->der);
		destruirNodo(nodoEliminar);
	}
	else{ // No tiene hijos
		reemplazar(nodoEliminar, NULL);
		destruirNodo(nodoEliminar);
	}
}

// Funcion para consultar el minimo (el nodo que esta mas a la izq)
Nodo *minimo(Nodo *arbol){
	if(arbol==NULL){
		return NULL; // retornar null
	}
	if(arbol->izq){ // si tiene hijo izq
		return minimo(arbol->izq); // buscamos la parte mas izq posible
	}else{ // si no tiene hijo izq
		return arbol; // retornamos el mismo nodo
	}
}

// Funcion para determinar el maximo (el nodo que esta mas a la derecha)
Nodo *maximo(Nodo *arbol){
	if(arbol==NULL){
		return NULL;
	}
	if(arbol->der){
		return maximo(arbol->der);
	}else{
		return arbol;
	}
}

// Funcion para obtener la altura del arbol
int obtenerAltura(Nodo *nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        // Obtener la altura de los subárboles izquierdo y derecho
        int alturaIzq = obtenerAltura(nodo->izq);
        int alturaDer = obtenerAltura(nodo->der);

        // La altura del nodo es el máximo entre las alturas de los subárboles más uno
        return max(alturaIzq, alturaDer)+1 ;
    }
}

// Funcion para obtener el Factor de Equilibrio del arbol
int factorEquilibrio(Nodo *nodo){
	if(nodo==NULL){
		return 0;
	}else{
	     return obtenerAltura(nodo->der) - obtenerAltura(nodo->izq);		
	}
	    
}