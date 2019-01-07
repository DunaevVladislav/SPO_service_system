///Заголовочный файл, описываюший константы приложения


/**
 * Среднее время между формированием двух заявок в мс
 */
const int REQUEST_PERIOD = 10;

/**
 * Квант времени в мс
 */
extern int QUANTUM_TIME;

/**
 * Минимальный приоритет заявки
 */
const int MIN_REQUEST_PRIORITY = 0;

/**
 * Максимальный приоритет заявки
 */
const int MAX_REQUEST_PRIORITY = 2;

/**
 * Минимальное время обслуживания заявки в мс
 */
const int MIN_SERVICE_TIME = 1;

/**
 * Максимальное время обслуживания заявки в мс
 */
const int MAX_SERVICE_TIME = 2000;