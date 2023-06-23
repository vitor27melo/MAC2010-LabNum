// EP3 - MAC0210 - monte_carlo_unidimensional.c
// Autor: Vítor Carvalho de Melo (nUSP 10723753)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef double (*funcao)(double);

double f1 (double x) {
    return sin(x);
}

double f2 (double x) {
    return pow(x, 3);
}

double f3(double x) {
    return exp(-1*x);
}

double monte_carlo(int iteracoes, double a, double b, funcao func) {
    double nRand, soma = 0;
    
    for (int i=0; i<iteracoes; i++) {
        nRand = a + ((double)rand() / RAND_MAX * (b-a));
        soma += func(nRand);
    }

    return (b-a)*(soma/iteracoes);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc != 3 || !atoi(argv[1]) || !atoi(argv[2])) { 
        printf("Uso do script: ./monte_carlo_unidimensional {número da função} {número de iterações}\n\n");
        printf("Número da função: \n   1: sin(x)\n   2: x^3\n   3: e^-x\n");
        exit(1);
    }

    switch(atoi(argv[1])) {
        case 1:
            printf("%lf\n", monte_carlo(atoi(argv[2]), 0, 1, &f1));
            break;
        case 2:
            printf("%lf\n", monte_carlo(atoi(argv[2]), 3, 7, &f2));
            break;
        case 3:
            printf("%lf\n", monte_carlo(atoi(argv[2]), 0, 10000000, &f3));
            break;
    }
}