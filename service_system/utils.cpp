///Файл с реализацией основных функций пртиложения

#include "utils.h"
#include "flow_request.h"
#include "queues.h"
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

/**
 * Время начало работы приложения
 */
chrono::time_point<chrono::system_clock> start_time;

/**
 * Инициализация
 */
void initial(){
    start_time = chrono::system_clock::now();
    srand(time(0));
    initial_flow();
    initial_queues();
}

/**
 * Освобождение памяти
 */
void finalize(){
    finalize_queues();
    finalize_flow();
}

/**
 * Получить время прошедшое с начало работы приложения в мс
 * @return Время, которое прошло с начала работы приложения в мс
 */
int past_time(){
    return (int)chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now()-start_time).count();
}

/**
 * Создать и добавить заявку в поток и очередь
 */
void add_request(){
    request* new_request = create_random_request(past_time());
    add_to_flow(new_request);
    add_to_queue(new_request);
}