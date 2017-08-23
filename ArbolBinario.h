#include<iostream>

template <typename S>
struct Nodo{
	S dato;
	struct Nodo *izquierda;
	struct Nodo *derecha;
};

template <class T>
class ArbolBinarioBusqueda{
	private :
		Nodo<T> *raiz;
		/*Regresa true en caso de que el árbol esté vacio.*/
		bool esVacio(){
			return raiz == nullptr;
		}
		/*Para recorrer un árbol binario cada nodo debe ser visitado una sóla vez.*/
		/*Visitas al hijo izquierdo, al padre y al hijo derecho.*/
		void recorridoEnOrden(Nodo<T> *r){
			if(r != nullptr){
				recorridoEnOrden(r->izquierda);
				std::cout << r->dato <<"\n";
				recorridoEnOrden(r->derecha);
			}
		}
		/*Visitas al padre, al hijo izquierdo y al hijo derecho.*/
		void recorridoEnPreOrden(Nodo<T> *r){
			if(r != nullptr){
				std::cout << r->dato <<"\n";
				recorridoEnOrden(r->izquierda);
				recorridoEnOrden(r->derecha);
			}
		}
		/*Visitas al hijo izquierdo, al hijo derecho y al padre.*/
		void recorridoEnPostOrden(Nodo<T> *r){
			if(r != nullptr){
				recorridoEnOrden(r->izquierda);
				recorridoEnOrden(r->derecha);
				std::cout << r->dato <<"\n";
			}
		}
		
		Nodo<T> *insercion(T d,Nodo<T> *r){
			
			if(r == nullptr){
				r = new Nodo<T>;
				r->dato = d;
				r->izquierda = nullptr;
				r->derecha = nullptr;
			}
			else if(d > r->dato){
				Nodo<T> *nuevoDer;
				nuevoDer = insercion(d,r->derecha);
				r->derecha = nuevoDer;
			}else if(d < r->dato){
				Nodo<T> *nuevoIzq;
				nuevoIzq = insercion(d,r->izquierda);
				r->izquierda = nuevoIzq;	
			}
		}
		/*
		void insercionIterativa(T d){
			Nodo<T> *nuevo = new Nodo<T>;
			Nodo<T> *actual = raiz;
			nuevo->dato = d;
			if(esVacia()){
				nuevo->izquierda = nullptr;
				nuevo->derecha = nullptr;
				raiz = nuevo;
				return;
			}
			while(actual!=nullptr){
				if(actual->)
				if(actual->dato > d){
					actual = actual->izquierda;
				}else{
					actual = actual->derecha;
				}
			}
		}*/
		bool busqueda(T d,Nodo<T> *r){
			if(r == nullptr){
				return false;
			}else if(r->dato == d){
				return true;
			}else if(d > r->dato){
				busqueda(d,r->derecha);
			}else{
				busqueda(d,r->izquierda);
			}
		}
		bool busquedaIterativa(T d){
			Nodo<T> *actual = raiz;
			while(actual!=nullptr){
				if(actual->dato == d){
					return true;
				}
				if(actual->dato > d){
					actual = actual->izquierda;
				}else{
					actual = actual->derecha;
				}
			}
			return false;/*La busqueda no tuvo exito o el arbol estaba vacio*/
		}
		Nodo<T> *eliminacion(T d,Nodo<T> *r){
			/*La clave del nodo que se desea a eliminar no se encuentró o el arbol estaba vacio.*/
			if(r == nullptr){
				throw "Error.";
			}else if(r->dato > d){/*Busca en la rama izquierda si la clave es menor que el valor de la raiz*/
				Nodo<T> *nodoIzq = nullptr;
				nodoIzq = eliminacion(d,r->izquierda);
				r->izquierda = nodoIzq;
			}else if(r->dato < d){/*Busca en la rama derecha si la clave es mayor que el valor de la raiz.*/
				Nodo<T> *nodoDer = nullptr;
				nodoDer = eliminacion(d,r->derecha);
				r->derecha = nodoDer;
			}else{                   /**El nodo con la clave correspondiente ya fue encontrado...*/
				Nodo<T> *eliminado;
				eliminado = r;
				/*La raiz tiene a lo más un hijo.En este caso el derecho.El anterior de la raiz apunta al siguiente de la raiz.*/
				if(eliminado->izquierda == nullptr){
					r = eliminado->derecha;
				}/*La raiz tiene un hijo izquierdo.El anterior de la raiz apunta al siguiente de la raiz.*/
				else if(eliminado->derecha == nullptr){
					r = eliminado->izquierda;
				}else{ /*El nodo a eliminar cuenta con ambos hijos(izquierdo y derecho).*/
				
					eliminado = mover(eliminado);
				}
				eliminado = nullptr;
			}
			return r;
		}
		Nodo<T> *mover(Nodo<T> *del){
			Nodo<T> *actual, *menor;
			menor = del;
			actual = del->izquierda;
			while(actual->derecha!=nullptr){
				menor = actual;
				actual = actual->derecha;
			}
			del->dato = actual->dato;
			if(menor == del){
				menor->izquierda = actual->izquierda;
			}else{
				menor->derecha = actual->izquierda;
			}
			return actual;
		}
		int numeroNodos(Nodo<T> *r){
			if(r == nullptr){
				return 0;
			}
			return 1 + numeroNodos(r->izquierda) + numeroNodos(r->derecha); 
		}
		int altura(Nodo<T> *r){
			if(r == nullptr) return 0;
			else{
				int alturaArbIzq = altura(r->izquierda);
				int alturaArbDer = altura(r->derecha);
				if(alturaArbDer > alturaArbIzq)
			  		return alturaArbDer + 1;
				else
			  		return alturaArbIzq + 1;	
			}
		}
	public :
		ArbolBinarioBusqueda(){
			raiz = nullptr;
		}
		~ArbolBinarioBusqueda(){
			delete raiz;
		}
		
		void Orden(){
			recorridoEnOrden(raiz);
		}
		void PostOrden(){
			recorridoEnPostOrden(raiz);
		}
		void PreOrden(){
			recorridoEnPreOrden(raiz);
		}
		void insertar(T d){
			raiz = insercion(d,raiz);
		}
		bool buscar(T d){
			return busqueda(d,raiz);
		}
		bool buscarIterativamente(T d){
			return busquedaIterativa(d);
		}
		void borrar(T d){
			eliminacion(d,raiz);
		}
		int nodos(){
			numeroNodos(raiz);
		}
		int altura(){
			altura(raiz);
		}
};
