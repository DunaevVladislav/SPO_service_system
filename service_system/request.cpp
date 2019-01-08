///Файл описывающий реализацию функций для работы с заявками

#include "request.h"
#include "utils.h"
#include "constants.h"
#include <stdlib.h>

/**
 * Последний неиспользованный id
 */
unsigned int _not_used_id = 0;

/**
 * Создать заявку со случайными параметрами
 * @param current_time
 * @return
 */
request *create_random_request(const int &current_time) {
    int priority = rand()%(MAX_REQUEST_PRIORITY - MIN_REQUEST_PRIORITY + 1) + MIN_REQUEST_PRIORITY;
    int service_time = rand()%(MAX_SERVICE_TIME - MIN_SERVICE_TIME + 1) + MIN_SERVICE_TIME;
    return new request(current_time, service_time, priority);
}

/**
 * Закрывает заявку
 * @param closing_request закрываемая заявка
 */
void close_request(request*& closing_request){
    closing_request->service_time = closing_request->spent_time;
    closing_request->close_time = past_time();
}