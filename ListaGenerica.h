#include <iostream>
template <typename S>
 struct Nodo{
	S dato;
	struct Nodo *siguiente;
 };

 template<class T>
 class ListaEnlazada{
	private :
		
       Nodo<T> *cabecera;
       int tamanio;
       
       bool esVacia(){
          return cabecera == nullptr;
       }
       Nodo<T> *crearNodo(T d){
     	  Nodo<T> *nuevo = new Nodo<T>;
     	  nuevo->dato = d;
     	  nuevo->siguiente = nullptr;
     	  tamanio++;
     	  return nuevo;
       }
       
	public :
        ListaEnlazada(){
     	    cabecera = nullptr;
     	    tamanio = 0;
     	} 
     	
		~ListaEnlazada(){
    		delete cabecera;
     	}    	
     	
     	void insertarAlInicio(T d){
     		Nodo<T> *nuevo = crearNodo(d);
     		nuevo->siguiente = cabecera;
     		cabecera = nuevo;
     	}
     	
     	void insertarAlFinal(T d){
     		Nodo<T> *nuevo = crearNodo(d);
     		Nodo<T> *actual;
     		if(esVacia()){
     		   cabecera = nuevo;
     		   return;
     		}
     
     	    for(actual = cabecera; actual->siguiente !=nullptr; actual = actual->siguiente){}
     		actual->siguiente = nuevo;
     		return;
     	}
     	
     	void borrar(T clave){
     		Nodo<T> *actual = cabecera;
     		Nodo<T> *anterior;
     		
     		if(actual->dato == clave&&!esVacia()){
     			cabecera = actual->siguiente;
     			delete actual;
     			tamanio--;
     			return;
			}
			
			for(actual; actual!=nullptr && actual->dato!=clave; actual= actual->siguiente){
				anterior = actual;
			}
			if(actual==nullptr)return;
			anterior->siguiente=actual->siguiente;
			tamanio--;
			delete actual;
		}
		
		bool buscar(T clave){
			Nodo<T> *actual;
			for(actual = cabecera; actual!=nullptr; actual = actual->siguiente){
				if(actual->dato == clave) return true;
			}
			return false;
		}
		
		void mostrarLista(){
			for(Nodo<T> * actual=cabecera;actual!=nullptr;actual=actual->siguiente){
				std::cout <<"Dato: "<<actual->dato <<" Posicion: "<< actual->indice <<"\n";
			}
		}
		
		int size(){
			return tamanio;
		}
		
};
