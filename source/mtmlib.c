#include "mtmlib.h"

//	Declaracion de vector de colores.
const char *colores = "ZVRALPON";

//	Funciones de Limpieza de pantalla
void limpieza(void){
	#ifdef UNIX
		system("clear");
	#else
		system("cls");
	#endif
}

void pausa(void){
	char buffer[10];

	printf("\nPulsa [Enter] para continuar..");
	(void)fgets(buffer,9,stdin);
	(void)fgets(buffer,9,stdin);
	limpieza();
}
/*************************************************/

//	Dependiendo de la complejidad dada muestra
//	los colores disponibles
void printColors(int complex){
	if(complex >= 4){
		printf("\tAzul [Z]    Verde   [V]");
		printf("\n\tRojo [R]   Amarillo [A]");
		if(complex >= 6)
			printf("\n\tLila [L]   Púrpura  [P]");  
		if(complex == 8)
			printf("\n\tOcre [O]   Naranja  [N]");
	}
	printf("\n\n");
}

int cargarTablero(char *name){
	int i = 0, j = 0;
	FILE *arch;
	char c;

	//	Verifica el archivo que cargara si este no existe aborta.
	if((arch = fopen(name, "r")) == NULL){
		limpieza();
		fprintf(stderr, "Error: No se pudo abrir %s\n", name);
		exit(1);
	}
	/***********************************************************/

	//	Se asigna caracter a caracter en el arreglo tablero
	while((c = getc(arch)) != EOF){
		if(c == '\n'){
			columnas = ((columnas > j) ? columnas : j);
			i++;
			j=0;
		}
		else{
			if((i < MAX_FILAS) && (j < MAX_COLUMNAS))
				*(tablero[i] + j++) = c;
			else{
				fprintf(stderr,"Error: Tamaño del tablero\n");
				return 0;
			}
		}
	}
	/**********************************************************/
	filas=i;
	fclose(arch);
	return 1;
}

void imprimirTablero(void){
	int i,j;

	for(i = 0; i < filas; i++){
		for(j = 0; j < columnas; j++)
			printf("%c", *(tablero[i] + j));
		printf("\n");
	}
	printf("\n");
}

void ingresarTablero(int f, int lengthCode, char *jugador, int blancas, int negras){
	int j, contador;
	char *status = "B=  N=";

	//	Asignado de informacion de intento en el arreglo tablero
	for(j = 30; j < 37; j++){
		if(j == 32)
			*(tablero[f] + j) = '0' + blancas;
		else 
		if(j == 36)
			*(tablero[f] + j) = '0' + negras;
		else
		*(tablero[f] + j) = *(status + (j - 30));
	}
	if(lengthCode <= 5){
		j = 13;
		if(lengthCode == 5)
			j = 12;
	}
	else
		j = 11;
	for(contador = 0; contador < lengthCode; contador++){
		*(tablero[f] + j) = *(jugador + contador);
		j += 2;
	}
}

char *strUp(char *str){
	int i;

	for(i = 0; *(str + i); i++)
		*(str + i) = toupper(*(str + i));
	return str;
}

void freeAll(char *code, int *conteoCode, char *jugador, int *conteoJugador){
	free(code);
	free(conteoCode);
	free(jugador);
	free(conteoJugador);
}

char *generarCodigo(int lengthCode, int complex){
	int i;
	char *codigo;

	//	Reserva de memoria para guardar el codigo secreto
	codigo = (char *)malloc(sizeof(char) * lengthCode);
	if(codigo == NULL){
		fprintf(stderr, "Error en malloc\n");
        exit(1);
	}
	/*******************************************************/

	srand(time(NULL));		//	Estableciendo semilla de rand
	
	//	Generacion de codigo secreto basado en la rueda 
	//de colores seleccionada
	for(i = 0; i < lengthCode; i++)
		*(codigo + i) = *(colores + (rand() % complex));
	/******************************************************/

	return codigo;
}

int *conteo(int lengthCode, int complex, char *code){
	int i, posicion, *vectorConteo, contador = 0;

	//	Reserva de memoria para guardar los vectores de conteo
	vectorConteo = (int *)malloc(sizeof(int) * complex);
	if(vectorConteo == NULL){
		fprintf(stderr, "Error en malloc\n");
        exit(1);
	}
	/*********************************************************/

	//	Llenado de vector conteo
	for(i = 0; i < complex; i++)
		*(vectorConteo + i) = 0;
	for(posicion = 0; posicion < complex; posicion++){
		for(i = 0; i < lengthCode; i++){
			if(*(colores + posicion) == *(code + i)){
				(*(vectorConteo + posicion))++;
				contador++;
			}
		}
	}
	/****************************************************/

	if(contador < lengthCode){	//	Validacion de llave erronea
		free(vectorConteo);
		return NULL;
	}
	return vectorConteo;
}

int verNegras(int lengthCode, char *code, char *jugador){
	int i, contador;

	for(i = 0, contador = 0; i < lengthCode; i++){
		if(*(code + i) == *(jugador + i))	//	Comparacion 1 a 1 de codigo si
			contador++;						//	son iguales le suma 1 a contador
	}
	return contador;
}

int verBlancas(int complex, int *conteoCode, int *conteoJugador){
	int i, contador;

	//	Comparacion de cantidad de colores encontrados en cada
	//	vector proporcionado por la funcion conteo
	for(i = 0, contador = 0; i < complex; i++){
		if(*(conteoJugador + i) != 0){
			if(*(conteoJugador + i) >= *(conteoCode + i))
				contador += *(conteoCode + i);
			else
				contador += (*(conteoCode + i) - *(conteoJugador + i));
		}
	}
	return contador;
}

void jugar(int lengthCode, int nIntentos, int complex){
	int i, intentoActual, casilla, blancas, negras, bytesLeidos;
	int *conteoCode, *conteoJugador;
	char *code, *jugador;
	size_t bytesLongitud;

	code = generarCodigo(lengthCode, complex);		//	Generacion de codigo secreto
	conteoCode = conteo(lengthCode, complex, code);	//	Vector conteo de codigo secreto
	
	//	Reserva de memoria para guardar el codigo del jugador
	jugador = (char *)malloc(sizeof(char) * lengthCode);
	if(jugador == NULL){
		fprintf(stderr, "Error en malloc\n");
        exit(1);
	}
	/******************************************************/
	
	//	Parte grafica
	limpieza();
	imprimirTablero();
	printf("\n\t    ");
	for(i = 0; i < lengthCode; i++)
		printf("#  ");
	printf("\n\n");
	printColors(complex);
	printf("\t\t> ");
	/********************************/

	bytesLongitud = lengthCode;
	for(casilla = intentoActual = 1; intentoActual <= nIntentos; intentoActual++){
		while(1){
			while(1){
				bytesLeidos = getline(&jugador, &bytesLongitud, stdin);	//	Lectura de codigo
				if((bytesLeidos - 1) != lengthCode)
					printf("\nError: Longitud de código distinta a la definida de [%d]\n\nIngrese su código nuevamente\n\t\t> ", lengthCode);
				else break;
			}
			jugador = strUp(jugador);
			conteoJugador = conteo(lengthCode, complex, jugador);	//	Vector conteo de codigo del jugador
			if(conteoJugador == NULL)	//	Validacion de llave erronea
				printf("\nError: Llave erronea\n\nIngrese su código nuevamente\n\t\t> ");
			else break;
		}

		//	Calculo de fichas negras y blancas
		negras = verNegras(lengthCode, code, jugador);
		blancas = (verBlancas(complex, conteoCode, conteoJugador)) - negras;
		/**********************************************************************/

		if(lengthCode == negras){	//	Condicion de codigo ganador
			ingresarTablero(casilla, lengthCode, jugador, blancas, negras);
			limpieza();
			imprimirTablero();
			printf("\n\t    ");
			for(i = 0; i < complex; i++)
				printf("%c  ", *(code + i));
			printf("\n\n   +-----------------------------+\n");
			printf("   | Has roto el código secreto! |\n");
			printf("   +-----------------------------+\n");
			freeAll(code, conteoCode, jugador, conteoJugador);
			return;
		}
		else{	//	Caso normal
			ingresarTablero(casilla, lengthCode, jugador, blancas, negras);
			limpieza();
			imprimirTablero();
			printf("\n\t    ");
			for(i = 0; i < lengthCode; i++)
				printf("#  ");
			printf("\n\n");
			printColors(complex);
			printf("\t\t> ");
		}
		casilla += 2;
	}
	
	//	Fin de partida
	printf("\n");
	limpieza();
	imprimirTablero();
	printf("\n\t    ");
	for(i = 0; i < complex; i++)
		printf("%c  ", *(code + i));
	printf("\n\n\nHas agotado tus intentos");
	if(negras == lengthCode - 1)
		printf(" (casi lo logras..)");
	freeAll(code, conteoCode, jugador, conteoJugador);
}