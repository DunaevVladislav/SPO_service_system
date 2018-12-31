///Заголовочный файл описывающий функции и структуры для работы с потоком заявок

#pragma once
#include "request.h"

/**
 * Инициализация потока заявок
 */
void initial_flow();

/**
 * Освобождение памяти использованной для формирования потока
 */
void finalize_flow();

/**
 * Добавить заявку в поток заявок
 * @param new_request добавляемая заявка
 */
void add_to_flow(request*& new_request);