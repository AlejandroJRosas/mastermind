#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define UNIX
#define MAX_FILAS 26
#define MAX_COLUMNAS 40

/*	  Funciones de visualización de Juego	  */

//  Hace uso del comando clean y limpia la pantalla.
void limpieza(void);

//  Pide precionar enter para continuar y luego limpia la pantalla.
void pausa(void);

//  Imprime por pantalla los colores admitidos en el juego.
void printColors(int complex);

//  Carga el tablero desde un archivo.
int cargarTablero(char *name);

//  Imprime por pantalla el tablero.
void imprimirTablero(void);

//  Ingresa información del juego a la matriz tablero.
void ingresarTablero(int f, int lengthcode, char *jugador, int blancas, int negras);

/*///////////////////////////////////////////////////////*/

/*		Funciones de lógica de Juego		*/

//  Recibe una cadena y la devuelve con todos sus caracteres en mayúsculas.
char *strUp(char *str);

//  Libera los bloques de memoria reservados por malloc en sus diferentes usos.
void freeAll(char *code, int *conteoCode, char *jugador, int *conteoJugador);

//  Genera un código aleatorio que es el que el jugador debera descifrar.
char *generarCodigo(int lengthCode, int complex);

//  Hace un conteo de las letras que se encuentran en el código ingresado por el
//  jugador si el código obtiene un conteo menor a la longitud del codigo este
//  regresa NULL dando a entender que se utilizo una llave inválida de lo contrario
//  devuelve un arreglo con el conteo de ese código.
int *conteo(int lengthCode, int complex, char *code);

//  Función principal donde se da el juego.
void jugar(int lengthCode, int nIntentos, int complex);

//  Recibe ambos códigos, el de la maquina y el jugador, y los compara casilla a casilla
//  para obtener la cantidad de pines negros en el código del jugador.
int verNegras(int lengthCode, char *code, char *jugador);

//  Recibe los conteos de letras de ambos códigos y la complejidad del juego y los compara 
//  para asi determinar la cantidad de pines blancos.
int verBlancas(int complex, int *conteoCode, int *conteoJugador);