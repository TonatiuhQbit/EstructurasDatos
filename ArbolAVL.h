#include<iostream>
/*
  Para guardar la condición de equilbrio en el árbol, la altura de las ramas izquierda y derecha deben diferir a lo mucho en 1.
  La condición de equilibrio puede verse afectada por la inserción e eliminación de un nodo con clave dada,por lo que se deben
  hacer las rotaciones necesarias para que el árbol permanezca equilibrado.
*/
template <typename S>
struct Nodo{
	S dato;
	struct Nodo *izquierda;
	struct Nodo *derecha;
	int factorEquilibrio;	
};

template <class T>
class ArbolAVL{
	private :
		Nodo<T> *raiz;
		/*True en caso de que el árbol esté vacío.*/
		bool esVacio(){
			return raiz == nullptr;
		}
		Nodo<T> *insercion(Nodo<T> *r,T d,bool cambioEnAltura){
			/*Si el árbol es vacio, asignamos memoria a la raiz(o padre)*/
			if(r == nullptr){
				r = new Nodo<T>;
				r->dato = d;
				r->izquierda = nullptr;
				r->derecha = nullptr;
				cambioEnAltura = true;
			}else if(r->dato > d){ /*inserción a la izquierda*/
				Nodo<T> *nuevoIzq = insercion(r->izquierda,d,cambioEnAltura);
				r->izquierda = nuevoIzq;
				if(cambioEnAltura){
					
					switch(r->factorEquilibrio){
						/*El padre cuenta únicamente con el nodo izquierdo y un factorEquilibrio = -1. Al insertar el nuevo nodo el
						  factor de equilibrio del padre será -2,violando por lo tanto la condición de equilibrio.Para reequilibrar 
						  el árbol se debe hacer una rotación Izquierda-Izquierda(hijo con factorEquilibrio = -1) o Izquierda-Derecha
						  (hijo con factorEquilibrio = 1).No hay cambio en la altura.
						*/
				
						case -1:{
							/*Caso Izquierda-Izquierda(Rotación simple.Padre e hijo involucrados.) :
							               PADRE(-2)                                  
							             /         \                           
							           HIJOI(-1)    nullptr  
									  /         \                            
							  NUEVONODOI(0)	   nullptr
							*/
							if(r->izquierda->factorEquilibrio == -1){
								r = rotacionIzquierdaIzquierda(r, r->izquierda); /*Pasamos la raiz y el hijo*/
							}
							/*Caso Izquierda-Derecha (Rotación doble.Padre,hijo y nieto involucrados.):
							               PADRE(-2)
							              /         \
 									HIJOI(1)        nullptr         
								   /        \	     
								nullptr     NUEVONODO(0)
							*/
							else{        
								r = rotacionIzquierdaDerecha(r, r->izquierda); /*Pasamos la raiz y el hijo*/
							}
							cambioEnAltura = false;
							break;
						}
						/*El padre no cuenta con hijos, al insertar a la izquierda el factor de equilibrio se actualiza*/
						case 0:{
							  r->factorEquilibrio = -1;
							break;
						}
						/*El padre(r) contaba con un nodo a la derecha y un factor de equilibrio 1, por lo que al insertar
						  el nuevo nodo a la izquierda el factor de equilibrio del padre se hace cero(1 + -1 = 0).*/
						case 1:{
							cambioEnAltura = false;
							r->factorEquilibrio = 0;
							break;
						}
					}
				}
			}else if(r->dato < d){ /*inserción a la derecha*/
				Nodo<T> *nuevoDer = insercion(r->derecha,d,cambioEnAltura);
				r->derecha = nuevoDer;
				if(cambioEnAltura){
					switch(r->factorEquilibrio){
						/*El padre(r) ya contaba con un nodo a la izquierda(factorEquilibrio = -1),por lo que al insertar a la derecha(1) se
						  preserva el equilibrio(1 + -1 = 0).No hay cambio en la altura.*/
						case -1:{
							r->factorEquilibrio = 0;	
							cambioEnAltura = false;
							break;
						}
						/*El padre no tiene hijos, al insertar el nuevo nodo a la derecha modificamos su factor de equilibrio.
						  Hay un incremento en la altura del árbol. */
						case 0:{
							r->factorEquilibrio = 1;
							break;
						}
						/*El padre cuenta únicamente con el nodo derecho y un factorEquilibrio = 1. Al insertar el nuevo nodo el
						  factor de equilibrio del padre será 2,violando por lo tanto la condición de equilibrio.Para reequilibrar 
						  el árbol se debe hacer una rotación Derecha-Derecha(hijo con factorEquilibrio = 1) o Derecha-Izquierda
						  (hijo con factorEquilibrio = -1).No hay cambio en la altura.
						*/
						case 1:{
							/*Caso Derecha-Derecha(Rotación simple.Padre e hijo involucrados.) :
							               PADRE(2)                                  
							             /         \                           
							           nullptr      HIJOD(1)  
									              /        \                            
							          	      nullptr     NUEVONODO(0)
							*/
							if(r->derecha->factorEquilibrio == 1){
								r = rotacionDerechaDerecha(r, r->derecha);
							}
							/*Caso Derecha-Izquierda (Rotación doble.Padre,hijo y nieto involucrados.):
							               PADRE(2)
							              /        \
 									nullptr        HIJOD(-1)         
								                  /        \	     
								          NUEVONODO(0)     nullptr
							*/
							else{
								r = rotacionDerechaIzquierda(r, r->derecha);
							}
							cambioEnAltura = false;
							break;
						}
					}
				}
			}else{
				throw "Error";	
			}
			return r;
		}
		/*Funciones de los 4 casos de rotación para equilibrar el árbol en caso de que se viole la condición de equilibrio.*/
		
		/*Inserción en el subárbol izquierdo de la rama izquierda(rota a la "derecha").*/
		Nodo<T> *rotacionIzquierdaIzquierda(Nodo<T> *padre,Nodo<T> *hijo){
			padre->izquierda = hijo->derecha;
			hijo->derecha = padre;
			if(hijo->factorEquilibrio == -1){ /*El hijo tiene tiene un nodo a la izquierda*/
				hijo->factorEquilibrio = padre->factorEquilibrio = 0; /*Al hacer la rotación se equilibra.*/
			}else{
				padre->factorEquilibrio = -1;
				hijo->factorEquilibrio = 1;
			}
			return hijo; /*el hijo apuntará al padre.*/
		}
		/*Inserción en el subárbol derecho de la rama derecha(rota a la "izquierda").*/
		Nodo<T> *rotacionDerechaDerecha(Nodo<T> *padre,Nodo<T> *hijo){
			padre->derecha = hijo->izquierda;
			hijo->izquierda = padre;
			if(hijo->factorEquilibrio == 1){ /*El hijo tiene un nodo a la derecha.*/
				padre->factorEquilibrio = hijo->factorEquilibrio = 0; /*Los factores se actualizan a 0,al hacer la rotación que equilbra el árbol.*/
			}else{
				padre->factorEquilibrio = 1;
				hijo->factorEquilibrio = -1;
			}
			return hijo;/*el hijo apuntará al padre.*/
		}
		/*Inserción en el subárbol derecho de la rama izquierda.*/
		Nodo<T> *rotacionIzquierdaDerecha(Nodo<T> *padre, Nodo<T> *hijo){
			Nodo<T> *nieto = hijo->derecha;
			padre->izquierda = nieto->derecha;
			nieto->derecha = padre;
			hijo->derecha = nieto->izquierda;
			nieto->izquierda = hijo;
			
			if(nieto->factorEquilibrio == 1){
				hijo->factorEquilibrio = -1;
			}else{
				hijo->factorEquilibrio = 0;
			}if(nieto->factorEquilibrio == -1){
				padre->factorEquilibrio = 1;
			}else{
				padre->factorEquilibrio = 0;
			}
			nieto->factorEquilibrio = 0;
			return nieto;
		}
		/*Inserción en el subárbol izquierdo de la rama derecha.*/
		Nodo<T> *rotacionDerechaIzquierda(Nodo<T> *padre, Nodo<T> *hijo){
			Nodo<T> *nieto = hijo->izquierda;
		    padre->derecha = nieto->izquierda;
		    nieto->izquierda = padre;
		    hijo->izquierda = nieto->derecha;
		    nieto->derecha = hijo;
		    
		    if(nieto->factorEquilibrio == 1){//El nieto tiene un nodo a la derecha.
		    	padre->factorEquilibrio = -1; //Una vez rotado el factor del padre es -1
			}else{
				padre->factorEquilibrio = 0; 
			}
			if(nieto->factorEquilibrio == -1){ //El nieto tiene un nodo a la izquierda
				hijo->factorEquilibrio = 1;  
			}else{
				hijo->factorEquilibrio = 0;
			}
			nieto->factorEquilibrio = 0;
		  return nieto;
		}
		bool busqueda(T d, Nodo<T> *padre){
			if(padre == nullptr){
				return false;
			}else if(padre->dato == d){
				return true;
			}else if(padre->dato > d){ /*continua la búsqueda en la rama izquierda*/
				busqueda(d, padre->izquierda);
			}else{
				busqueda(d,padre->derecha);/*continua la búsqueda en la rama derecha*/
			}
		}
		/*Hijo izquierdo,raiz,hijo derecho.*/
		void orden(Nodo<T> *padre){
			if(padre != nullptr){
				orden(padre->izquierda);
				std::cout << padre->dato << "\n";
				orden(padre->derecha);	
			}
		}
		/*Raiz,hijo izquierdo,hijo derecho.*/
		void preOrden(Nodo<T> *padre){
			if(padre != nullptr){
				std::cout << padre->dato << "\n";
				preOrden(padre->izquierda);
				preOrden(padre->derecha);	
			}
		}
		/*Hijo izquierdo,hijo derecho,raiz.*/
		void postOrden(Nodo<T> *padre){
			if(padre != nullptr){
				postOrden(padre->izquierda);
				postOrden(padre->derecha);	
				std::cout << padre->dato << "\n";
			}
		}
		
		void borrar(Nodo<T> *padre, T d){
			
		}
	public :
		ArbolAVL(){
			raiz = nullptr;
		}
		~ArbolAVL(){
			delete raiz;
		}
		void orden(){
			orden(raiz);
		}
		void preOrden(){
			preOrden(raiz);
		}
		void postOrden(){
			postOrden(raiz);
		}
		void insertar(T d){
			raiz = insercion(raiz,d,false);
		}
		bool buscar(T d){
			return busqueda(d,raiz);
		}
};
