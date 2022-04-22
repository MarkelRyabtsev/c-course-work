#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include "constants.h"
#include "helper.h"


void print_student_info();
void do_task();
void fill_student_list(struct Student students[]);
int get_random_result();
struct Result ms_to_result(int milliseconds);
void sort_array(struct Student students[], int n);

int main() {
    setlocale(0, "Russian");
    srand(time(NULL));

    print_student_info();
    do_task();

    return 0;
}

void print_student_info() {
    printf("\n---------------------------------Курсовая работа (вариант %s)---------------------------------\n",
           STUDENT_VARIANT);
    printf("%s\n", STUDENT_NAME);
    printf("МИДО %s\n", STUDENT_GROUP);
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("Составить алгоритм и программу, в которой необходимо сформировать массив строк. В каждой строке\n"
           "записать фамилию студента и его результат в беге на 100 м (в сотых долях секунды). По результатам\n"
           "этих данных сформировать команду из четырех лучших бегунов для участия в эстафете 4 х 100 м.\n"
           "Результаты выполнения программы вывести на экран.\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    system("pause");
    printf("\n");
}

void do_task() {
    struct Student students[100];
    fill_student_list(students);
    for (int i = 0; i < 100; i++) {
        struct Result result = ms_to_result(students[i].result_ms);
        printf("%d) %s - %d сек %d мс\n", i + 1, students[i].name, result.seconds, result.milliseconds);
    }
    sort_array(students, 100);
    printf("-----------------------------------------Лучшие 4 студента----------------------------------------\n");
    for (int i = 0; i < 4; i++) {
        struct Result result = ms_to_result(students[i].result_ms);
        printf("%d) %s - %d сек %d мс\n", i + 1, students[i].name, result.seconds, result.milliseconds);
    }

    printf("\n");
}

void fill_student_list(struct Student students[100]) {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("student_names.txt", "r");
    int counter = 0;

    while(fgets(buffer, bufferLength, filePointer)) {
        buffer[strcspn(buffer, "\n")] = 0;
        struct Student student;
        student.result_ms = get_random_result();
        student.name = (char*)malloc(bufferLength);
        strcpy(student.name, buffer);

        students[counter] = student;
        counter++;
    }

    fclose(filePointer);
}

int get_random_result() {
    return (rand() % 6000) + 10000;
}

struct Result ms_to_result(int milliseconds) {
    int sec = milliseconds / 1000;
    int ms = milliseconds - 1000 * sec;
    struct Result result = { sec, ms };
    return result;
}

void sort_array(struct Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].result_ms > students[j + 1].result_ms) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}
