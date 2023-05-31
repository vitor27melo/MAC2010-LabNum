#include <stdio.h>
#include <math.h>

double function_1 (double x) {
    return pow(x, 4) - 1;
}

double function_1_derivative (double x) {
    return 4*pow(x, 3);
}

double eval(double x, double (*f)(double)) {
    return f(x);
}

double evalDf(double x, double (*f)(double)) {
    return f(x);
}

int main() {

}