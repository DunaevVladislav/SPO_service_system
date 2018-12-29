#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <queue>
#include <vector>

using namespace std;

/**
 * Период времени в мс, через который может сформироваться новые заявки
 */
const int request_period = 100;

 /**
 * Стурктура описывающая заявку
 */
struct request{
    /**
     * Время начало обсулживания в мс с момента запуска системы
     */
    int start_time;

    /**
     * Время в мс, которое необходимо потратить на обслуживнаие заявка
     */
    int service_time;

    /**
     * Время в мс, которое уже было потрачено на обсуживания заявки
     */
    int spent_time;

    /**
     * Время в мс, когда заявка была обслуживана с момента запуска системы
     * -1 означает, что заявка еще не была обслужена
     */
    int close_time;

    /**
     * Приоритет (чем больше число, тем выше приоритет)
     */
    int priority;

    /**
     * Конструктор
     * @param start_time  время начало обсулживания в мс с момента запуска системы
     * @param service_time время в мс, которое необходимо потратить на обслуживнаие заявка
     * @param priority приоритет
     */
    request(const int &start_time, const int &service_time, const int &priority):
        start_time(start_time), service_time(service_time), spent_time(0), close_time(-1), priority(priority){};
};

/**
 * Количество очередей
 */
unsigned int queues_count;

/**
 * Очереди заявок
 * Массив очередей заявок
 */
queue<request*>** queues_request = nullptr;

/**
 * Поток заявок
 * Вектор всех созданных заявок
 */
vector<request*>* flow_request = nullptr;

/**
 * Инициализация очередей
 */
void initial_queues(){
    printf("Количество очередей: ");
    scanf("%u", &queues_count);
    queues_request = new queue<request*>*[queues_count];
    for(int i = 0; i < queues_count; ++i){
        queues_request[i] = new queue<request*>();
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

/**
 * Инициализация потока заявок
 */
void initial_flow(){
    flow_request = new vector<request*>();
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

/**
 * Гланая функция программы
 * Точка входа в программу
 * @return код возврата
 */
int main() {
    initial();

    finalize();
    return 0;
}