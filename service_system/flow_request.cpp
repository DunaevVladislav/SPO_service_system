///Файл с реализацией функций для работы с потоком заявок

#include "flow_request.h"
#include "constants.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>

/**
 * Поток заявок
 * Вектор всех созданных заявок
 */
std::vector<request*>* flow_request = nullptr;

/**
 * Инициализация потока заявок
 */
void initial_flow(){
    flow_request = new std::vector<request*>();
}

/**
 * Завершиьт функцию _gen_flow_function
 */
bool break_flow = false;

std::thread* _flow_thread = nullptr;

/**
 * Освобождение памяти использованной для формирования потока
 */
void finalize_flow(){
    break_flow = true;
    _flow_thread->join();
    for (auto &req : *flow_request) {
        delete req;
        req = nullptr;
    }
    delete flow_request;
    flow_request = nullptr;
}

/**
 * Добавить заявку в поток заявок
 * @param new_request добавляемая заявка
 */
void add_to_flow(request*& new_request){
    flow_request->push_back(new_request);
}

/**
 * Выводит информаицию о потоке
 */
void output_flow(){
    if (flow_request->size() < 50) system("clear");
    puts("Список заявок:\n");
    printf("%-5s %-20s %-35s %-35s %-25s %-35s\n", "id", "Время", "Время необходимое", "Время потраченное", "Приоритет", "Обсужена ли");
    printf("%-5s %-23s %-33s %-33s %-16s %-22s\n", "", "создания", "на обслуживание", "на обслуживание", "", "заявка?");
    for (auto &req : *flow_request) {
        printf("%-5d %-15d %-19d %-19d %-16d %-18s\n", req->id, req->start_time, req->service_time, req->spent_time, req->priority, req->close_time == -1?"Нет":"Да");
    }
}

/**
 * Остановлено ли формирование потока заявок
 */
bool stop = false;

/**
 * Функция генерации потока заявок
 * @param функция добавления новой заявки
 */
void _gen_flow_function(void (*_adding_function)()){
    while(!break_flow){
        if (!stop)
            for(int i = 2; rand()%i == 0; i <<= 1) _adding_function();
        usleep(1000LL*REQUEST_PERIOD);
    }
}

/**
 * Начать формирование потока заявок
 * @param функция добавления новой заявки
 */
void start_generate_request(void (*_adding_function)()){
    _flow_thread = new std::thread(_gen_flow_function, _adding_function);
}

/**
 * Начать формирование потока заявок
 */
void stop_generate_request(){
    stop = true;
}

/**
 * Продолжить формирование потока заявок
 */
void resume_generate_request(){
    stop = false;
}