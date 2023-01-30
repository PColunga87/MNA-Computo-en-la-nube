/*definiendo headers*/
#include <iostream>
#include <omp.h>
#include <time.h>

/*definiendo elementos, pedazos y datos*/
#define N 1000 
#define chunk 100 
#define mostrar 10 

/*Funcion imprimir arreglos*/
void imprimeArreglo(float* d);

int main()
{
    srand(time(NULL));
    std::cout << "Sumando Arreglos en Paralelo!\n";
    /*creacion de arreglos*/
    float a[N], b[N], c[N];
    int i = 0;
    
    /*ciclo para generar valores aleatorios en "a" y "b"*/
    for (i = 0; i < N; i++)
    {
        int random = rand() % 10;
        a[i] = i * random; 
        b[i] = (i + random) * 1.8; 
    }
    int pedazos = chunk; /*asignamos a la variable pedazos nuestro constante chunk para el tamaño de hilo*/

    /*programacion paralela, los arreglos a,b,c y pedazos comparten memoria mientras que constante i debe ser privada para evitar mezcla*/
#pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static,pedazos)
    /* Programacion paralela para ciclo for*/
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl; // Imprimir los primeros 10 valores del arreglo a
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl; // Imprimir los primeros 10 valores del arreglo b
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl; // Imprimir los primeros 10 valores del arreglo c
    imprimeArreglo(c);
}
/* funcion para imprimir los arreglos*/
void imprimeArreglo(float* d) 
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " , ";
    std::cout << std::endl;
}