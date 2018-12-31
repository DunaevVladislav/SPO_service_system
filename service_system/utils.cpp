///Файл с реализацией основных функций пртиложения

#include "utils.h"
#include "flow_request.h"
#include "queues.h"


/**
 * Инициализация
 */
void initial(){
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