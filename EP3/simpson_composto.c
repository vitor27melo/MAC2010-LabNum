// EP3 - MAC0210 - simpson_composto.c
// Autor: Vítor Carvalho de Melo (nUSP 10723753)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Calcula, o valor de p(x) pelo polinômio descrito no relatório
long double lagrange_pol(double x) {
    long double y = -
        ((long double) 22963    / (long double) 56250000000 )*pow(x, 6) -
        ((long double) 4801     / (long double) 937500000   )*pow(x, 5) +
        ((long double) 9823     / (long double) 4500000     )*pow(x, 4) - 
        ((long double) 1170289  / (long double) 15000000    )*pow(x, 3) +
        ((long double) 84136223 / (long double) 90000000    )*pow(x, 2) -
        ((long double) 8058593  / (long double) 3000000     )*pow(x, 1);
    return y;
}

long double calcula_integral(double h){
    // Calcula, p/ uma distância h, o número de pontos que deverão ser calculados
    int n_pontos = floor(30/h) + 1;
    long double result = 0;

    // Calcula os n_pontos do intervalo [0, 30]
    float pontos[n_pontos];
    for (int i=0; i<n_pontos; i++) {
        pontos[i] = i*h;
    }
    
    result = lagrange_pol(pontos[0]);
    if (n_pontos > 2) {
        for (int i=1; i<=floor(((n_pontos-1)/2)) -1; i++) {
            result += 2*lagrange_pol(pontos[2*i]);
        }
        for (int i=1; i<=floor((n_pontos-1)/2); i++) {
            result += 4*lagrange_pol(pontos[(2*i)-1]);
        }
    }
    result += lagrange_pol(30);
    printf("n pontos %d\n", n_pontos);
    return (h*result)/3;
}

int main(int argc, char **argv) {
   if (argc != 2 || !atof(argv[1]) || atof(argv[1]) > 30 || atof(argv[1]) < 0) { 
        printf("Uso do script: ./simpson_composto {0 < h <= 30}\n\n");
        exit(1);
    }

    printf("%LG", calcula_integral(atof(argv[1])));
   return 0;
}