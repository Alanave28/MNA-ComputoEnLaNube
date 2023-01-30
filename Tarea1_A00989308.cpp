#include <omp.h>
#include <iostream>

#define N 20
#define chunk 4
#define mostrar 5
#define numHilos 2

void imprimeArreglo(float *d);


int main(){

    std::cout << "Sumando Arreglos en paralelo!!\n";
    // Creamos los arreglos con el número de espacios establecido en las inicializaciones anteriores
    float a[N], b[N], c[N];
    int i;

    for(i = 0; i < N; i++){
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;

    //Se define el num de hilos a utilizar
    omp_set_num_threads(numHilos);
    int hId = 0;

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for(i = 0; i < N; i++){
        hId = omp_get_thread_num();
        std::cout << "La suma de los arreglos en la posición c["<< i <<"] es aplicado por el hilo: " << hId << std::endl;
        c[i] = a[i] + b[i];
    }

    std::cout << "Imprimiendo los primeros " << mostrar << "valores del arreglo a: " << std::endl;
    imprimeArreglo(a);   
    std::cout << "Imprimiendo los primeros " << mostrar << "valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << "valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

}

void imprimeArreglo(float *d){
    for(int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    
    std::cout << std::endl;
}
