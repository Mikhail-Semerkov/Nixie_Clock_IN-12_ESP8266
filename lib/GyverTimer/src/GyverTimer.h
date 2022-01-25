/*
    GTimer - полноценный таймер на базе системных millis() / micros()
    ВНИМАНИЕ, БИБЛИОТЕКА УСТАРЕЛА! ИСПОЛЬЗУЙ TimerMs https://github.com/GyverLibs/TimerMs
    Документация: https://alexgyver.ru/gyvertimer/
    GitHub: https://github.com/GyverLibs/GyverTimer
    Возможности:
    - Миллисекундный и микросекундный таймер
    - Два режима работы:
        - Режим интервала: таймер "срабатывает" каждый заданный интервал времени
        - Режим таймаута: таймер "срабатывает" один раз по истечении времени (до следующего перезапуска)
    - Служебные функции:
        - Старт
        - Стоп
        - Сброс
        - Продолжить
        
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    
    Версии:
    v2.0 - улучшенный алгоритм работы таймера
        - Кратные интервалы
        - Защита от пропусков
        - Защита от переполнения millis()
        - Убраны дефайны
    v2.1 - возвращены дефайны
    v2.2 - улучшена стабильность	
    v3.0
        - Логика работы разделена на интервал и таймаут
        - Добавлен общий класс GTimer (для миллисекундного и микросекундного таймера)
        - Добавлена возможность остановить и продолжить счёт таймера
    v3.2
        - Добавлен isEnabled
        - Возможность не запускать таймер при создании
*/

#ifndef GyverTimer_h
#define GyverTimer_h
#include <Arduino.h>
enum timerType {
    US,
    MS,
};

// ============== GTimer (микросекундный и миллисекундный таймер) ================
class GTimer {
public:
    GTimer(timerType type = MS, uint32_t interval = 0);	// объявление таймера с указанием типа и интервала (таймер не запущен, если не указывать)
    void setInterval(uint32_t interval);	// установка интервала работы таймера (также запустит и сбросит таймер) - режим интервала
    void setTimeout(uint32_t timeout);		// установка таймаута работы таймера (также запустит и сбросит таймер) - режим таймаута
    boolean isReady();						// возвращает true, когда пришло время
    boolean isEnabled();					// вернуть состояние таймера (остановлен/запущен)
    void reset();							// сброс таймера на установленный период работы
    void start();							// запустить/перезапустить (со сбросом счёта)
    void stop();							// остановить таймер (без сброса счёта)	
    void resume();							// продолжить (без сброса счёта)	
    
    // служебное
    void setMode(boolean mode);				// установка режима работы вручную: AUTO или MANUAL (TIMER_INTERVAL / TIMER_TIMEOUT)
    
private:
    uint32_t _timer = 0;
    uint32_t _interval = 0;
    uint32_t _resumeBuffer = 0;
    boolean _mode = true;
    boolean _state = false;
    boolean _type = true;
};

#define MANUAL 0
#define AUTO 1
#define TIMER_TIMEOUT 0
#define TIMER_INTERVAL 1


// ================================================================================
// ================== УСТАРЕЛО (но работает, для совместимости) ===================
// ================================================================================
class GTimer_ms {
public:
    GTimer_ms();							// объявление таймера (МИЛЛИСЕКУНДНЫЙ)
    GTimer_ms(uint32_t interval);			// объявление таймера с указанием интервала
    void setInterval(uint32_t interval);	// установка интервала работы таймера (также запустит таймер и сбросит период) - режим авто
    void setTimeout(uint32_t interval);		// установка таймаута работы таймера (также запустит таймер и сбросит период) - режим ручной
    void setMode(uint8_t mode);				// установка типа работы: AUTO или MANUAL (MANUAL нужно вручную сбрасывать reset или setInterval/setTimeout)
    boolean isReady();						// возвращает true, когда пришло время
    void reset();							// ручной сброс таймера на установленный период работы
    void stop();							// остановить таймер (без сброса счёта)
    void start();							// продолжить (без сброса счёта)
    
private:
    uint32_t _timer = 0;
    uint32_t _interval = 1000;
    boolean _mode = true;
    boolean _state = true;
};

class GTimer_us {
public:
    GTimer_us();							// объявление таймера (МИКРОСЕКУНДНЫЙ)
    GTimer_us(uint32_t interval);			// объявление таймера с указанием интервала
    void setInterval(uint32_t interval);	// установка интервала работы таймера (также запустит таймер и сбросит период) - режим авто
    void setTimeout(uint32_t interval);		// установка таймаута работы таймера (также запустит таймер и сбросит период) - режим ручной
    void setMode(uint8_t mode);				// установка типа работы: AUTO или MANUAL (MANUAL нужно вручную сбрасывать reset или setInterval/setTimeout)
    boolean isReady();						// возвращает true, когда пришло время
    void reset();							// ручной сброс таймера на установленный интервал
    void stop();							// остановить таймер (без сброса счёта)
    void start();							// продолжить (без сброса счёта)
    
private:
    uint32_t _timer = 0;
    uint32_t _interval = 1000;
    boolean _mode = true;
    boolean _state = true;
};
#endif