#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    char *arr1, *arr2, *answer2, *answer6;
    int size1, size2, n_elements, answer9;
    scanf("%d %d\n", &size1, &size2);
    arr1 = (char *) malloc((size1 + 1) * sizeof(char));
    arr2 = (char *) malloc((size2 + 1) * sizeof(char));
    gets(arr1); // То же самое что и scanf
    gets(arr2);
    printf("\n");

    // Задание 2.
    printf("Task2:\n");
    scanf("%d", &n_elements);
    fflush(stdin);
    answer2 = (char *) malloc((size1 + n_elements + 1) * sizeof(char));
    strcpy(answer2, arr1); // Копия arr1
    strncat(answer2, arr2, n_elements); // Присоединение строки к строкке
    printf("Stacked lines: %s\n\n", answer2);

    // Задание 3.
    printf("Task 3:\n");
    if (strcmp(arr1, arr2) == 0) { // Сравнивает строки, 0 если одинаковые, возврат меньше нуля - первая строка меньше второй, возврат больше нуля - если первая строка больше второй
        printf("Comparison result: The lines are the same\n\n");
    } else {
        printf("Comparison result: The lines are different\n\n");
    }

    // Задание 6.
    printf("Task 6:\n");
    scanf("%d", &n_elements);
    fflush(stdin);
    answer6 = (char *) malloc((n_elements) * sizeof(char));

    strncpy(answer6, arr1, n_elements); // Копия
    answer6[n_elements] = '\0';
    printf("Copy n characters: %s\n\n", answer6);

    // Задание 9.
    printf("Task 9:\n");
    char ch;
    scanf("%c", &ch);
    fflush(stdin);
    char *index = strrchr(arr1, ch); //поиск правого вхождения
    answer9 = index - arr1;
    printf("Symbol index: %d\n\n", answer9);

    // Задание 12.
    printf("Task 12:\n");
    int max = 0;
    int counter = 0;
    for (int i = 0; i < size1; ++i) {
        counter++;
        for (int j = 0; j < size2; ++j) {
            if (arr1[i] == arr2[j]) {
                counter = 0;
                break;
            }
        }
        if (max < counter) {
            max = counter;
        }
    }
    printf("%d", max);

    free(arr1);
    free(arr2);
    free(answer2);
    free(answer6);
}