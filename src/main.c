/*
*		UCAB - GUAYANA 
*	Algoritmos y Programacion II
*
*	Programa para el juego Mastermind
*
*	Documentación de funciones en el
*	directorio de Programa.
*
*	Hecho por Alejandro Rosas
*/

#include "mtmlib.h"

int main(void){
	int opcion, temp, status, lengthCode, complex, nIntentos;
	char buffer[10], *tab[] = {"tabs/tab8.txt", "tabs/tab10.txt", "tabs/tab12.txt"};

	limpieza();
	while(1){
		printf("  -----------------\n");
		printf("    > MASTERMIND_\n");
		printf("  -----------------\n");
		printf("\nQue desea realizar:\n\n");
		printf("\t[1] Jugar una partida\n");
		printf("\t[2] Información del juego\n");
		printf("\n\t[0] Salir del programa\n");
		printf("\n\tSu opcion (0-2):\n\n\t> ");
		scanf("%d",&opcion);
		switch (opcion){
			case 0:
				printf("\nGracias por jugar!\n");
				pausa();
				return 0;
			case 1:
				limpieza();
				printf("    Ingrese un número dentro del rango respectivo en");
				printf("\n\tcada opción para la generación del juego\n\n");
				while(1){
					printf("\n	Tamaño del código [4 - 6]\n\t> ");
					//	Validación de que la entrada sea un número
					status = scanf("%d", &lengthCode);
					while(status != 1){
						while(((temp = getchar()) != EOF) && (temp != '\n'));
						printf("\n{Entrada Inválida... por favor ingrese otro número}\n\t> ");
						status = scanf("%d", &lengthCode);
					}
					/*******************************************************/
					//	Validación de valor dentro de dominio admisible
					if((lengthCode < 4)||(lengthCode > 6))
						printf("\n\tTamaño de código inválido\n");  
					else break;
					/**********************************************/
				}  
				while(1){
					printf("\n	Rango de la rueda de colores [4, 6 o 8]\n\t> ");
					//	Validación de que la entrada sea un número
					status = scanf("%d", &complex);
					while(status != 1){
						while(((temp = getchar()) != EOF) && (temp != '\n'));
						printf("\n{Entrada Inválida... por favor ingrese otro número}\n\t> ");
						status = scanf("%d", &complex);
					}
					/*******************************************************/
					//	Validación de valor admitido
					if(complex != 4)
						if(complex != 6)
							if(complex != 8)
								printf("\n\tRango de rueda de colores inválido\n");
							else break;
						else break;
					else break;
					/***************************************************************/
				}
				while(1){
					printf("\n	Número de intentos [8, 10 o 12]\n\t> ");
					//	Validación de que la entrada sea un número
					status = scanf("%d", &nIntentos);
					while(status != 1){
						while(((temp = getchar()) != EOF) && (temp != '\n'));
						printf("\n{Entrada Inválida... por favor ingrese otro número}\n\t> ");
						status = scanf("%d", &nIntentos);
					}
					/*******************************************************/
					//	Validación de valor admitido
					if(nIntentos != 8)
						if(nIntentos != 10)
							if(nIntentos != 12)
								printf("\n\tNúmero de intentos inválido\n");
							else break;
						else break;
					else break;
					/********************************************************/
				}
				(void)fgets(buffer,9,stdin);
				//	Carga el tablero de tamaño [nIntentos]
				cargarTablero(tab[(nIntentos < 10) ? 0 : (nIntentos == 10) ? 1 : 2]);
				jugar(lengthCode, nIntentos, complex);
				break;
			case 2:
				limpieza();
				printf("  -----------------\n");
				printf("    > MASTERMIND_\n");
				printf("  -----------------\n");
				printf("\n\tMastermind, es un juego de dos participantes que\n");
				printf("\tconsiste en romper un código secreto compuesto por\n");
				printf("\tfichas de colores. Se juega en un tablero con fichas\n");
				printf("\tde colores y fichas pequeñas blancas y negras. Uno\n");
				printf("\tde los 2 participantes escoge cierta cantidad de\n");
				printf("\tfichas de colores, generalmente 4, y coloca un\n");
				printf("\tcódigo oculto al otro jugador.\n");
				printf("\n\tUCAB Guayana - Algoritmos y Programacion 2\n\n");
				break;
			default:
			printf("Error en seleccion\n");
		}
		pausa();
	}
	return 0;
}