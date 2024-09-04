#include <stdio.h>
#include <math.h>

int main() {

    double x;

    // Считываем данные с консоли и производим математические вычисления, после этого выводим
    scanf("%lf", &x);
    double z1 = (pow(x,2) + 2 * x - 3 + (x + 1) * sqrt(pow(x,2) - 9)) / (pow(x,2) - 2 * x - 3 + (x - 1) * sqrt(pow(x,2) - 9));
    printf("%lf\n", z1);

    // Считываем данные с консоли и производим математические вычисления, после этого выводим
    scanf("%lf", &x);
    double z2= sqrt((x+3)/(x-3));
    printf("%lf\n", z2);
}