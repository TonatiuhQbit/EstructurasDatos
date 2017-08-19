#include<iostream>
template <typename S>
struct NodoC{
	S dato;
	NodoC *siguiente;
};

template <class T>
class ListaCircular{
	private :
		NodoC<T> *cabecera;
		int tam;
		NodoC<T> *creaNodo(T d){
			NodoC<T> *nuevo = new NodoC<T>;
			nuevo->dato = d;
			tam++;
			return nuevo;
		}
		bool esVacia(){
			return cabecera == nullptr;
		}
	public :
		ListaCircular(){
			cabecera = nullptr;
			tam = 0;
		}
		~ListaCircular(){
			delete cabecera;
		}
		void insertar(T d){
			NodoC<T> *nuevo = creaNodo(d);
			if(esVacia()){
				cabecera = nuevo;
				nuevo->siguiente = nuevo;
			}
			nuevo->siguiente = cabecera->siguiente;
			cabecera->siguiente = nuevo;
			tam++;
		}
		
		bool buscar(T d){
			if(esVacia())return false;
			NodoC<T> *primero = cabecera->siguiente;
			do{
				if(primero->dato == d) return true;
				primero = primero->siguiente; 
			}while(primero!=cabecera->siguiente);
			return false;
		}
		/*Falta implementar*/
		void eliminar(){
			
		}
		
		void imprimir(){
			if(esVacia())return;
			NodoC<T> *primero = cabecera->siguiente;
			do{
				std::cout << primero->dato <<"\n";
				primero = primero->siguiente; 
			}while(primero!=cabecera->siguiente);			
		}
		
		int size(){
			return tam;
		}
};
