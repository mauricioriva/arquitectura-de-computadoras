/*
 fl.c

 José Galaviz
 marzo 2000


      FORMATO DE IEEE DE PRECISION SENCILLA
         (tipo float de C/C++)

Se utilizan 4 bytes (octetos). Del más significativo al
menos significativo se utilizan asi:

1) El primer bit (msb) del primer byte (msbyte) se utiliza
para decir el signo de la mantisa: 1 si es negativa, 0 si es
positiva.

2) Los siguientes 8 bits (los 7 restantes del primer byte y
el msb del siguiente byte), se utilizan para expresar el
exponente en "exceso a 127". Es decir:

  A. Sea "ne" el valor del número que se encuentra escrito
  en estos 8 bits, considerado como un numero binario comun
  sin signo.

  B. Sea "nd" el valor del número que se desea representar,
  es decir el valor real del exponente.

  ne y nd obedecen la expresión:  ne - 127 = nd
  es decir:                       ne = nd + 127

3) Los restantes 23 bits representan la mantisa normalizada,
es decir, la mantisa desplazada tantos lugares hacia la
izquierda como sea necesario para que sea ocupado el lugar
de las unidades excluyendo ese dígito. Se forza a que la
mantisa sea de la forma "1.abcde..." y en estos 23 bits se
escriben los dígitos binarios "abcde...".

EJEMPLO:

Supóngase que se desea escribir 15 * 2 ^(-10) es decir:
                      15/1024

esto en binario se escribe:
                      01111 x 2 ^(-10)
                      ^^^^^
                      (15)

normalizando la mantisa:
                      01.111 x 2 ^(-7)

(se recorrió el punto tres lugares a la izquierda y
10 - 3 = 7). Se presupone la existencia del "1" a la
izquierda del punto y por tanto no se escribe.

entonces el número binario que hay que escribir como
exponente es el que usualmente representaría sin signo al:

        ne = -7 + 127 = 120 = 64 + 32 + 16 + 8 = 01111000

Así que lo que se escribe es:

 byte  contenido
  1    0 0111100 (signo de mantisa y 7 primeros bits de exp.)
  2    0 1110000 (ultimo bit de exp. y primeros 7 de mantisa)
  3    00000000  (mantisa)
  4    00000000  (mantisa)

*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

float        npf1, *npf2;
unsigned int *p, n;

char         car;

void printBits(unsigned int ent) {
    unsigned int  val, i, msk;
    unsigned int  exponente, expn;
    
    val = ent & 0X80000000;
    printf("Signo de mantisa: ");
    if (val) 
        printf ("negativo (1)\n");
    else
        printf ("positivo (0)\n");

    val = ent & 0X7F800000;
    val = val >> 23;
    exponente = val - 127;
    msk = 0X000000080;
    printf ("Exponente: %d en exceso a 127: %d = ", exponente, val);
    for (i = 0; i < 8; i++) {
        if (msk & val) 
            printf("1");
        else 
            printf("0");
        msk >>= 1;
    }
    
    val = ent & 0X007FFFFF;
    msk = 0X0000400000;
    printf("\n Mantisa: 1 + %d = 1. ", val);
    for (i = 0; i < 23; i++) {
        if (msk & val) 
            printf("1");
        else 
            printf("0");
        msk >>= 1;
    }
    printf("\n");
}

int main () {
    printf ("\n\nPUNTO FLOTANTE DE PRECISIÓN SIMPLE\n");
    printf ("Formato de IEEE, equivalente a el tipo float de C\n\n");
    printf ("\nEl tamaño, en bytes (octetos), de un float es: %ld\n\n",sizeof(float));
    
    printf ("\nInfinito: \n");
    p = (unsigned int *)&npf1;
    // Infinito
    *p = 0;
    *p = 0X7F800000;
    printf ("1. %E en punto flotante: %08X\n\n",npf1,*p);
    printBits(*p);
    
    printf ("\nCero: \n");
    // Cero
    *p = 0;
    printf ("2. %E en punto flotante: %08X\n\n",npf1,*p);
    printBits(*p);
    
    printf ("\nEl número positivo más pequeño: \n");
    // La mantisa más pequeña
    // EL número mas pequeño representable como float
    *p = 0;
    *p = 0X00000001;
    printf ("3. %E en punto flotante: %08X\n\n",npf1,*p);
    printBits(*p);
    
    printf ("\nEl número positivo más grande: \n");
    // el número más grande expresable como float
    *p = 0;
    *p = 0X7F7FFFFF;
    printBits(*p);
    
    printf ("4. %E en punto flotante: %08X\n\n",npf1,*p);
    
    printf ("\nEl número negativo más pequeño: \n");
    // La mantisa más pequeña
    // EL número mas pequeño representable como float
    *p = 0;
    *p = 0X80000001;
    printBits(*p);
    
    printf ("5. %E en punto flotante: %08X\n\n",npf1,*p);
    
    printf ("\nEl número negativo más grande: \n");
    // el número más grande expresable como float
    *p = 0;
    *p = 0XFF7FFFFF;
    printBits(*p);
    
    printf ("6. %E en punto flotante: %08X\n\n",npf1,*p);
    
    printf ("\nLa expresión de ¶: \n");
    npf1 = M_PI;
    p = (unsigned int *)&npf1;
    printBits(*p);
    
    printf ("7. %f = %E en punto flotante: %08X\n\n",npf1,npf1,*p);
    printBits(*p);
    
    do {
        printf ("\n¿Que operación desea hacer?\n");
        printf ("A) Pasar de la representación hexadecimal a la de punto flotante\n");
        printf ("B) Pasar de la representación de punto flotante a la hexadecimal\n");
        printf ("C) Salir\n");
        do {
            printf ("Pulse la tecla [A], [B] o [C] solamente: ");
            //      scanf ("%c", &car);
            car = getchar();
            getchar();
            car = toupper(car);
            printf ("\n");
        } while ((car!='A') && (car!='B') && (car!='C'));
        
        if (car == 'C') exit (0);
        
        system ("clear");
        if (car == 'A') {
            printf ("\nNúmero en hexadecimal: ");
            scanf ("%X", &n);
            npf2 = (float *)&n;
            printf ("\nEn punto flotante: %f = %E \t En hexadecimal: %08X\n\n",*npf2,*npf2,n);
        }
        else {
            printf ("\nNúmero en punto flotante: ");
            scanf ("%f", &npf1);
            p = (unsigned int *)&npf1;
            printf ("\nEn punto flotante: %f = %E \t En hexadecimal: %08X\n\n",npf1,npf1,*p);
        }
        
        getchar();
        do {
            printf ("\n¿Desea hacer otra operación (s/n)?\n");
            car = getchar();
            getchar();
            car = toupper(car);
            printf ("\n");
        } while ((car!='N') && (car!='S'));
        if (car == 'S') system ("clear");
    }while (car!='N');
}
