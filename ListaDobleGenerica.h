#include <iostream>
template <typename S>
struct Nodo{
	S dato;
	struct Nodo *anterior;
	struct Nodo *siguiente;	
};

template <class T>
class ListaDoble{
	private :
		Nodo<T> *cabecera;
		int tamanio;
		Nodo<T> *crearNodo(T d){
			Nodo<T> *nuevo = new Nodo<T>;
			nuevo->dato = d;
			nuevo->anterior = nuevo->siguiente = nullptr;
			return nuevo;
		}
		bool esVacia(){
          return cabecera == nullptr;
        }
	public :
		ListaDoble(){
			cabecera=nullptr;
			tamanio = 0;
		}
		~ListaDoble(){
			delete cabecera;
		}
		void insertarAlInicio(T d){
			Nodo<T> *nuevo = crearNodo(d);
			nuevo->siguiente = cabecera;
			if(!esVacia()){
				cabecera->anterior = nuevo;	
			}
			cabecera = nuevo;
			tamanio++;
		}
		
		void insertarAlFinal(T d){
			Nodo<T> *nuevo = crearNodo(d);
			Nodo<T> *actual;
			if(esVacia()){
				cabecera = nuevo;
				return;
			}
			for(actual = cabecera; actual->siguiente!=nullptr; actual = actual->siguiente){}
			actual->siguiente = nuevo;
			nuevo->anterior = actual;
			tamanio++;
			return;
		}
		
		void imprimir(){
			Nodo<T> *actual;
			for(actual = cabecera; actual!=nullptr; actual = actual->siguiente){
				std::cout << actual->dato <<"\n";
			}
		}
		
		void borrar(T clave){
			Nodo<T> *actual=cabecera;
			if(actual->dato == clave){
				cabecera = actual->siguiente;
				delete actual;
				tamanio--;
				return;
			}
			for(actual; actual!=nullptr && actual->dato!=clave; actual = actual->siguiente){}
			if(actual==nullptr)return;
			if(actual->siguiente != nullptr){
				actual->anterior->siguiente = actual->siguiente;
				actual->siguiente->anterior = actual->anterior;
				delete actual;
				tamanio--;
				return;
			}
		    actual->anterior->siguiente = actual->siguiente;	
			delete actual;
			tamanio--;
			return;
		}
		
		int size(){
			return tamanio;
		}
};
