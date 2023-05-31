/*
EP1 MAC0210 PARTE 2
GRUPO:  Andre Nogueira Ribeiro nUSP: 12542230
        Matheus Sanches Jurgensen nUSP: 12542199
COMO COMPILAR: gcc -o parte2 parte2.c -lm -w
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double complex evalf (double complex x, int funcao) {
    /*
    Calcula o valor da função f(x) escolhida no ponto x
    */
    switch(funcao) {
        case 1:
            return (cpowf(x,4) - 1); // f1(x) = x⁴ - 1
        case 2:
            return (cpowf(x,3) - 1); // f2(x) = x³ - 1
        case 3:
            return (cpowf(x,3) - 2*cpowf(x,2) + 25*x - 50); // f3(x) = x³ - 2x² + 25x - 50
        case 4:
            return (cpowf(x,5) - 4*cpowf(x,4) + 10*cpowf(x,3) + cpowf(x,2) - 10); // f4(x) = x⁵ - 4x⁴ + 10x³ + x² - 10
        case 5:
            return (cpowf(x,6) - 1); // f5(x) = x⁶ - 1
    }
}

double complex evalDf (double complex x, int funcao) {
    /*
    Calcula o valor da derivada da função f(x) escolhida no ponto x
    */
    switch(funcao) {
        case 1:
            return (4*cpowf(x,3));
        case 2:
            return (3*cpowf(x,2));
        case 3:
            return (3*cpowf(x,2) - 4*x + 25);
        case 4:
            return (5*cpowf(x,4) - 16*cpowf(x,3) + 30*cpowf(x,2) + 2*x);
        case 5:
            return (6*cpowf(x,5));
    }
}

double complex newton (double complex x0, double atol, int funcao) {
    /*
    Aplica o método de Newton para achar uma raiz da função f (com primeira derivada f'), partindo do ponto x0.
    */
    complex anterior, df;
    complex xk = x0;
    int contador = 0;
    int convergiu = 1;
    do {
        anterior = xk;
        df = evalDf(anterior, funcao);
        if (creal(df) == 0 && cimag(df) == 0){ // derivada da função no ponto é zero, então não converge
            convergiu = 0;
            break;
        }
        xk = anterior - (evalf(anterior, funcao)/df);
        contador++;
    } while ((fabs(cabs(xk) - cabs(anterior)) > atol) && (contador < 500));
    if (contador >= 500 || convergiu == 0 || isnan(creal(xk))) {
        return(800); // caso em que não convergiu (800 não é raiz de nenhuma das funções implementadas)
    }
    return(xk); // convergiu
}

char *newton_basins (double* l, double* u, int p, double atol, int funcao) {
    /*
    Acha as bacias de convergência da função f no domínio [l1, u1] × [l2, u2] e retorna um arquivo output.txt que
    contém os dados para a geração da imagem das bacias. Os dados gerados preenchem uma imagem com p × p pixels.
    */
    double real, imag;
    double complex z, raiz;
    double tamr = u[0] - l[0];
    double tami = u[1] - l[1];
    double distr = tamr/p;
    double disti = tami/p;
    char *saida = "output.txt";
    FILE *dados = fopen(saida ,"w");
    for (int i = 0; i < p; i++) {
        real = l[0] + distr * i;
        for (int j = 0; j < p; j++) {
            imag = l[1] + disti * j;
            z = CMPLX(real, imag);
            raiz = newton(z, atol, funcao);
            fprintf(dados, "(%.10f,%.10f) (%.6f,%.6f)\n", real, imag, creal(raiz), cimag(raiz));
        }
    }
    fclose(dados);
    return saida;
}

void plot (char *end_dados) {
    int pid, status;
    FILE *arq_especificacao;
    char *especificacao = "/tmp/texto_especificacao";
    char *img_bacias = "bacias.png";
    arq_especificacao = fopen(especificacao, "a");
    char* aux = "%lf";
    fprintf(arq_especificacao,  "set term png size 1000, 1000\n"
                                "set output '%s'\n"
                                "plot \"%s\" using 2:1:(arg($3+$4*{0,1})) '(%s,%s) (%s,%s)' palette", img_bacias, end_dados, aux, aux, aux, aux);
    fclose(arq_especificacao);

    // chamada do execvp
    char *args[] = { "gnuplot", "-p -e", especificacao, NULL };
    if((pid = (fork())) < 0) {
        fprintf(stderr, "Erro de fork().\n");
        return;
    }
    else if(pid == 0) {
        if(execvp(*args, args) == -1) {
        fprintf(stderr, "Erro de execvp().\n");
        _exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
    remove(especificacao);
}

int main() {
    double atol = 1e-8;
    double l1, l2, u1, u2;
    int p;
    int funcao;
    printf("Qual o valor real mínimo a ser exibido? ");
    scanf("%lf", &l1);
    printf("Qual o valor imaginário mínimo a ser exibido? ");
    scanf("%lf", &l2);
    printf("\nQual o valor real máximo a ser exibido? ");
    scanf("%lf", &u1);
    printf("Qual o valor imaginário máximo a ser exibido? ");
    scanf("%lf", &u2);
    double l[2] = {l1, l2};
    double u[2] = {u1, u2};
    printf("\nA imagem gerada terá p x p pixels. Qual o valor de p? ");
    scanf("%d", &p);
    printf("\nAgora, qual das seguintes funções será analisada?\n");
    printf("1. f1(x) = x⁴ - 1\n2. f2(x) = x³ - 1\n3. f3(x) = x³ - 2x² + 25x - 50\n4. f4(x) = x⁵ - 4x⁴ + 10x³ + x² - 10\n5. f5(x) = x⁶ - 1\n");
    do {
        printf("\nSua escolha: ");
        scanf("%d", &funcao);
    } while (funcao != 1 && funcao != 2 && funcao != 3 && funcao != 4 && funcao != 5);
    char* output = newton_basins(l, u, p, atol, funcao);
    plot(output);
}