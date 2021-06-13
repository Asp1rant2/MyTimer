#ifndef MYTIMER_H
#define MYTIMER_H

#include <functional>
#include <atomic>
#include <future>

typedef std::function<void()> TimerFunc;

#define TIMER_ID unsigned long
#define INTERVAL unsigned int

class MyTimer{
public:
    MyTimer(TIMER_ID _id, INTERVAL _interval, TimerFunc _func);
    void stopTimer();
    void startTimer();
    ~MyTimer();
private:
    TIMER_ID m_id;
    INTERVAL m_interval;
    bool m_stop;
    TimerFunc m_func;
    std::future<int> m_future;
};

class TimerService
{
public:
    static TIMER_ID setTimer(INTERVAL _interval, TimerFunc _func);
    static void killTimer(TIMER_ID _id);
};

#endif // MYTIMER_H
