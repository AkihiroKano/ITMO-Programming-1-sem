#include <stdio.h>

int main() {
    int octal_number;

    scanf("%o", &octal_number);

    //Десятичная сс
    printf("to the decimal number system: %d \n", octal_number);

    // Шестнадцатиричная сс
    printf("to the hexadecimal number system: %x \n", octal_number);

    // Побитовый сдвиг на 4 вправо
    int shifted_number = octal_number >> 4;
    printf("to the hexadecimal number system and move to the left by 4: %x \n", shifted_number);

    // Побитовое отрицание
    int bitwise_negation = ~shifted_number;
    printf("bitwise negation in 16: %x \n", bitwise_negation);

    // Побитовый И для hexadecimal_number и octal_number
    int hexadecimal_number;
    scanf("%x", &hexadecimal_number);
    int answer = hexadecimal_number & octal_number;
    printf("bitwise and: %x", answer);
}
