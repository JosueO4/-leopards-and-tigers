#include <stdio.h>
#include <stdlib.h>

/**
 * JUEGO LEN CHOA: LEOPARDS AND TIGERS 
 * HECHO POR JOSUE MENA Y ANTONIO FERNANDEZ
 * El juego trata sobre el cazador (tigre) y sus presas (leopardos)
 * La idea del juego es entre dos jugadores ver quien puede ganar
 * si el cazador o sus presas.
 * Se deben hacer movimientos estratégicos que permitan a cada bando mejorar
 * sus posibilidades de ganar.
 * 
 * Para ejecutar el juego se debe: compilar el archivo (en este caso se puede usar gcc).
 * Luego se debe ejecutar el código en la linea de comandos como: ./a.out
 * A partir de ese punto se presenta la interfaz de juego.
 */



/**
 * El struct para el nodo de las listas dobles
 * lleva un valor
 * el valord de la lista donde esta el tigre
 * la posicion del leon
 * un puntero a previo
 * un puntero a siguiente
 */
struct nodo_doble{
	int valor;
	int lista_leon;
	int pos_leon;
	struct nodo_doble* prev;
	struct nodo_doble* sgt;
};
	
/**
 * Struct de la lista doble
 * sirve para llevar el inicio o cabeza de la lista
 */
struct lista_doble{
	struct nodo_doble* inicio;
};

/**
 * Struct del tablero
 * lleva la punta
 * las listas de izq, centro y derecha
 */
struct tablero{
    
    struct lista_doble* punta;
    struct lista_doble* izq;
    struct lista_doble* cen;
    struct lista_doble* der;
};

/**
 * funcion para crear un nodo y alocarlo en memoria
 * retorna un nodo en memoria
 */	
struct nodo_doble* crear_nodo(int num){
	struct nodo_doble* nuevo_nodo = calloc(1,sizeof(struct nodo_doble));
	nuevo_nodo -> valor = num;
	return nuevo_nodo;
	};

/**
 * funcion para insertar un nodo en la lista doble 
 * retorna un int segun el estado de la insercion
 */
int insertar_nodo(struct lista_doble* lista1, int num){
	
	if(lista1 == NULL){
		return -1;
		}
	if(lista1 -> inicio == NULL){
		//lista vacia
		struct nodo_doble* nn = crear_nodo(num);
		lista1 -> inicio = nn;
		return 0; 
		}
		else{
			struct nodo_doble* act = lista1 -> inicio;
			while(act -> sgt != NULL){
				act = act -> sgt;
				}
			struct nodo_doble* nn = crear_nodo(num);
			act -> sgt = nn;
			nn -> prev = act;
			return 0;
		}
	
	}

/**
 * Funcion para crear un tablero y alocarlo en memoria
 * retorna un tablero alocado en memoria
 */
struct tablero* crear_tablero(int tam){
	
	struct tablero* t = calloc(1,sizeof(struct tablero));
	struct lista_doble* listaTigre = calloc(1,sizeof(struct lista_doble));
	struct lista_doble* lista1 = calloc(1,sizeof(struct lista_doble));
	struct lista_doble* lista2 = calloc(1,sizeof(struct lista_doble));
	struct lista_doble* lista3 = calloc(1,sizeof(struct lista_doble));
	
	insertar_nodo(listaTigre,9);
	listaTigre->inicio->lista_leon = 0;
	listaTigre->inicio->pos_leon = 1;
	
	for (int i = 0; i<tam;i++){
		
		insertar_nodo(lista1,0);
		insertar_nodo(lista2,0);
		insertar_nodo(lista3,0);
		
		}
	
	
	t->punta = listaTigre;
	t->izq = lista1;
	t->cen = lista2;
	t->der = lista3;
	
	return t;
	}


/**
 * Funcion que retorna el tamanio de una lista ingresada
 * por parametro
 */
int tamanio_lista(struct lista_doble* lista1){
	struct nodo_doble* act = lista1 -> inicio;
	int contador = 0;
	while (act != NULL){
		contador++;
		act = act -> sgt;
		}
	return contador;
	
	}



/**
 * Funcion para cambiar el valor de una posicion en una lista dada
 * parametros: la lista, el valor a ingresar, la posicion donde se va a cambiar
 */
void cambiar_valor(struct lista_doble* lista1, int valor_nuevo, int posicion){
	if (posicion>tamanio_lista(lista1) || posicion<1){
		printf("Mi rey, el nodo no existe \n");
		return;
		}
	struct nodo_doble* act = lista1 -> inicio;
	int contador = 1;
	while(contador<posicion && act->sgt != NULL){		
		act = act->sgt;
		contador++;
		}
	act->valor = valor_nuevo;
	
	}

/**
 * funcion que ayuda a imprimir el tablero
 * calcula la cantidad de tabs necesarios
 */
void cantidad_tabs(int valor,int cant){
    
    for(int i = 0; i<cant; i++){
        
       printf("\t");
        
    }
    printf("%d",valor);
    
}
/**
 * funcion que ayuda a imprimir el tablero
 * coloca los simbolos
 */
void simbolos(char* carac, int cant){
    
        for(int i = 0; i<cant; i++){
        
       printf("\t");
        
    }
    printf("%s",carac);
    
}
    
    

/**
 * funcion que imprime el tablero
 * no retorna nada solo imprime un tablero 
 */
void imprimir_tablero(struct tablero* t, int tamano){
    
    struct nodo_doble* p = t->punta->inicio;
    struct nodo_doble* act_izq = t->izq->inicio;
    struct nodo_doble* act_cen = t->cen->inicio;
    struct nodo_doble* act_der = t->der->inicio;
    
    int tabs = (tamano*2)-1;
    cantidad_tabs(p->valor,tabs);
    printf("\n");
    
    
    for(int i = 1; i<tamano+1; i++){
        simbolos("/",tabs-i);
        simbolos("|",i);
        simbolos("\\",i);
        printf("\n");
        
        cantidad_tabs(act_izq->valor,tabs-i);
        cantidad_tabs(act_cen->valor,i);
        cantidad_tabs(act_der->valor,i);

        act_izq = act_izq->sgt;
        act_cen = act_cen->sgt;
        act_der = act_der->sgt;
		printf("\n");
    }
    
    
    printf("\n");
    printf("\n");
    
}

/**
 * funcion para sacar el valor int en una posicion especifica de una lista
 * toma una lista y la posicion
 * retorna el valor
 */
int encontrar_valor_pos(struct lista_doble* l, int pos){
	if (pos>tamanio_lista(l) || pos<1){
		printf("Mi rey, el nodo no existe \n");
		return 1;
		}
	struct nodo_doble* act = l -> inicio;
	int contador = 1;
	while(contador<pos){		
		act = act->sgt;
		contador++;
		}
	return act->valor;
	
	
	}


/**
 * funcion que coloca los leopardos al inicio
 * toma el tablero, el tamanio, lado, posicion, numero de leopardo
 * segun el lado especificado se verifica si la posicion en dicho lado se puede colocar un leopardo y retorna 0
 * caso contrario retorna -1
 */
int colocar_leopardos_inicio(struct tablero* t, int tam, int lado, int pos, int leopardo_n){
	
	
	
	struct lista_doble* iz = t->izq;
	struct lista_doble* ce = t->cen;
	struct lista_doble* de = t->der;
	struct lista_doble* p = t->punta;
	
	
	if(lado == 1){
		
		if(encontrar_valor_pos(iz, pos)==0){
			cambiar_valor(iz, leopardo_n, pos);
			return 0;
			}
			return -1;
			
		}
			
	if(lado == 2){
		if(encontrar_valor_pos(ce, pos)==0){
			cambiar_valor(ce, leopardo_n, pos);
			return 0;
		}
		return -1;
			
		}
			
	if(lado == 3){
		
		if(encontrar_valor_pos(de, pos) == 0){
			cambiar_valor(de, leopardo_n, pos);
			return 0;
		}
		return -1;
			
		}
		
	if(lado == 0){
		if(encontrar_valor_pos(p, pos)==0){
			cambiar_valor(p, leopardo_n, pos);
			return 0;
		}
		return -1;
		
		}		
	}


	
/**
 * funcion que mueve una pieza
 * toma la lista de donde viene, la lista a donde va, la posicion donde viene y la posicion donde va
 * cambia el valor de la lista a donde va por el valor de donde viene
 * y viceversa
 */
void mover_pieza(struct lista_doble* listaVengo, struct lista_doble* listaVoy, int posVengo, int posVoy){
	
	
	int valorListaVengo = encontrar_valor_pos(listaVengo, posVengo);
	cambiar_valor(listaVoy, valorListaVengo, posVoy);
	cambiar_valor(listaVengo, 0, posVengo);
	
	
	}

/**
 * una funcion que verifica si hay un leopardo en la posicion especificada
 * toma una lista y la posicion
 * retorna -2 si esta fuera de rango
 * 0 si es valido
 * y -1 en otro caso
 */
int hay_leopardo(struct lista_doble* lista, int pos){
	
	// Posicion fuera del rango
	
	if (pos>tamanio_lista(lista) || pos<1){
		
		return -2;
		
		}
	
	if(encontrar_valor_pos(lista,pos) == 0){
		
		return 0;
		
		}
		
	return -1;
	
	}

/**
 * Funcion para convertir la lista a terminos humanos
 * hace entendible para la maquina y el usuario la lista que se busca
 */
struct lista_doble* encontrar_lista(struct tablero* t, int n){
	
	struct lista_doble* iz = t->izq;
	struct lista_doble* ce = t->cen;
	struct lista_doble* de = t->der;
	struct lista_doble* p = t->punta;
	
	if(n == 1){
		
		return iz;
		}
	if(n == 2){
		
		return ce;
		}
	if(n == 3){
		
		return de;
		}
	if(n == 0){
	
		return p;
		}
	else{
		return 0;
		}
	
	}
	
/**
 * Funcion que calcula los movimientos posibles para el tigre
 * toma la lista actual, la posicion y el numero de lista
 * retorna un numero que es la suma de la cantidad de movimientos
 */	
int movimiento_posible(struct tablero* t,struct lista_doble* lista_actual, int pos, int lista_num){
	
	int cantidad_movimientos = 0;
	
	// Si esta en la punta
	if(lista_num == 0){
		
		// Si se puede mover a la izquierda
		if(hay_leopardo(t->izq,1) == 0){
			
			cantidad_movimientos++;		
			
			}
			
		// Si se puede mover al centro
		if(hay_leopardo(t->cen,1) == 0){
			
			cantidad_movimientos++;		
			
			}
			
		// Si se puede mover a la derecha
		if(hay_leopardo(t->der,1) == 0){
			
			cantidad_movimientos++;		
			
			}
			
			return cantidad_movimientos;
		
		}
		
	
	// Si esta en la izquierda
	if(lista_num == 1){
		
		// Si está en la posicion 1 con posibilidad de ir a la punta
		if(pos == 1){
			
			// Si puede ir a la punta
			if(hay_leopardo(t->punta,1) == 0){
				
				cantidad_movimientos++;	
				
				}
				
			// Si puede ir hacia abajo
			if(hay_leopardo(lista_actual,pos+1) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			// Si se puede mover a la derecha
			if(hay_leopardo(t->cen,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			return cantidad_movimientos;	
			}
			
		// En otro caso
		
		
		// Si se puede mover hacia abajo
		if(hay_leopardo(lista_actual,pos+1) == 0){
			
			cantidad_movimientos++;		
			
			}
		
		// Si se puede mover hacia arriba
		if(hay_leopardo(lista_actual,pos-1) == 0){
			
			cantidad_movimientos++;		
			
			}
			
		// Si se puede mover a la derecha	
		if(hay_leopardo(t->cen,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
		
			return cantidad_movimientos;
		}
		
		
	// Si esta en el medio
	if(lista_num == 2){
		
		// Si está en la posicion 1 con posibilidad de ir a la punta
		if(pos == 1){
			
			// Si puede ir a la punta
			if(hay_leopardo(t->punta,1) == 0){
				
				cantidad_movimientos++;	
				
				}
				
			// Si puede ir hacia abajo
			if(hay_leopardo(lista_actual,pos+1) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			// Si se puede mover a la derecha
			if(hay_leopardo(t->der,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			// Si se puede mover a la izquierda
			if(hay_leopardo(t->izq,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			return cantidad_movimientos;	
			}
			
		// En otro caso
		
		
		// Si se puede mover hacia abajo
		if(hay_leopardo(lista_actual,pos+1) == 0){
			
			cantidad_movimientos++;		
			
			}
		
		// Si se puede mover hacia arriba
		if(hay_leopardo(lista_actual,pos-1) == 0){
			
			cantidad_movimientos++;		
			
			}
			
		// Si se puede mover a la derecha	
		if(hay_leopardo(t->der,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
		// Si se puede mover a la izquierda
		if(hay_leopardo(t->izq,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
		
			return cantidad_movimientos;
		}
		
		
	// Si esta en la derecha
	if(lista_num == 3){
		
		// Si está en la posicion 1 con posibilidad de ir a la punta
		if(pos == 1){
			
			// Si puede ir a la punta
			if(hay_leopardo(t->punta,1) == 0){
				
				cantidad_movimientos++;	
				
				}
				
			// Si puede ir hacia abajo
			if(hay_leopardo(lista_actual,pos+1) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			// Si se puede mover a la izquierda
			if(hay_leopardo(t->izq,pos) == 0){
			
				cantidad_movimientos++;		
			
				}
				
			return cantidad_movimientos;	
			}
			
		// En otro caso
		
		
		// Si se puede mover hacia abajo
		if(hay_leopardo(lista_actual,pos+1) == 0){
			
			cantidad_movimientos++;		
			
			}
		
		// Si se puede mover hacia arriba
		if(hay_leopardo(lista_actual,pos-1) == 0){
			
			cantidad_movimientos++;		
			
			}
			
		// Si se puede mover a la izquierda
		if(hay_leopardo(t->izq,pos) == 0){
			
			cantidad_movimientos++;		
			
			}
		
			return cantidad_movimientos;
		}
		return 0;
	}


/**
 * Funcion que calcula los saltos (comer y saltar a la siguiente posicion) del tigre
 * Recibe la lista actual, la posicion y el numero de lista
 * returna la cantidad de saltos posibles
 */	
int saltos_posibles(struct tablero* t,struct lista_doble* lista_actual, int pos, int lista_num){
	
	int cantidad_saltos = 0;
	
	// Si esta en la punta
	if(lista_num == 0){
		
		// Si no hay leopardo donde cae en la izq y hay uno para comer
		if((hay_leopardo(t->izq,2) == 0)&&(hay_leopardo(t->izq,1) == -1)){
			
			cantidad_saltos++;		
			
			}
			
		// Si no hay leopardo donde cae en el centro y hay uno para comer
		if((hay_leopardo(t->cen,2) == 0)&&(hay_leopardo(t->cen,1) == -1)){
			
			cantidad_saltos++;		
			
			}
			
		// Si no hay leopardo donde cae en la derecha y hay uno para comer
		if((hay_leopardo(t->der,2) == 0)&&(hay_leopardo(t->der,1) == -1)){
			
			cantidad_saltos++;		
			
			}
			
			return cantidad_saltos;
		
		}
		
	// Si esta en la izquierda
	if(lista_num == 1){
		
		// Si está en la posicion 2 con posibilidad de saltar a la punta
		if(pos == 2){
			
			// Si puede saltar a la punta
			if((hay_leopardo(t->punta,1) == 0)&&(hay_leopardo(t->izq,1) == -1)){
				
				cantidad_saltos++;	
				
				}
				
			// Si puede saltar abajo
			if((hay_leopardo(lista_actual,pos+2) == 0)&&(hay_leopardo(lista_actual,pos+1) == -1)){
			
				cantidad_saltos++;		
			
				}
				
			// Si puede saltar a la derecha
			if((hay_leopardo(t->der,pos) == 0)&&(hay_leopardo(t->cen,pos) == -1)){
			
				cantidad_saltos++;		
			
				}
				
			return cantidad_saltos;	
			}
			
		// En otro caso
		
		
		// Si se puede mover hacia abajo
		if((hay_leopardo(lista_actual,pos+2) == 0)&&(hay_leopardo(lista_actual,pos+1) == -1)){
			
			cantidad_saltos++;		
			
			}
		
		// Si se puede mover hacia arriba
		if((hay_leopardo(lista_actual,pos-2) == 0)&&(hay_leopardo(lista_actual,pos-1) == -1)){
			
			cantidad_saltos++;		
			
			}
			
		// Si se puede mover a la derecha	
		if((hay_leopardo(t->der,pos) == 0)&&(hay_leopardo(t->cen,pos) == -1)){
			
				cantidad_saltos++;		
			
				}
		
			return cantidad_saltos;
		}
		
	// Si esta en la izquierda
	if(lista_num == 2){
		
		// Si está en la posicion 2 con posibilidad de saltar a la punta
		if(pos == 2){
			
			// Si puede saltar a la punta
			if((hay_leopardo(t->punta,1) == 0)&&(hay_leopardo(t->cen,1) == -1)){
				
				cantidad_saltos++;	
				
				}
				
			// Si puede saltar abajo
			if((hay_leopardo(lista_actual,pos+2) == 0)&&(hay_leopardo(lista_actual,pos+1) == -1)){
			
				cantidad_saltos++;		
			
				}
				
			return cantidad_saltos;	
			}
			
		// En otro caso
		
		
		// Si se puede mover hacia abajo
		if((hay_leopardo(lista_actual,pos+2) == 0)&&(hay_leopardo(lista_actual,pos+1) == -1)){
			
			cantidad_saltos++;		
			
			}
		
		// Si se puede mover hacia arriba
		if((hay_leopardo(lista_actual,pos-2) == 0)&&(hay_leopardo(lista_actual,pos-1) == -1)){
			
			cantidad_saltos++;		
			
			}
			
			return cantidad_saltos;
		}

		// Si esta en la izquierda
	if(lista_num == 3){
		
		// Si está en la posicion 2 con posibilidad de saltar a la punta
		if(pos == 2){
			
			// Si puede saltar a la punta
			if((hay_leopardo(t->punta,1) == 0)&&(hay_leopardo(t->der,1) == -1)){
				
				cantidad_saltos++;	
				
				}
				
			// Si puede saltar abajo
			if((hay_leopardo(lista_actual,pos+2) == 0)&&(hay_leopardo(lista_actual,pos+1) == -1)){
			
				cantidad_saltos++;		
			
				}
				
			// Si puede saltar a la izquierda
			if((hay_leopardo(t->izq,pos) == 0)&&(hay_leopardo(t->cen,pos) == -1)){
			
				cantidad_saltos++;		
			
				}
				
			return cantidad_saltos;	
			}
			
		// En otro caso
		
		
		// Si se puede mover hacia abajo
		if((hay_leopardo(lista_actual,pos+2) == 0)&&(hay_leopardo(lista_actual,pos+1) == -1)){
			
			cantidad_saltos++;		
			
			}
		
		// Si se puede mover hacia arriba
		if((hay_leopardo(lista_actual,pos-2) == 0)&&(hay_leopardo(lista_actual,pos-1) == -1)){
			
			cantidad_saltos++;		
			
			}
			
		// Si se puede mover a la izquierda	
		if((hay_leopardo(t->izq,pos) == 0)&&(hay_leopardo(t->cen,pos) == -1)){
			
				cantidad_saltos++;		
			
				}
		
			return cantidad_saltos;
		}
		return 0;
	}

/**
 * Convierte la entrada del usuario a la estructura interna del juego
 * toma el valor numerico de la lista donde se ubica y la lista donde quiere ir y sus posiciones respectivas
 * y convierte esos valores a la estructura buscada
 */
int intentar_mover(struct tablero* t, int lis_ven, int p_ve, int lis_voy, int p_vo){
	
	struct lista_doble* l_ve = encontrar_lista(t,lis_ven);
	struct lista_doble* l_vo = encontrar_lista(t,lis_voy);
	int n_leopardo = encontrar_valor_pos(l_ve, p_ve);
	if(lis_ven == 0){
		if(p_vo == 1){
				
				// Si a donde va esta libre y hay un leopardo en el medio
				if(hay_leopardo(l_vo,p_vo) == 0){
				cambiar_valor(l_ve,0,p_ve);
				cambiar_valor(l_vo,n_leopardo,p_vo);
				return 3;
				
				
				}
				printf("No es posible hacer el movimiento!\n");
				return 2;
				}
				printf("No es posible hacer el movimiento!\n");
				return 2;
			}
			
		if(lis_voy == 0){
			if(p_ve == 1){
				
				if(hay_leopardo(l_vo,p_vo) == 0){
				
				cambiar_valor(l_ve,0,p_ve);
				cambiar_valor(l_vo,n_leopardo,p_vo);
				return 3;
				
				
				}
				printf("No es posible hacer el movimiento!\n");
				return 2;
				}
				
				printf("No es posible hacer el movimiento!\n");
				return 2;
	
			}
			
		if(hay_leopardo(l_vo,p_vo) == 0){
			cambiar_valor(l_ve,0,p_ve);
			cambiar_valor(l_vo,n_leopardo,p_vo);
			return 3;
			
			}
			
			printf("No es posible hacer el movimiento!\n");
			return 2;
	

	}


/**
 * Esta funcion permite mover al tigre
 * Se necesita el valor numerico de las listas de donde viene, a donde va y sus posiciones respectivas
 * Ademas se necesita la desicion de saltar o moverse normalmente
 * retorna 1 cuando hizo el salto y se comio al leopardo
 * retorna 2 cuando no se pudo hacer el salto o movimiento
 * retorna 3 cuando se movio simple
 */	
int mover_tigre(struct tablero* t, int l_ven_t, int p_ve_t, int l_voy_t, int p_vo_t,int desicion){
	
	
	struct lista_doble* lista_act_vengo = encontrar_lista(t,l_ven_t);
	struct lista_doble* lista_act_voy = encontrar_lista(t,l_voy_t);
	struct lista_doble* medio = t->cen;
	
	// Si se quiere hacer un salto
	if(desicion == 1){
		
		// Si esta en la punta
		if(l_ven_t == 0){
			
			if(p_vo_t == 2){
				
				// Si a donde va esta libre y hay un leopardo en el medio
				if((hay_leopardo(lista_act_voy,p_vo_t) == 0) && (hay_leopardo(lista_act_voy,p_vo_t-1) == -1)){
				
				cambiar_valor(lista_act_voy,0,p_vo_t-1);
				cambiar_valor(lista_act_vengo,0,p_ve_t);
				cambiar_valor(lista_act_voy,9,p_vo_t);
				
				return 1;
				
				
					}
				printf("No es posible hacer el salto!\n");
				return 2;
				
				
				}
				printf("No es posible hacer el salto!\n");
				return 2;
				
			}
			
		// Si esta intentando saltar a la punta
		if(l_voy_t == 0){
			
			if(p_ve_t == 2){
				
				// Si a donde va esta libre y hay un leopardo en el medio
				if((hay_leopardo(lista_act_voy,p_vo_t) == 0) && (hay_leopardo(lista_act_vengo,p_ve_t-1) == -1)){
					
				cambiar_valor(lista_act_vengo,0,p_ve_t-1);
				cambiar_valor(lista_act_vengo,0,p_ve_t);
				cambiar_valor(lista_act_voy,9,p_vo_t);
				return 1;
				
				
				}
				}
				printf("No es posible hacer el salto!\n");
				return 2;
			}
		
		// Si está saltando en la misma lista
		if(l_ven_t == l_voy_t){
			
			// Saltando en la misma lista para arriba
			if((p_vo_t-p_ve_t)==2){
				
				if((hay_leopardo(lista_act_voy,p_vo_t) == 0) && (hay_leopardo(lista_act_voy,p_vo_t-1) == -1)){
					
					cambiar_valor(lista_act_voy,0,p_vo_t-1);
					cambiar_valor(lista_act_vengo,0,p_ve_t);
					cambiar_valor(lista_act_voy,9,p_vo_t);
					return 1;
				
				}
			}
			
			// Saltando en la misma lista para abajo
			if((p_vo_t-p_ve_t)==-2){
				
				if((hay_leopardo(lista_act_voy,p_vo_t) == 0) && (hay_leopardo(lista_act_voy,p_vo_t+1) == -1)){
					
					cambiar_valor(lista_act_voy,0,p_vo_t+1);
					cambiar_valor(lista_act_vengo,0,p_ve_t);
					cambiar_valor(lista_act_voy,9,p_vo_t);
					return 1;
				
				}
				printf("No es posible hacer el salto!\n");
				return 2;
			}
		}
			
		if((l_ven_t != l_voy_t)&&(p_ve_t == p_vo_t)){
			
			if(abs(l_voy_t-l_ven_t) == 2){
				
				if((hay_leopardo(lista_act_voy,p_vo_t) == 0) && (hay_leopardo(medio,p_vo_t) == -1)){
					
					cambiar_valor(medio,0,p_vo_t);
					cambiar_valor(lista_act_vengo,0,p_ve_t);
					cambiar_valor(lista_act_voy,9,p_vo_t);
					return 1;
				
				}
				printf("No es posible hacer el salto!\n");
				return 2;
				
				}
				printf("No es posible hacer el salto!\n");
				return 2;
			
			}
		}
		
	// Si está intentando hacer un movimiento simple
	if(desicion == 2){
		
		if(l_ven_t == 0){
			if(p_vo_t == 1){
				
				// Si a donde va esta libre y hay un leopardo en el medio
				if(hay_leopardo(lista_act_voy,p_vo_t) == 0){
				cambiar_valor(lista_act_vengo,0,p_ve_t);
				cambiar_valor(lista_act_voy,9,p_vo_t);
				return 3;
				
				
				}
				printf("No es posible hacer el movimiento!\n");
				return 2;
				}
				printf("No es posible hacer el movimiento!\n");
				return 2;
			}
			
		if(l_voy_t == 0){
			if(p_ve_t == 1){
				
				if(hay_leopardo(lista_act_voy,p_vo_t) == 0){
				
				cambiar_valor(lista_act_vengo,0,p_ve_t);
				cambiar_valor(lista_act_voy,9,p_vo_t);
				return 3;
				
				
				}
				printf("No es posible hacer el movimiento!\n");
				return 2;
				}
				
				printf("No es posible hacer el movimiento!\n");
				return 2;
	
			}
			
		if(hay_leopardo(lista_act_voy,p_vo_t) == 0){
			printf("aca");
			cambiar_valor(lista_act_vengo,0,p_ve_t);
			cambiar_valor(lista_act_voy,9,p_vo_t);
			return 3;
			
			}
			
			printf("No es posible hacer el movimiento!\n");
			return 2;
			}
		
		return 2;
		
		}


int main(){
	
	int tam_tablero,li_ven,li_voy,pos_ven,pos_vo,lado,pos, li_ven_ti,li_voy_ti,pos_ven_ti,pos_vo_ti,desicion;
	
	
	do{
	printf("Ingrese el tamano del tablero\n");
	scanf("%d",&tam_tablero);
	}while(tam_tablero>9 || tam_tablero<3);
	
	struct tablero* tab = crear_tablero(tam_tablero);
	struct lista_doble* tig = tab->punta;
	int id_lista = tig->inicio->lista_leon;
	int pos_leon = tig->inicio->pos_leon;
	int cantidad_leopardos = 0;
	int leopardos_muertos = 0;
	
	// Ciclo mientras acomodan los 6 leopardos
	do{
		imprimir_tablero(tab,tam_tablero);
		
		int colocar_leopardos_resp;
		do{
			printf("Dónde desea colocar el leopardo %d\n",cantidad_leopardos+1);
			printf("0 -> Punta\n");
			printf("1 -> Izquierda\n");
			printf("2 -> Centro\n");
			printf("3 -> Derecha\n");
			scanf("%d", &lado);
			printf("Escoja una posicion en el rango 1 a %d:\n", tam_tablero);
			scanf("%d", &pos);
			colocar_leopardos_resp=colocar_leopardos_inicio(tab,tam_tablero,lado,pos,cantidad_leopardos+1);
		}while((lado>3 || lado<0) || (pos>tam_tablero || pos<0) || (colocar_leopardos_resp == -1));
		
		cantidad_leopardos++;
		
		imprimir_tablero(tab,tam_tablero);
		
		if(movimiento_posible(tab,tig,pos_leon,id_lista) + saltos_posibles(tab,tig,pos_leon,id_lista) == 0){
			
			printf("Ganan los leopardos, el tigre no tiene escapatoria\n");
			imprimir_tablero(tab,tam_tablero);
			return 0;
			
			}
		
		
		
		printf("Desea realizar un salto o un movimiento simple?\n");
		printf("1 -> Salto\n");
		printf("2 -> Movimiento simple\n");
		scanf("%d", &desicion);
		
		int mover_tigre_resp;
		do{
			printf("Introduzca la lista donde quiere mover el tigre:\n");
			printf("0 -> Punta\n");
			printf("1 -> Izquierda\n");
			printf("2 -> Centro\n");
			printf("3 -> Derecha\n");
			scanf("%d", &li_voy_ti);
			printf("Introduzca la posición donde irá:\n");
			scanf("%d", &pos_vo_ti);
	
			mover_tigre_resp = mover_tigre(tab, id_lista, pos_leon, li_voy_ti, pos_vo_ti, desicion);
		}while(mover_tigre_resp == 2);
		
		
		
		if(mover_tigre_resp==1){
			
			leopardos_muertos = leopardos_muertos+1;
			id_lista = li_voy_ti;
			pos_leon = pos_vo_ti;
			tig = encontrar_lista(tab,li_voy_ti);
			
			}
			
		if(mover_tigre_resp==3){
			id_lista = li_voy_ti;
			pos_leon = pos_vo_ti;
			tig = encontrar_lista(tab,li_voy_ti);
			}
		
		if(leopardos_muertos==3){
			printf("EL tigre se ha comido 3 leopardos, el tigre ha ganado\n");	
			imprimir_tablero(tab,tam_tablero);
			return 0;
			}
		
		}while(cantidad_leopardos < 6);
	
	
	// Ciclo del juego donde todos pueden hacer movimientos
	do{
		imprimir_tablero(tab,tam_tablero);
		
		int intentar_mover_resp;
		do{
			printf("Introduzca la lista donde está el leopardo a mover:\n");
			printf("0 -> Punta\n");
			printf("1 -> Izquierda\n");
			printf("2 -> Centro\n");
			printf("3 -> Derecha\n");
			scanf("%d", &li_ven);	
			printf("Introduzca la posición donde está:\n");
			scanf("%d", &pos_ven);	
			printf("Introduzca la lista donde quiere mover su leopardo:\n");
			printf("0 -> Punta\n");
			printf("1 -> Izquierda\n");
			printf("2 -> Centro\n");
			printf("3 -> Derecha\n");
			scanf("%d", &li_voy);	
			printf("Introduzca la posición donde irá:\n");
			scanf("%d", &pos_vo);
			intentar_mover_resp = intentar_mover(tab,li_ven,pos_ven,li_voy,pos_vo);
		}while(li_ven>3 || li_ven<0 || pos_ven>tam_tablero || pos_ven<1 || li_voy>3 || li_voy<0 || pos_vo>tam_tablero || pos_vo < 1 || intentar_mover_resp == 2);
		
		if(movimiento_posible(tab,tig,pos_leon,id_lista) + saltos_posibles(tab,tig,pos_leon,id_lista) == 0){
			
			printf("Ganan los leopardos, el tigre no tiene escapatoria\n");
			imprimir_tablero(tab,tam_tablero);
			return 0;
			
			}
		
		imprimir_tablero(tab,tam_tablero);
		
		
		printf("Desea realizar un salto o un movimiento simple?\n");
		printf("1 -> Salto\n");
		printf("2 -> Movimiento simple\n");
		scanf("%d", &desicion);
		
		int mover_tigre_resp;
		do{
			printf("Introduzca la lista donde quiere mover el tigre:\n");
			printf("0 -> Punta\n");
			printf("1 -> Izquierda\n");
			printf("2 -> Centro\n");
			printf("3 -> Derecha\n");
			scanf("%d", &li_voy_ti);
			printf("Introduzca la posición donde irá:\n");
			scanf("%d", &pos_vo_ti);
	
			mover_tigre_resp = mover_tigre(tab, id_lista, pos_leon, li_voy_ti, pos_vo_ti, desicion);
		}while(mover_tigre_resp == 2);
	
		if(mover_tigre_resp==1){
			
			leopardos_muertos = leopardos_muertos+1;
			id_lista = li_voy_ti;
			pos_leon = pos_vo_ti;
			tig = encontrar_lista(tab,li_voy_ti);
			
			}
			
		if(mover_tigre_resp==3){
			id_lista = li_voy_ti;
			pos_leon = pos_vo_ti;
			tig = encontrar_lista(tab,li_voy_ti);
			}
		
		
		}while(leopardos_muertos < 3);
	
	printf("EL tigre se ha comido 3 leopardos, el tigre ha ganado\n");	
	imprimir_tablero(tab,tam_tablero);
	
	return 0;

	}
