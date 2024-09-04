#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// Функция для обращения байтов беззнакового целого числа
unsigned int ReverseBytes(unsigned int n) {
    // Меняем порядок байтов в беззнаковом целом числе
    return ((n >> 24) & 0x000000ff) |
           ((n >> 8) & 0x0000ff00) |
           ((n << 8) & 0x00ff0000) |
           ((n << 24) & 0xff000000);
}

// Объединение для представления заголовка тега в файле
typedef union TagHeader {
    char buffer[12];                  // Общий буфер из 12 байт
    struct {
        unsigned short empty;        // Поле пустое, 2 байта
        unsigned char version[3];    // Версия тега, 3 байта
        unsigned char v1;            // Версия тега (1 байт)
        unsigned char v2;            // Версия тега (1 байт)
        unsigned char flags;         // Флаги тега (1 байт)
        unsigned int size;           // Размер тега, 4 байта
    } data;
} header;

// Объединение для представления заголовка каждого кадра в файле
typedef union FrameHeader {
    char buffer[10];                  // Общий буфер из 10 байт
    struct {
        unsigned char name[4];        // Имя кадра, 4 байта
        unsigned int size;            // Размер кадра, 4 байта
        unsigned short flags;         // Флаги кадра, 2 байта
    } data;
} frame;

// Функция для копирования содержимого из одного файла в другой
void CopyFile(FILE *inp, FILE *outp) {
    // Цикл копирования символов из одного файла в другой
    int c;
    while ((c = getc(inp)) != EOF)
        // Получаем символ из входного файла и записываем его в выходной файл
        putc(c, outp);
}

// Функция для отображения содержимого файла
void ShowFile(char *fileName) {
    // Открываем файл для чтения в бинарном режиме
    FILE *file;
    file = fopen(fileName, "rb");

    // Проверяем, удалось ли открыть файл
    if (file == NULL) {
        printf("Read file error occurred!\n");
        return;
    }

    // Устанавливаем указатель в начало файла
    fseek(file, 0, SEEK_SET);

    // Считываем заголовок тега
    header tagHeader;
    fread(tagHeader.buffer + 2, sizeof(char), 10, file);

    // Получаем размер тега в обратном порядке байт
    unsigned int tagSize = ReverseBytes(tagHeader.data.size);

    // Выводим информацию о версии тега
    printf("%sv%d.%d\n", tagHeader.data.version,
           tagHeader.data.v1,
           tagHeader.data.v2);

    // Перебираем кадры в теге и выводим их содержимое
    while (ftell(file) < tagSize) {
        // Считываем заголовок кадра
        frame frameHeader;
        fread(frameHeader.buffer, sizeof(char), 10, file);

        // Если имя кадра пустое, завершаем цикл
        if (frameHeader.data.name[0] == 0)
            break;

        // Выводим имя кадра
        printf("%s: ", frameHeader.data.name);

        // Получаем размер кадра в обратном порядке байт
        unsigned int frameSize = ReverseBytes(frameHeader.data.size);

        // Выделяем память для содержимого кадра
        unsigned char *frameContent;
        frameContent = malloc(sizeof(char) * frameSize);

        // Считываем содержимое кадра
        fread(frameContent, sizeof(char), frameSize, file);

        // Выводим содержимое кадра
        for (int i = 0; i < frameSize; ++i) {
            printf("%c", frameContent[i]);
        }

        printf("\n");

        // Освобождаем память, выделенную для содержимого кадра
        free(frameContent);
    }

    // Закрываем файл
    fclose(file);
}

// Функция для получения и отображения содержимого конкретного кадра из файла
void GetFile(char *fileName, char frameName[4]) {
    // Открываем файл для чтения в бинарном режиме
    FILE *file;
    file = fopen(fileName, "rb");

    // Считываем заголовок тега
    header tagHeader;
    fread(tagHeader.buffer + 2, sizeof(char), 10, file);

    // Получаем размер тега в обратном порядке байт
    unsigned int tagSize = ReverseBytes(tagHeader.data.size);

    // Поиск кадра с указанным именем
    while (ftell(file) < tagSize) {
        // Считываем заголовок кадра
        frame frameHeader;
        fread(frameHeader.buffer, sizeof(char), 10, file);

        // Получаем размер кадра в обратном порядке байт
        unsigned int frameSize = ReverseBytes(frameHeader.data.size);

        // Если имя кадра совпадает с заданным, выводим его содержимое
        if (strcmp(frameHeader.data.name, frameName) == 0) {
            printf("%s: ", frameHeader.data.name);

            // Выделяем память для содержимого кадра
            unsigned char *frameContent;
            frameContent = malloc(sizeof(char) * frameSize);
            fread(frameContent, sizeof(char), frameSize, file);

            // Выводим содержимое кадра
            for (int i = 0; i < frameSize; ++i) {
                printf("%c", frameContent[i]);
            }
            printf("\n");

            // Освобождаем память и закрываем файл
            free(frameContent);
            fclose(file);
            return;
        }

        // Перемещаем указатель в файле к следующему кадру
        fseek(file, frameSize, SEEK_CUR);
    }

    // Закрываем файл и выводим сообщение, если кадр не был найден
    fclose(file);
    printf("No value found for %s!", frameName);
}

// Функция для установки содержимого конкретного кадра в файле
void SetFile(char *fileName, char frameName[4], char *frameValue) {
    // Открываем файл для чтения в бинарном режиме
    FILE *file;
    file = fopen(fileName, "rb");

    // Считываем заголовок тега
    header tagHeader;
    fread(tagHeader.buffer + 2, sizeof(char), 10, file);

    // Получаем размер тега в обратном порядке байт
    unsigned int tagSize = ReverseBytes(tagHeader.data.size);

    // Переменные для хранения старой позиции и размера кадра
    unsigned int oldFramePos = 0;
    unsigned int oldFrameSize = 0;

    // Поиск кадра с указанным именем
    while (ftell(file) < tagSize) {
        // Считываем заголовок кадра
        frame frameHeader;
        fread(frameHeader.buffer, sizeof(char), 10, file);

        // Получаем размер кадра в обратном порядке байт
        unsigned int frameSize = ReverseBytes(frameHeader.data.size);

        // Если имя кадра совпадает с заданным, сохраняем позицию и размер кадра
        if (strcmp(frameHeader.data.name, frameName) == 0) {
            oldFramePos = ftell(file) - 10;
            oldFrameSize = frameSize;
            break;
        }

        // Перемещаем указатель в файле к следующему кадру
        fseek(file, frameSize, SEEK_CUR);
    }

    // Получаем размер значения кадра
    unsigned int valueSize = strlen(frameValue);

    // Вычисляем новый размер тега
    unsigned int newTagSize = tagSize - oldFrameSize + valueSize + 10 * (oldFramePos != 0);

    // Если кадр не был найден, устанавливаем позицию
    if (oldFramePos == 0) {
        oldFramePos = ftell(file);
    }

    // Если размер значения равен 0, уменьшаем новый размер тега на 10 байт
    if (valueSize == 0) {
        newTagSize -= 10;
    }

    // Открываем временный файл для записи
    FILE *fileCopy;
    fileCopy = fopen("temp.mp3", "wb");

    // Устанавливаем позиции в начало файлов
    fseek(file, 0, SEEK_SET);
    fseek(fileCopy, 0, SEEK_SET);

    // Копируем содержимое файла во временный файл
    CopyFile(file, fileCopy);

    // Закрываем исходный файл
    fclose(file);
    // Закрываем временный файл
    fclose(fileCopy);

    // Открываем временный файл для чтения и исходный файл для записи
    fileCopy = fopen("temp.mp3", "rb");
    file = fopen(fileName, "wb");

    // Обновляем размер тега в заголовке
    tagHeader.data.size = ReverseBytes(newTagSize);
    fwrite(tagHeader.buffer + 2, sizeof(char), 10, file);

    // Устанавливаем позицию в начало копии файла после заголовка
    fseek(fileCopy, 10, SEEK_SET);

    // Копируем данные до старой позиции кадра
    for (int i = 0; i < oldFramePos - 10; ++i) {
        int c;
        c = getc(fileCopy);
        putc(c, file);
    }

    // Если размер значения больше 0, добавляем новый кадр
    if (valueSize > 0) {
        // Создаем заголовок нового кадра
        frame frameHeader;

        // Копируем имя кадра
        for (int i = 0; i < 4; ++i) {
            frameHeader.data.name[i] = frameName[i];
        }
        frameHeader.data.size = ReverseBytes(valueSize);
        frameHeader.data.flags = 0;

        // Записываем заголовок нового кадра
        fwrite(frameHeader.buffer, sizeof(char), 10, file);
    }

    // Записываем значение кадра
    fwrite(frameValue, sizeof(char), valueSize, file);

    // Устанавливаем позицию в копии файла после старого кадра
    fseek(fileCopy, oldFramePos + 10 + oldFrameSize, SEEK_SET);

    // Копируем оставшуюся часть данных
    for (int i = ftell(file); i < newTagSize; ++i) {
        unsigned short int c;
        c = getc(fileCopy);
        putc(c, file);
    }

    // Копируем остальные данные из временного файла
    CopyFile(fileCopy, file);

    // Закрываем исходный файл
    fclose(file);
    // Закрываем временный файл
    fclose(fileCopy);
    // Удаляем временный файл
    remove("temp.mp3");
}

int main() {
    // Инициализация переменных
    char string[200] = " ";  // Буфер для считывания строки
    int flag = 1;  // Флаг продолжения выполнения программы
    char *file_location;  // Указатель на строку с расположением файла
    char *number;  // Указатель на строку с числовым значением
    char *frame_name;  // Указатель на строку с именем кадра

    // Основной цикл
    while (flag) {
        // Чтение ввода пользователя
        scanf("%s", string);

        // Проверка команд пользователя
        if (strcmp(string, "stop") == 0) {
            // Если команда "stop", завершаем программу
            return 0;
        } else if (strcmp(string, "--show") == 0) {
            // Если команда "--show", отображаем содержимое файла
            ShowFile(file_location);
            return 1;
        } else if (strncmp("--get", string, 5) == 0) {
            // Если команда "--get", извлекаем имя кадра и вызываем функцию GetFile
            char *after_eq = strchr(string, '=') + 1;
            frame_name = (char *) malloc(sizeof(char) * strlen(after_eq));
            strcpy(frame_name, after_eq);
            GetFile(file_location, frame_name);
            free(frame_name);  // Освобождение памяти, выделенной под имя кадра
            return 1;
        } else if (strncmp("--set", string, 5) == 0) {
            // Если команда "--set", считываем имя кадра, проверяем наличие команды "--value",
            // и вызываем функцию SetFile с указанным именем кадра и значением
            printf("Read command set\n");
            char *after_eq = strchr(string, '=') + 1;
            frame_name = (char *) malloc(sizeof(char) * strlen(after_eq));
            strcpy(frame_name, after_eq);
            scanf("%s", string);

            if (strncmp("--value", string, 7) == 0) {
                printf("Read command value\n");
                char *after_eq = strchr(string, '=') + 1;
                number = (char *) malloc(sizeof(char) * strlen(after_eq));
                strcpy(number, after_eq);
                SetFile(file_location, frame_name, number);
                free(number);  // Освобождение памяти, выделенной под числовое значение
                free(frame_name);  // Освобождение памяти, выделенной под имя кадра
                return 1;
            } else {
                // Если команда "--value" не найдена, выводим ошибку и завершаем программу
                printf("Error\n");
                return 0;
            }
        } else if (strncmp("--filepath", string, 10) == 0) {
            // Если команда "--filepath", извлекаем расположение файла
            char *after_eq = strchr(string, '=') + 1;
            file_location = (char *) malloc(sizeof(char) * strlen(after_eq));
            strcpy(file_location, after_eq);
        }
    }
    // Освобождение выделенной памяти и завершение программы
    free(file_location);
}


//app.exe --filepath=files\file2.mp3 --show
//app.exe --filepath=files\file2.mp3 --get=TIT2
//app.exe --filepath=files\file2.mp3 --set=COMM --value=Test