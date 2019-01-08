///Файл с реализацией функций для работы с очередями заявок

#include "queues.h"
#include "constants.h"
#include <list>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

/**
 * Количество очередей
 */
unsigned int queues_count;

/**
 * Очереди заявок
 * Массив очередей заявок
 */
std::list<request*>** queues_request = nullptr;

/**
 * Обслужить заявку (в течение одного кванта)
 */
void _service_request(int){
    int index_req_max_prior;
    for(index_req_max_prior = 0; index_req_max_prior < queues_count; ++index_req_max_prior){
        if (!queues_request[index_req_max_prior]->empty()) break;
    }
    if (index_req_max_prior == queues_count) return;
    for(int i = 1; i < queues_count; ++i){
        if (queues_request[i]->empty()) continue;
        if (queues_request[i]->front()->priority > queues_request[index_req_max_prior]->front()->priority)
            index_req_max_prior = i;
    }
    request*& handled_request = queues_request[index_req_max_prior]->front();
    queues_request[index_req_max_prior]->pop_front();
    handled_request->spent_time += QUANTUM_TIME;
    if (handled_request->spent_time >= handled_request->service_time){
        close_request(handled_request);
    }else{
        add_to_queue(handled_request);
    }
}

/**
 * Инициализация очередей
 */
void initial_queues(){
    printf("Количество очередей: ");
    scanf("%u", &queues_count);
    queues_request = new std::list<request*>*[queues_count];
    for(int i = 0; i < queues_count; ++i){
        queues_request[i] = new std::list<request*>();
    }
    signal(SIGALRM, _service_request);
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
 * Добавить заявку в очереди
 * Заявка добавляем в очередь с наименьшим числом заявок
 * @param new_request Добавляемая заявка
 */
void add_to_queue(request *&new_request) {
    int index_queue_min_size = 0;
    for(int i = 1; i < queues_count; ++i){
        if (queues_request[i]->size() < queues_request[index_queue_min_size]->size())
            index_queue_min_size = i;
    }
    queues_request[index_queue_min_size]->push_back(new_request);
}

/**
 * Запустить обслуживание заявок
 */
void start_service(){
    struct itimerval tval = {0,  1000LL*QUANTUM_TIME, 0 , 1000LL*QUANTUM_TIME};
    setitimer(ITIMER_REAL, &tval, nullptr);
}

/**
 * Остановить обслуживание заявок
 */
void stop_service(){
    struct itimerval tval = {0 , 0 , 0 , 0};
    setitimer(ITIMER_REAL, &tval, nullptr);
}

/**
 * Вывести информацию об очередях
 */
void output_queues(){
    puts("Очередь: id заявок");
    for(int i = 0; i < queues_count; ++i){
        printf("№%d: ", i + 1);
        for(request*& req:*queues_request[i]){
            printf("%d ", req->id);
        }
        puts("");
    }
}
