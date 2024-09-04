#include <stdio.h>

int main() {

    // Проверка входит ли число в диапазон от 21 до 45
    int number1;
    scanf("%d", &number1);

    int Matching_the_range = (number1 >= 21 && number1 <= 45);
    printf("%s \n", Matching_the_range ? "Yes" : "No");



// Проверка установлен ли бит на позции 16
    int number2;
    scanf("%d", &number2);
    int check = 1 << 16;

    if (number2 & check) {
        printf("bit 16 is set \n");
    } else {
        printf("bit 16 is not set \n");
    }
}


