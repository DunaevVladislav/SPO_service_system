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
    request(int start_time, int service_time, int priority):
        start_time(start_time), service_time(service_time), spent_time(0), close_time(-1), priority(priority){};
};

int main() {

    return 0;
}