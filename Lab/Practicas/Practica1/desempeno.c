#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void rendimiento(float **tabla, int n, int m)
{
    return; // Que operacion a la tabla ???
}

void imprime_arreglo(float *arreglo, int longitud)
{
    for (int i = 0; i < longitud; i++)
    {
        printf("%0.2f ", arreglo[i]);
    }
    printf("\n");
}

/**
 * @brief Suma los elementos de las columnas en la tabla, los guarda
 * en un arreglo y te devuelve el número menor de ese arreglo, el cuál
 * es el menor tiempo de ejecución.
 * @param tabla La matriz con los datos.
 * @param n El número de renglones.
 * @param m El número de columnas.
 */
void tiempo_respuesta(float **tabla, int n, int m)
{
    float *resultados = malloc(sizeof(int)*m);
    int cont = 0;
    float aux = 0;
    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            aux += tabla[i][j];
        }
        resultados[cont] = aux;
        cont++;
        aux = 0;
    }
    imprime_arreglo(resultados,m);
    float menor = resultados[0];
    int computadora = 1;
    aux = 0;
    for (int i = 1; i < m; i++)
    {
        aux = resultados[i];
        if (menor > aux)
        {
            menor = aux;
            computadora = i+1;
        }
    }
    printf("La computadora %d : %0.2f tiene el mejor tiempo de respuesta.\n", computadora, menor);
}

/**
 * @brief Imprime los elementos de la matriz en la terminal
 * en forma de tabla.
 * @param tabla La matriz con los datos.
 * @param n El numero de renglones de la matriz.
 * @param m El numero de columnas de la matriz.
 */
void imprime_tabla(float **tabla, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%0.2f ",tabla[i][j]); // Hasta 2 decimales
        }
        printf("\n");
    }
}

/**
 * @brief Procesa el archivo y los datos del mismo los ingresa
 * a una matriz, y dependiendo de la bandera ejecuta la función
 * correspondiente. (T = tiempo de respuesta o R = rendimiento).
 * @param entrada El archivo a procesar de tipo FILE
 * @param bandera La bandera es T o R.
 */
void lee_archivo(FILE *entrada, char *bandera)
{
    int n, m;
    fscanf(entrada,"%d %d", &n, &m);
    float **tabla = malloc(sizeof(int)*n); //Creas n renglones
    for (int i = 0; i < n; i++)
    {
        tabla[i] = malloc(sizeof(int)*m); //Cada renglon es de tamaño m
    }
    float aux;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(entrada,"%f", &aux);
            tabla[i][j] = aux;
        }
    }
    imprime_tabla(tabla,n,m);
    //printf("%c", *bandera);
    if (*bandera == 'T')
    {
        tiempo_respuesta(tabla,n,m);
    } else
    {
        rendimiento(tabla,n,m);
    }
}

/**
 * @brief Procesa la entrada, verifica que los argumentos del programa
 * sean correctos.
 * @param argc El número de argumentos deben ser por lo menos 3.
 * @param argv El primer argumento es el ejecutable, el segundo argumento
 * es la bandera (T = tiempo de respuesta o R = rendimiento), el tercer
 * argumento es el archivo de texto con los datos de la tabla.
 */
void main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Faltan Argumentos\n");
        return;
    }
    char *nombre = argv[2];
    char *bandera = argv[1];
    if (!(*bandera == 'R' || *bandera == 'T'))
    {
        printf("Error al leer la bandera\n");
        return;
    }
    FILE *entrada = fopen(nombre,"r");
    lee_archivo(entrada,bandera);
    /* argv(0)  argv(1) argv(2)
    ./desempeño bandera  archivo.txt */
}
