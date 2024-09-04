#include <stdio.h>
#include <stdlib.h>

// Функция для нахождения НОД
int GCD(int a, int b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

// Функция для нахождения НОК
int LCM(int a, int b) {
    return (a * b) / GCD(a, b);
}

// Функция разбияния числа на цифры
int *digitsArray(int arr, int *len) {
    int temp = arr;
    int count = 0;

    while (temp != 0) {
        temp /= 10;
        count++;
    }

    int *n_arr = (int *) malloc(count * sizeof(int));

    temp = arr;
    *len = count;

    for (int i = count - 1; i >= 0; --i) {
        n_arr[i] = temp % 10;
        temp /= 10;
    }

    return n_arr;
}

int main() {

    // Задание 1.
    int num1, num2;
    int gcd, lcm; // nod and nok
    printf("Task 1:\n");
    scanf("%d %d", &num1, &num2);
    fflush(stdin);

    // Находим НОД и НОК
    gcd = GCD(num1, num2);
    lcm = LCM(num1, num2);

    printf("NOD %d and %d: %d\n\n", num1, num2, gcd);
    printf("NOK %d and %d: %d\n\n", num1, num2, lcm);

    // Задание 3.
    int arr, len;
    printf("Task 3:\n");
    scanf("%d", &arr);
    fflush(stdin);


    int *n_arr = digitsArray(arr, &len);

    printf("Digits of %d: ", arr);
    for (int i = 0; i < len; i++) {
        printf("%d ", n_arr[i]);
    }
    printf("\n");

    free(n_arr);
}