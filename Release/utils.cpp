///Файл с реализацией основных функций пртиложения

#include "utils.h"
#include "flow_request.h"
#include "queues.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <termios.h>
#include <signal.h>

using namespace std;

/**
 * Время начало работы приложения
 */
chrono::time_point<chrono::system_clock> start_time;

/**
 * Квант времени в мс
 */
int QUANTUM_TIME = 10;

/**
 * Инициализация кванта времени
 */
void _initial_quantun(){
    printf("Квант времени: ");
    scanf("%d", &QUANTUM_TIME);
}

/**
 * Инициализация
 */
void initial(){
    start_time = chrono::system_clock::now();
    srand(time(0));
    _initial_quantun();
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

void output_menu(){
    puts("\nНажмите 1, чтобы прекратить генерацию заявок");
    puts("Нажмите 2, чтобы завершить работу программы");
}

/**
 * Был ли нажаты ctrl+c
 */
bool was_input = false;

/**
 * Обработчик сигнала завершения программы
 */
void signal_handler(int)
{
    was_input = true;
}

/**
 * Функция для управления программой
 */
void control(){
    start_generate_request(&add_request);
    start_service();
    signal(SIGINT, signal_handler);
    while(1){
        output_flow();
        output_queues();
        puts("Нажите ctrl+c чтобы остановить программу");
        usleep(1000LL * 100);
        if (was_input){
            stop_generate_request();
            stop_service();
            output_menu();
            int num;
            scanf("%d", &num);
            was_input = false;
            switch (num){
                case 1:{
                    start_service();
                    continue;
                }
                case 2:{
                    return;
                }
                default:
                    resume_generate_request();
                    start_service();
                    continue;
            }
        }

    }
}