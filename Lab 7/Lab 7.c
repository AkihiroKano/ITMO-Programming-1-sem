#include <stdio.h>
// #define - используется для создания макросов. Макросы позволяют задавать сокращенные имена для фрагментов кода, которые будут заменены на соответствующий текст в процессе компиляции.

// Определение перечисления типов печати
enum PrintType {
    Book, Magazine, Newspaper, Brochure
};

// Определение структуры круга
struct Circle {
    float x; // координата X центра круга
    float y; // координата Y центра круга
    float r; // радиус круга
};

// Функция для расчета площади круга
float circleArea(struct Circle circle) {
    return 3.14 * circle.r * circle.r;
}

// Функция для расчета периметра круга
float circlePerimeter(struct Circle circle) {
    return 2 * 3.14 * circle.r;
}

// Определение битовых полей элементов приборов
typedef union {
    struct {
        unsigned int num_lock : 1;
        unsigned int caps_lock : 1;
        unsigned int scroll_lock : 1;
        unsigned int reserved : 13;
    } keyboard;
    // можно добавить определения для других приборов, если необходимо
} device_condition;

int main() {
    // Блок 1: Работа с перечислением типов печати
    enum PrintType printType = Newspaper;
    printf( "%d\n", printType);

    // Блок 2: Работа с кругом
    struct Circle circle = {0, 0, 5};
    printf("Perimeter of Circle = %f\n", circlePerimeter(circle));
    printf("Area of Circle = %f\n", circleArea(circle));

    // Блок 3: Работа с битовыми полями
    unsigned int number;
    printf("Enter a hex number: ");
    scanf("%x", &number);

    // Проверяем установку битов
    device_condition condition;
    condition.keyboard.num_lock = (number & 0x1);
    condition.keyboard.caps_lock = (number & 0x2) >> 1;
    condition.keyboard.scroll_lock = (number & 0x4) >> 2;

    printf("NumLock: %d\n", condition.keyboard.num_lock);
    printf("CapsLock: %d\n", condition.keyboard.caps_lock);
    printf("ScrollLock: %d\n", condition.keyboard.scroll_lock);
}
