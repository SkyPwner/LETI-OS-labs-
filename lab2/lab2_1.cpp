#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

using namespace std;

int flag1 = 0; // объявление флагов завершения потоков
int flag2 = 0; 
sem_t semaphoreID; // объявляем идентификатор семафора

void* proc1(void* array1) {
    char* array = (char*)array1;

    while (flag1 != 1){
        sem_wait(&semaphoreID); // вход в критический участок
        for (int i = 0; i < strlen(array); i++){
            cout << array[i] << flush;
            sleep(1);
        }
        cout << endl;
        sem_post(&semaphoreID); // выход из критического участка
        sleep(2);
    }
    void* returned_value = NULL;
    return returned_value;
}

void* proc2(void* array2) {
    char* array = (char*)array2;

    while (flag2 != 1){
        sem_wait(&semaphoreID); // вход в критический участок 
        for (int i = 0; i < strlen(array); i++){
            cout << array[i] << flush;
            sleep(1)
        }
        cout << endl;
        sem_post(&semaphoreID); // выход из критического участка
        sleep(2);
    }
    void* returned_value = NULL;
    return returned_value; 
}

int main(){
    pthread_t id1; // Объявление идентификатора потоков
    pthread_t id2; 

    sem_init(&semaphoreID, false, 1);

    char array_1[] = {"98\0"};
    char array_2[] = {"94\0"};

    pthread_create (&id1 , NULL , proc1 , &array_1); // Создание потока
    pthread_create (&id2 , NULL , proc2 , &array_2); 

    getchar();
    
    flag1 = 1; // Установка флага завершения потоков
    flag2 = 1; 

    pthread_join(id1, NULL); // Ожидание завершения потоков
    pthread_join(id2, NULL); 

    sem_destroy(&semaphoreID);
}