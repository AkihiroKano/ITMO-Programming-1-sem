// 1. Создать пустой текстовый файл, записать в него массив 10 строк, содержащих даты, увеличивающиеся на 1 день, начиная с сегодняшнего числа.
#include <stdio.h>
#include <time.h>

int main() {

    FILE *file = fopen("dates.txt", "w"); // открываем файл для записи
    if (file == NULL) {
        printf("ERROR\n");
        return 1;
    }

    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);

    char date_str[11]; // буфер для хранения даты
    strftime(date_str, sizeof(date_str), "%d-%m-%Y", current_time); // форматируем дату в строку
    fprintf(file, "%s\n", date_str); // записываем дату в файл

    for (int i = 1; i < 10; ++i) {
        ++current_time->tm_mday; // увеличиваем день на 1
        char date_str[11]; // буфер для хранения даты
        strftime(date_str, sizeof(date_str), "%d-%m-%Y", current_time); // форматируем дату в строку
        fprintf(file, "%s\n", date_str); // записываем дату в файл
    }

    fclose(file); // закрываем файл
    return 0;
}
