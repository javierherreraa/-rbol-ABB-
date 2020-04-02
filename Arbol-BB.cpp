#include <iostream>
#include <stdlib.h>

using namespace std;

//NODO
struct nodo {
	int dato;
	nodo *izq;
	nodo *der;
	nodo *padre;

};
nodo *arbol = NULL;

//PROTOTIPOS 
void menu();
 

void insertarNodo(nodo *&, int,nodo *);		
void mostrarArbol(nodo*, int);
bool busqueda(nodo *, int);

void preOrden(nodo *);
void inOrden(nodo *);
void postOrden(nodo *);

void eliminar(nodo *, int);		
void eliminarNodo(nodo *);
nodo *crearNodo(int, nodo *);	
nodo *minimo(nodo *);	
void reemplazar(nodo *, nodo *);	
void destruir(nodo *);		


//MAIN
int main() {
	
	menu();

	system("pause");
	return 0;
}

void menu() {
	int dato, opcion;
	int contador = 0;//para la raíz al imprimir = 0

	do
	{
		cout << "\n\t\tMENU" << endl;
		cout << "\n\t1. Insertar nuevo nodo";
		cout << "\n\t2. Mostrar Arbol completo";
		cout << "\n\t3. Buscar elemento en el arbol";
		cout << "\n\t4. Recorrido PreOrden";
		cout << "\n\t5. Recorrido InOrden";
		cout << "\n\t6. Recorrido en Postorden";
		cout << "\n\t7. Eliminar Nodo";
		cout << "\n\t8. Salir";
		cout << "\n\tElija opcion: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			cout << "\n\tInserte un numero: ";
			cin >> dato;
			insertarNodo(arbol, dato, NULL);
			cout << "\n";
			system("pause"); break;
		case 2:
			cout << "\n\tArbol completo: \n\n";
			mostrarArbol(arbol, contador);
			cout << "\n";
			system("pause");
			break;

		case 3:
			cout << "\n\tInserte el elemento a buscar: ";
			cin >> dato;
			if (busqueda(arbol, dato) == true) {
				cout << "\n\tElemento " << dato << " encontrado en el arbol" << endl;
			}
			else {
				cout << "\n\tElemento no encontrado" << endl;
			}
			cout << "\n";
			system("pause");
			break;


		case 4:
			cout << "\n\tRecorrido en PreOrden";
			preOrden(arbol);
			cout << "\n\n";
			system("pause");
			break;
		case 5:
			cout << "\n\tRecorrido en InOrden";
			inOrden(arbol);
			cout << "\n\n";
			system("pause");
			break;
		case 6:
			cout << "\n\tRecorrido en PostOrden";
			postOrden(arbol);
			cout << "\n\n";
			system("pause");
			break;

		case 7:cout << "\n\tDigite el nodo a eliminar: ";
			cin >> dato;
			eliminar(arbol, dato);
			cout << "\n";
			system("pause");
			break;
		}
		system("cls");
	} while (opcion != 8);

}

//FUNCIONES


//---------Funcíón Insertar Nodo---------
void insertarNodo(nodo *&arbol, int n,nodo *padre){
	if (arbol == NULL){
		nodo *nuevoNodo = crearNodo(n,padre);
		arbol = nuevoNodo;
	}
	else{//si el arbol tiene un nodo o más
		int valorRaiz = arbol->dato;
		if (n<valorRaiz) {
			insertarNodo(arbol->izq, n,arbol);//hacia la izq
		}
		else{
			insertarNodo(arbol->der, n,arbol);
		}
	}
}

//---------Función Mostrar Arbol---------
void mostrarArbol(nodo*arbol, int cont) {
	//cont variable, para espacios en impresión de los nodos
	if (arbol == NULL) {
		return;
	}
	else {
		mostrarArbol(arbol->der, cont + 1);
		for (int i = 0; i < cont; i++) {
			cout << "   ";
		}
			
		cout << arbol->dato << endl;
		mostrarArbol(arbol->izq, cont + 1);
	}
}

//---------Función Búsqueda--------
bool busqueda(nodo *arbol, int n) {
	if (arbol == NULL) {
		return false;
	}
	else if (arbol->dato==n) {//si el nodo es == al elemento 
		return true;
	}
	else if (n<arbol->dato) {
		busqueda(arbol->izq, n);
	}
	else {
		return busqueda(arbol->der, n);
	}

}

/****************Funciones de recorrido --> en Profundidad******************
------------Recorrido en PreOrden*/
void preOrden(nodo *arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		cout<< arbol->dato << " - ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}

}

// --------- Recorrido InOrden--------
void inOrden(nodo *arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		inOrden(arbol->izq);
		cout << arbol->dato<<" - ";
		inOrden(arbol->der);
	}
}

// --------- Recorrido postOrden--------
void postOrden(nodo *arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		postOrden(arbol->izq);
		postOrden(arbol->der);
		cout << arbol->dato << " - ";
	}
}



/*********************ELIMINAR*****************
*/

nodo *crearNodo(int n, nodo *padre) {	
	nodo *nuevoNodo = new nodo();

	nuevoNodo->dato = n;
	nuevoNodo->der = NULL;
	nuevoNodo->izq = NULL;
	nuevoNodo->padre = padre;

	return nuevoNodo;
}

void eliminar(nodo *arbol, int n)
{
	if (arbol == NULL) {
		return;
	}
	else if (n < arbol->dato) {//Dato a eliminar < valor del arbol actual
		eliminar(arbol->izq, n);//Busca por la izquierda
	}
	else if (n > arbol->dato) {
		eliminar(arbol->der, n);//Busca por la derecha
	}
	else {
		eliminarNodo(arbol);
		//arbol posición de nodo actual
	}
}

//Función para determinar el nodo más izquierdo (CASO ---> 2)
nodo *minimo(nodo *arbol) {
	if (arbol == NULL) {
		return NULL;
	}
	if (arbol->izq) {//Si tiene hijo izq, busca la parte más izq posible
		return minimo(arbol->izq);
	}
	else {
		return arbol;//No tiene hijo izq, retorna el mismo árbol
	}
}

//Función para reemplazar 2 nodos (CASO---> 3)
void reemplazar(nodo *arbol, nodo *nuevoNodo) {
	if (arbol->padre) {
		if (arbol->dato == arbol->padre->izq->dato) {
			arbol->padre->izq = nuevoNodo;
		}
		else if (arbol->dato == arbol->padre->der->dato) {
			arbol->padre->der = nuevoNodo;
		}
	}
	
	if (nuevoNodo) {
		nuevoNodo->padre = arbol->padre;//Su nuevo padre
	}

}

//Función para destruir un nodo		
void destruir(nodo *nodo) {
	nodo->izq = NULL;
	nodo->der = NULL;
	delete(nodo);
}


//Función para Eliminar el nodo encontrado 
void eliminarNodo(nodo *nodoEliminar) {
	if (nodoEliminar->izq && nodoEliminar->der) {
		nodo *menor = minimo(nodoEliminar->der);
		nodoEliminar->dato = menor->dato;
		eliminarNodo(menor);
	}
	else if (nodoEliminar->izq) {
		reemplazar(nodoEliminar, nodoEliminar->izq);
		destruir(nodoEliminar);
	}
	else if (nodoEliminar->der) {
		reemplazar(nodoEliminar, nodoEliminar->der);
		destruir(nodoEliminar);
	}
	else {//Caso de nodos Hojas  (CASO 1)
		reemplazar(nodoEliminar, NULL);
		destruir(nodoEliminar);
		 
	}
}
