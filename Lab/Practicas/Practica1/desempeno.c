/**
 * @file desempeno.c
 * @author Mauricio Riva Palacio 316666343
 * @author Dicter
 * @brief Calcula el mejor desempeño de entre un grupo de computadoras.
 * @version 0.1
 * @date 2020-03-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void tiempo(float *media_arit, float *media_geo, int longitud);
void rendimiento(float *media_arit, float *media_geo, int longitud);
float * media_aritmetica(float **tabla, int n, int m);
float * media_geometrica(float **tabla, int n, int m);

/**
 * @brief Imprime el arreglo de forma horizontal.
 * 
 * @param arreglo El arreglo con los datos.
 * @param longitud El tamaño del arreglo.
 */
void imprime_arreglo(float *arreglo, int longitud)
{
    for (int i = 0; i < longitud; i++)
    {
        printf("%0.4f ", arreglo[i]);
    }
    printf("\n");
}

/**
 * @brief Calcula el tiempo de respuesta, dado por
 * T(B) / T(A), donde T(X) pertenece a la media aritmética.
 * El T(A) es una constante la cual pertenece a la computadora
 * que tiene el menor valor en la media geometrica.
 * 
 * @param media_arit Arreglo con los datos de la media aritmetica.
 * @param media_geo Arreglo con los datos de la meida geometrica.
 * @param longitud El tamaño de ambos arreglos.
 */
void tiempo(float *media_arit, float *media_geo, int longitud)
{
    int comp = 1; //numero de computadora
    float valor_menor = media_geo[0];
    for (int i = 1; i < longitud; i++)
    {
        if (media_geo[i] < valor_menor)
        {
            valor_menor = media_geo[i];
            comp = i;
        }
    }
    float valor_menor_arit = media_arit[comp];
    float *resultados = malloc(sizeof(int)*longitud);
    for (int i = 0; i < longitud; i++)
    {
        resultados[i] = media_arit[i] / valor_menor_arit;
    }
    printf("La computadora con mejor tiempo de respuesta es: c%i\n", comp);
    printf("  c0     c1     c2     c3\n");
    imprime_arreglo(resultados,longitud);
}

/**
 * @brief Calcula el Rendimiento, dado por
 * Ren(A) / Ren(B), donde Ren(X) pertenece a la media aritmética.
 * El Ren(A) es una constante la cual pertenece a la computadora
 * que tiene el mayor valor en la media geometrica.
 * 
 * @param media_arit Arreglo con los datos de la media aritmetica.
 * @param media_geo Arreglo con los datos de la meida geometrica.
 * @param longitud El tamaño de ambos arreglos.
 */
void rendimiento(float *media_arit, float *media_geo, int longitud)
{
    int comp = 1; //numero de computadora
    float valor_mayor = media_geo[0];
    for (int i = 1; i < longitud; i++)
    {
        if (media_geo[i] > valor_mayor)
        {
            valor_mayor = media_geo[i];
            comp = i;
        }
    }
    float valor_mayor_arit = media_arit[comp];
    float *resultados = malloc(sizeof(int)*longitud);
    for (int i = 0; i < longitud; i++)
    {
        resultados[i] = valor_mayor_arit / media_arit[i];
    }
    printf("La computadora con mejor rendimiento es: c%i\n", comp);
    printf("  c0     c1     c2     c3\n");
    imprime_arreglo(resultados,longitud);
}

/**
 * @brief Imprime los elementos de la matriz en la terminal
 * en forma de tabla.
 * 
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
            printf("%0.4f ",tabla[i][j]); // Hasta 4 decimales
        }
        printf("\n");
    }
}

/**
 * @brief Dada una tabla, crea un arreglo con la media aritmetica
 * (promedio) de cada uno de los renglones de la tabla.
 * 
 * @param tabla La tabla con los datos.
 * @param n El número de renglones.
 * @param m El número de columnas.
 * @return float* Apuntador que indica en 
 * donde se encuentra el arreglo con los promedios.
 */
float * media_aritmetica(float **tabla, int n, int m)
{
    float *media_arit = malloc(sizeof(int)*n); //Arreglo con los resultados
    float aux = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            aux += tabla[i][j];
        }
        media_arit[i] = aux / m;
        aux = 0;
    }
    return media_arit;
}

/**
 * @brief Dada una tabla, crea un arreglo con la media geometrica
 * de cada uno de los renglones de la tabla. La media geometrica está
 * definida como la raiz n-esima de la multiplicación de todos los factores.
 * 
 * @param tabla La tabla con los datos.
 * @param n El número de renglones.
 * @param m El número de columnas.
 * @return float* Apuntador que indica en 
 * donde se encuentra el arreglo con la media geometrica
 * de cada uno de los renglones.
 */
float * media_geometrica(float **tabla, int n, int m)
{
    float **tabla_norm = malloc(sizeof(int)*n); //La tabla normalizada
    for (int i = 0; i < n; i++)
    {
        tabla_norm[i] = malloc(sizeof(int)*m);
    }
    float norm = 0;
    for (int j = 0; j < m; j++)
    {
        norm = tabla[0][j];
        for (int i = 0; i < n; i++)
        {
            tabla_norm[i][j] = tabla[i][j] / norm;
        }
    }
    //imprime_tabla(tabla_norm,n,m);
    float *resultados = malloc(sizeof(int)*n);
    float aux = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            aux *= tabla_norm[i][j];
        }
        resultados[i] = pow(aux, (float)1/n);
        aux = 1;
    }
    return resultados;
}

/**
 * @brief Lee el archivo con los datos, y los guarda en un
 * espacio de memoria dinámica, el cual es un arreglo bidimensional
 * para tener los datos en forma de una matriz de nxm.
 * 
 * @param entrada El arhivo con los datos.
 * @param n El número de renglones.
 * @param m El número de columnas.
 * @return float** Apuntador que indica en 
 * donde se encuentra la tabla (arreglo) con los datos.
 */
float ** lee_archivo(FILE *entrada, int n, int m)
{
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
    return tabla;
}

/**
 * @brief Función principal la cuál verifica que los argumentos al
 * ejecutar el programa sean correctos, como la bandera y el archivo
 * con los datos. Independientemente de la bandera, los datos del archivo
 * los guarda en una tabla(arreglo), y obtiene la media aritmetica y la media
 * geometrica. Y finalmente dependiendo de la bandera se calcula el rendimiento
 * o el tiempo de respuesta.
 * 
 * @param argc El número de argumentos deben ser por lo menos 3.
 * @param argv El primer argumento es el ejecutable, el segundo argumento
 * es la bandera (T = tiempo de respuesta o R = rendimiento), el tercer
 * argumento es el archivo de texto con los datos de la tabla.
 */
void main(int argc, char **argv)
{
    bool rend = false;
    if (argc != 3)
    {
        printf("Faltan Argumentos.\n");
        return;
    }
    char *archivo = argv[2];
    char *bandera = argv[1];
    if (*bandera == 'R')
    {
        rend = true;
    } 
    else if (*bandera != 'T')
    {
        printf("Error al leer la bandera.\n");
        return;
    }
    FILE *entrada = fopen(archivo,"r");
    if (entrada == NULL)
    {
        printf("Error al leer el archivo.\n");
        return;
    }
    int n, m; //Renglones y columnas
    fscanf(entrada,"%d %d", &n, &m);
    float **tabla = lee_archivo(entrada, n, m);
    float *media_geo = media_geometrica(tabla,n,m);
    float *media_arit = media_aritmetica(tabla,n,m);
    if (rend)
    {
        rendimiento(media_arit,media_geo,n);
    } 
    else
    {
        tiempo(media_arit,media_geo,n);
    }
    /*
    printf("Tabla Original\n");
    imprime_tabla(tabla,n,m);
    printf("Media Aritmetica\n");
    imprime_arreglo(media_arit,n);
    printf("Media Geometrica\n");
    imprime_arreglo(media_geo,n);
    */
}
/*
    ]$ gcc desempeno.c -o desempeno -lm
    ]$ ./desempeno R prueba.txt
    ]$ ./desempeno T prueba.txt

    ./desempeno bandera  archivo.txt 
    argv(0)     argv(1)    argv(2)
*/
