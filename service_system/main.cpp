#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utils.h"
using namespace std;


/**
 * Гланая функция программы
 * Точка входа в программу
 * @return код возврата
 */
int main() {
    initial();
    add_request();
    finalize();
    return 0;
}