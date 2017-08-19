#include<cstdlib>
#include<iostream>
using namespace std;

struct Nodo{
	int dato;
	Nodo *siguiente;
};

struct NodoDoble{
	int dato;
	NodoDoble *anterior;
	NodoDoble *siguiente;
};

void insertaEnDoble(NodoDoble **n,int d){
	NodoDoble *nuevo = new NodoDoble();
	nuevo->dato = d;
	nuevo->siguiente = *n;
	nuevo->anterior = nullptr;
	if(*n != nullptr){
		(*n)->anterior = nuevo;
	}
	*n = nuevo;
}

void mostrarListaDoble(NodoDoble *n){
	for(n; n!=nullptr; n = n->siguiente){
		cout << n->dato<<endl;
	}
}

class ListaEnlazada{
	private :
		
       Nodo *cabecera;
       
       bool esVacia(){
          return cabecera == nullptr;
       }
       Nodo *crearNodo(int d){
     	  Nodo *nuevo = new Nodo;
     	  nuevo->dato = d;
     	  nuevo->siguiente = nullptr;
     	  return nuevo;
       }
       
	public :
        ListaEnlazada(){
     	    cabecera = nullptr;
     	} 
     	
		~ListaEnlazada(){
    		delete cabecera;
     	}    	
     	
     	void insertarAlInicio(int d){
     		Nodo *nuevo = crearNodo(d);
     		nuevo->siguiente = cabecera;
     		cabecera = nuevo;
     	}
     	
     	void insertarAlFinal(int d){
     		Nodo *nuevo = crearNodo(d);
     		Nodo *actual;
     		if(esVacia()){
     		   cabecera = nuevo;
     		   return;
     		}
     
     	    for(actual = cabecera; actual->siguiente !=nullptr; actual = actual->siguiente){}
     		actual->siguiente = nuevo;
     		return;
     	}
     	
     	void borrar(int clave){
     		Nodo *actual = cabecera;
     		Nodo *anterior;
     		
     		if(actual->dato == clave&&!esVacia()){
     			cabecera = actual->siguiente;
     			delete actual;
     			return;
			}
			
			for(actual; actual!=nullptr && actual->dato!=clave; actual= actual->siguiente){
				anterior = actual;
			}
			if(actual==nullptr)return;
			anterior->siguiente=actual->siguiente;
			delete actual;
		}
		
		bool buscar(int clave){
			Nodo *actual;
			for(actual = cabecera; actual!=nullptr; actual = actual->siguiente){
				if(actual->dato == clave) return true;
			}
			return false;
		}
		
		void mostrarLista(){
			for(Nodo * actual=cabecera;actual!=nullptr;actual=actual->siguiente){
				std::cout <<"Dato: "<<actual->dato<<"\n";
			}
		}
		/*Inserta un nodo entre dos nodos consecutivos cuyo valor entero difiere en signo.*/
		void insertaEnMedio(){
			Nodo *actual=cabecera,*nuevo;
			int valor = 0;
			if(actual->siguiente==nullptr || esVacia())return;
			for(actual; actual->siguiente!=nullptr; actual=actual->siguiente ){
				if((actual->dato <=0 && actual->siguiente->dato>=0) || (actual->dato >=0 && actual->siguiente->dato<=0)){
					valor = abs(actual->dato - actual->siguiente->dato);
					nuevo = crearNodo(valor);
					nuevo->siguiente = actual->siguiente;
					actual->siguiente = nuevo;
					actual = nuevo;
					//cout<<valor<<endl;
				}
			}
			
		}
		/*Recibe el puntero a una lista enlazada e inserta los datos de la misma en una doblemente enlazada,
		  en orden inverso.*/
		void insertaEnListaDoble(NodoDoble **n){
			for(Nodo *actual = cabecera; actual!=nullptr; actual = actual->siguiente){
				insertaEnDoble(n,actual->dato);
			}
		}
};




int main(int argc,char **argv){
	NodoDoble *nd = nullptr;
    ListaEnlazada lista;
	lista.insertarAlFinal(1);
	lista.insertarAlFinal(-1);
	lista.insertarAlFinal(2);
	lista.insertarAlFinal(3);
	lista.insertarAlFinal(-4);
	lista.insertarAlFinal(7);
	lista.insertarAlFinal(-8);
	lista.insertaEnListaDoble(&nd);
	mostrarListaDoble(nd);
	return 0;
}
