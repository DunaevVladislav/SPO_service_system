///Файл с реализацией функций для работы с потоком заявок

#include "flow_request.h"
#include "request.h"
#include <vector>


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