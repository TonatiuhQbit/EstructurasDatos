#include <iostream>
template <typename U>
struct Nodo{
	U dato;
	struct Nodo *siguiente;
};

template <class T>
class Pila{
	private :
		Nodo<T> *cabecera;
		int tamanio;
		bool esVacia(){
			return cabecera == nullptr;
		}
	public :
		Pila(){
			cabecera = nullptr;
			tamanio = 0;
		}
		~Pila(){
			delete cabecera;
		}
		void push(T dato){
			Nodo<T> *nuevo= new Nodo<T>;
			nuevo->dato = dato;
			nuevo->siguiente = cabecera;
			cabecera = nuevo;
			tamanio++;
		}
		T pop(){
			if(esVacia()){
				return 0;
			}
			T aux = cabecera->dato;
			cabecera = cabecera->siguiente;
			tamanio--;
			return aux;
		}
		void vaciarPila(){
			cabecera = nullptr;
		}
		void mostrarPila(){
			Nodo<T> *actual=nullptr;
			
			for(actual=cabecera;actual!=nullptr;actual=actual->siguiente){
				std::cout <<actual->dato <<"\n";
			}
		}
		T tope(){
			if(!esVacia()){
				return cabecera->dato;
			}
		}
		int size(){
			return tamanio;
		}
};
