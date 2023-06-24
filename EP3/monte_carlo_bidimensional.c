// EP3 - MAC0210 - monte_carlo_bidimensional.c
// Autor: Vítor Carvalho de Melo (nUSP 10723753)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// Verifica se o ponto (x,y) está inscrito no círculo
bool ponto_inscrito(double x, double y) {
    double dist = sqrt(pow(x, 2) + pow(y, 2));
    return dist <= 1;
}

double monte_carlo(int iteracoes) {
    double x, y, nInscrito = 0;

    for (int i=0; i<iteracoes; i++) {
        // a + rand/(b-a)
        x = -1 + (double)rand() / RAND_MAX * (1 - (-1));
        y = -1 + (double)rand() / RAND_MAX * (1 - (-1));
        nInscrito += ponto_inscrito(x, y);
    }

    return 4*(nInscrito/iteracoes);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc != 2 || !atoi(argv[1])) { 
        printf("Uso do script: ./monte_carlo_bidimensional {número de iterações}\n\n");
        exit(1);
    }

    printf("%lf\n", monte_carlo(atoi(argv[1])));
    
}