///Файл с реализацией функций для работы с очередями заявок

#include "queues.h"
#include "request.h"
#include <queue>
#include <stdio.h>


/**
 * Количество очередей
 */
unsigned int queues_count;

/**
 * Очереди заявок
 * Массив очередей заявок
 */
std::queue<request*>** queues_request = nullptr;

/**
 * Инициализация очередей
 */
void initial_queues(){
    printf("Количество очередей: ");
    scanf("%u", &queues_count);
    queues_request = new std::queue<request*>*[queues_count];
    for(int i = 0; i < queues_count; ++i){
        queues_request[i] = new std::queue<request*>();
    }
}

/**
 * Освобождние памяти использованной для формирования очередей
 */
void finalize_queues(){
    for(int i = 0; i < queues_count; ++i){
        delete queues_request[i];
        queues_request[i] = nullptr;
    }
    delete[] queues_request;
    queues_request = nullptr;
}