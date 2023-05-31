// Para compilar, faça gcc -o fixed_point fixed_point.c -lm
#include <stdio.h>
#include <math.h>

double function_1 (double x) {
    return log(2) + 2*log(x);
}

double function_2 (double x) {
    return exp(x/2)/sqrt(2);
}

double function_3 (double x) {
    return x - ((exp(x) - 2*pow(x,2))/(exp(x) - 4*x));
}

double fixed_point (double x_0, double abs_err_tol, double max_iterations, double (*f)(double)) {
    double curr_x = x_0;
    double new_x = x_0;
    double diff = 0;
    for(int i = 0; i < max_iterations; i++) {
        new_x = f(curr_x);
        diff = new_x - curr_x;
        printf("\n Iteração %d:\n   X_i: %lf    Diff(X_i+1 - X_i): %lf\n", i, new_x, fabs(diff));
        if (fabs(diff) < abs_err_tol) {
            printf("\nValor de X encontrado após %d iterações: %lf\n\n", i, new_x);
            return new_x;
        }
        curr_x = new_x;
    }
    return -1;

}

int main(int argc, char *argv[]) {
    int n_func, max_iterations;
    double x_0, err_abs;
    printf("Escolha uma das funções para executar:\n\n 1:    g(x) = ln(2) + 2*ln(x) \n\n 2:    g(x) = exp(x/2) / sqrt(2) \n\n 3:    g(x) = x - ((exp(x) - 2*pow(x,2))/(exp(x) - 4*x)) \n\nNúmero da função escolhida: ");
    scanf("%d", &n_func);
    if (n_func < 1 || n_func > 3) {
        printf("\nPor favor escolha um número entre 1 e 3!\n");
        return -1;
    }
    printf("\nEscolha o ponto inicial x_0: ");
    scanf("%lf", &x_0);
    printf("\nErro absoluto máximo: ");
    scanf("%lf", &err_abs);
    printf("\nNúmero máximo de iterações: ");
    scanf("%d", &max_iterations);
    switch(n_func) {
        case 1:
            // Testar 2.1, 0.0000001, 100
            return fixed_point(x_0, err_abs, max_iterations, function_1);
        case 2:
            // Testar 1, 0.0000001, 100
            return fixed_point(x_0, err_abs, max_iterations, function_2);
        case 3:
            // Testar -0.5, 0.0000001, 100
            return fixed_point(x_0, err_abs, max_iterations, function_3);
    }
    
}