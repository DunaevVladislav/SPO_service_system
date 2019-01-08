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

/**
 * Выводит информаицию о потоке
 */
void output_flow();

/**
 * Начать формирование потока заявок
 * @param функция добавления новой заявки
 */
void start_generate_request(void (*_adding_function)());

/**
 * Начать формирование потока заявок
 */
void stop_generate_request();

/**
 * Продолжить формирование потока заявок
 */
void resume_generate_request();