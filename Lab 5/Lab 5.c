#include <stdio.h>

int main() {
    int arr[] = {34, 45, 56, 67, 78, 89};
    int size = sizeof(arr) / sizeof(int);
    // Выводим значения массива
    for (int i = 0; i < size; ++i) {
        printf("%d\t%d\n", i, arr);
    }



    int matrix1[2][2] = {{2, 1},{ 1, 3 }};
    int matrix2[2][2] = {{1, 2},{ 3, 1 }};

    printf("\n");

    // Инициализируем элементы результирующей матрицы нулями
    int answer[2][2]= {0};

    // Вычисляем значения элементов результирующей матрицы
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                answer[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Выводим значения элементов результирующей матрицы
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d \t", answer[i][j]);
        }
        printf("\n");
    }
}
