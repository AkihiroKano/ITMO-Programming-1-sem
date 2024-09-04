#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

    char *arr;
    int size;
    scanf("%d", &size);
    fflush(stdin);
    arr = (char *) malloc((size + 1) * sizeof(char));
    gets(arr); // То же самое что и scanf
    printf("\n");

    // Задание 1.

    printf("Task 1:\n");
    int digits = 0;
    int lowercase = 0;
    int uppercase = 0;

    for (int i = 0; i < size; i++) {
        if (isdigit(arr[i])) {
            digits++;
        } else if (islower(arr[i])) {
            lowercase++;
        } else if (isupper(arr[i])) {
            uppercase++;
        }
    }

    printf("digits: %d, lowercase: %d, uppercase: %d\n\n", digits, lowercase, uppercase);

    // Задание 3.
    printf("Task 3:\n");
    int num;
    scanf("%d", &num);
    fflush(stdin);

    switch (num) {
        case 0:
            printf("zero\n");
            break;
        case 1:
            printf("one\n");
            break;
        case 2:
            printf("two\n");
            break;
        case 3:
            printf("three\n");
            break;
        case 4:
            printf("four\n");
            break;
        case 5:
            printf("five\n");
            break;
        case 6:
            printf("six\n");
            break;
        case 7:
            printf("seven\n");
            break;
        case 8:
            printf("eight\n");
            break;
        case 9:
            printf("nine\n");
            break;
        default:
            printf("Invalid input\n");
    }

    free(arr);
}

/*// Альтернативное решение задания 3
    char *numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    if (num >= 0 && num <= 9) {
        printf("Numeral: %s\n", numbers[num]);
    } else {
        printf("Invalid input\n");
    }*/