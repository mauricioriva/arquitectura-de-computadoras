/**
 * @file tiempo_ejecucion.c
 * @author Mauricio Riva Palacio 316666343
 * @author Dicter
 * @brief Calcula el tiempo total de ejecución de un programa 
 * a partir del catálogo de instrucciones, la cantidad promedio 
 * de ciclos que estas requieren para ejecutarse, la cantidad 
 * de apariciones de cada operación y la frecuencia del procesador 
 * o duración de cada ciclo.
 * @version 0.1
 * @date 2020-03-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Imprime el arreglo de forma horizontal.
 * 
 * @param arreglo El arreglo con los datos.
 * @param longitud El tamaño del arreglo.
 */
void imprime_arreglo(int *arreglo, int longitud)
{
    for (int i = 0; i < longitud; i++)
    {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

/**
 * @brief Calcula el tiempo de ejecución, que es
 * la suma de la multiplicación de el número de ciclos
 * y de el número de veces que se ejecuta por cada instrucción.
 * Σ(nc(i) * ne(i)). Donde cada i es la i-esima instrucción.
 * 
 * @param entrada El archivo con los datos de entrada.
 * @return float El tiempo de ejecución del programa.
 */
float tiempo_ejecucion(FILE *entrada)
{
    int n; //número de instrucciones
    fscanf(entrada,"%d",&n);
    float *num_ciclos = malloc(sizeof(int)*n);
    float aux;
    for (int i = 0; i < n; i++)
    {
        fscanf(entrada,"%f", &aux);
        num_ciclos[i] = aux;
    }
    float suma_total = 0.0;
    float num_repeticiones;
    for (int i = 0; i < n; i++)
    {
        fscanf(entrada,"%f", &num_repeticiones);
        suma_total += num_ciclos[i] * num_repeticiones;
    }
    char tipo; //frecuencia o tiempo (F/T)
    float ciclo; //Ultimo número
    fscanf(entrada," %c", &tipo);
    fscanf(entrada," %f", &ciclo);
    if (tipo == 'F')
    {
        return suma_total / ciclo;
    } 
    else 
    {
        return suma_total * ciclo;
    }
}

/**
 * @brief Función principal, solo recibe un argumento,
 * el nombre del archivo de texto con los datos de
 * la computadora.
 * 
 * @param argc El número de argumentos.
 * @param argv Un arreglo con los argumentos.
 */
void main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("No es el formato de los argumentos.\n");
        return;
    }
    char *nombre = argv[1];
    FILE *entrada = fopen(nombre,"r");
    float tiempo = tiempo_ejecucion(entrada);
    fclose(entrada);
    printf("El tiempo total de ejecución es: %0.3f\n",tiempo);
}
/*
    $] gcc tiempo_ejecucion.c -o tiempo
    $] ./tiempo archivo.txt
*/
