#include <stdio.h>

float data_matrix[][2] = {
    {0.0, 0.0},
    {5.0, 1.5297},
    {10.0, 9.5120},
    {15.0, 8.7025},
    {20.0, 2.8087},
    {25.0, 1.0881},
    {30.0, 0.3537}
};

float calcula_integral(){
    int h = 5;
    float result = 0;
    result = data_matrix[0][1]; // f(x_0)
    for (int i=1; i<=2; i++) {
        result += 2*data_matrix[2*i][1];
    }
    for (int i=1; i<=3; i++) {
        result += 4*data_matrix[(2*i)-1][1];
    }
    result += data_matrix[6][1]; // f(x_6)
    return (h*result)/3;
}

int main() {
   printf("\n%f", calcula_integral());
   return 0;
}