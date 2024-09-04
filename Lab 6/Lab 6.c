#include <stdio.h>
#include <stdlib.h>

int main() {

    double *arr;

    // выделение памяти под массив из 4 элементов типа double
    arr = (double*)malloc(4*sizeof(double));
    arr[0] = -3.4;
    arr[1] = 4.5;
    arr[2] = -5.6;
    arr[3] = 6.7;

    // вывод значений массива на консоль с использованием указателя
    for (int i=0; i<4; i++) {
        printf("%d\t%.1lf\n", i, *(arr+i));
    }

    // Освобождение выделенной памяти
    free(arr);


    // выделение памяти под массив из 4 элементов типа double
    double *arr1 = (double*)malloc(4*sizeof(double));
    arr1[0] = -3.4;
    arr1[1] = 4.5;
    arr1[2] = -5.6;
    arr1[3] = 6.7;

    // вывод значений массива на консоль
    for (int i=0; i<4; i++) {
        printf("%d\t%.1lf\n", i, arr1[i]);
    }

    // Освобождение выделенной памяти
    free(arr1);
}