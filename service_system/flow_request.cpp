///Файл с реализацией функций для работы с потоком заявок

#include "flow_request.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

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
 * Освобождение памяти использованной для формирования потока
 */
void finalize_flow(){
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
    system("clear");
    puts("Список заявок:\n");
    printf("%-20s %-35s %-35s %-25s %-35s\n", "Время", "Время необходимое", "Время потраченное", "Приоритет", "Обсужена ли");
    printf("%-23s %-33s %-33s %-16s %-22s\n", "создания", "на обслуживание", "на обслуживание", "", "заявка?");
    for (auto &req : *flow_request) {
        printf("%-15d %-19d %-19d %-16d %-18s\n", req->start_time, req->service_time, req->spent_time, req->priority, req->close_time == -1?"Нет":"Да");
    }
}