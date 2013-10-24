/* 
 * File:   main.c
 * Author: fferegrino
 *
 * Created on 23 de octubre de 2013, 03:26 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include "frecuencias.h"

void imprimeTablaFrecuencias(ListaFrecuencia* frecuencias, const char ruta[]);

// Definimos el tamaño del buffer
#define BUFFER 1024 
// Usada para almacenar temporalmente los valores del archivo
char buffer[BUFFER];
// Nuestras variables para los archivos
FILE * entrada;
FILE * tablaFrecuenciasArchivo;

/*
 * 
 */
int main(int argc, char** argv) {
	printf("Parametros %s\n",argv[1]);
    entrada = fopen(argv[1], "rb");
	
    if (entrada == NULL) {
        perror("No se puede abrir");
        return -1;
    }
    ListaFrecuencia f;
    f.inicio = NULL;
    int leidos;
    do {
	// Leemos el archivo hasta que ya no haya que leer
        // fread nos devuelve la cantidad de datos leídos
        leidos = fread(buffer, 1, BUFFER, entrada);
        // Insertamos las frecuencias en nuestra tabla
        generaFrecuencias(&f,buffer,leidos);
        // Cuando no se hayan ocupado todos los espacios en la lectura
        // sabemos que ya se terminó de leer el archivo
    }while(leidos == BUFFER);
    fclose(entrada);
    // Imprimimos la tabla de frecuencias a un archivo para conservarla
    imprimeTablaFrecuencias(&f,argv[2]);
    printf("\nTotal caracteres: %d\n",f.length);
    
    return (EXIT_SUCCESS);
}

/**
 * Función para imprimir la tabla de frecuencias a un archivo especificado
 * @param frecuencias La tabla de frecuencias en el archivo
 * @param ruta La ruta en la que se debe guardar
 */
void imprimeTablaFrecuencias(ListaFrecuencia* frecuencias,const char ruta[]) {
    tablaFrecuenciasArchivo = fopen(ruta,"w");
    	
    if (tablaFrecuenciasArchivo == NULL) {
        perror("No se puede abrir archivo");
    }
    NodoFrecuencia * aux = frecuencias->inicio;
    while (aux != NULL) {
        fprintf(tablaFrecuenciasArchivo,"C:%d|A:%d\n"
                , (int) aux->frecuencia.caracter
                , aux->frecuencia.apariciones);
        aux = aux->siguiente;
    }
    fclose(tablaFrecuenciasArchivo);
}
