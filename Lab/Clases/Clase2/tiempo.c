#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void tiempo_ejecucion(FILE *entrada, int extra)
{
    int n = fscanf(entrada,"%d"); //numero de operaciones
    int *tabla = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        fscanf(entrada,"%d",&tabla[i]);
    }
}

void main(int argc, char **argv)
{
    char *nombre;
    int extra = -1;
    if (argc == 1)
    {
        printf("Faltan Argumentos\n");
        return;
    }
    if (argc == 2)
    {
        printf("Version Normal\n");
        //archivo está en 1
        nombre = argv[1];
        extra = 0;
    } else
    {
        if (argv[1][0] != 'C')
        {
            printf("Opción invalida\n");
            return;
        }
        nombre = argv[2];
        extra = 1;
        //archivo está en 2
    }
    FILE *entrada = fopen(nombre,"r");
    tiempo_ejecucion(entrada, extra);
}
