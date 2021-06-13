#include "mytimer.h"
#include <unordered_map>
#include <chrono>
#include <thread>

std::unordered_map<TIMER_ID, MyTimer*> TimerMap;
std::mutex g_mutex;

static TIMER_ID NewTimerID = 0;

TIMER_ID TimerService::setTimer(INTERVAL _interval, TimerFunc _func){
    MyTimer* pTimer = new MyTimer(NewTimerID, _interval, _func);
    TimerMap[NewTimerID] = pTimer;
    pTimer->startTimer();
    return NewTimerID++;
}

void TimerService::killTimer(unsigned long _id)
{
    MyTimer* pTimer = TimerMap.at(_id);
    if (pTimer){
        pTimer->stopTimer();
        delete pTimer;
        TimerMap.erase(_id);
    }
}

MyTimer::MyTimer(unsigned long _id, unsigned int _interval, TimerFunc _func)
{
    m_id = _id;
    m_interval = _interval;
    m_func = _func;
    m_stop = false;
}

void MyTimer::startTimer()
{
    m_future = std::async(std::launch::async, [this](){
        while(true){
            if(m_stop)
                break;
            std::this_thread::sleep_for(std::chrono::milliseconds(m_interval));
            std::lock_guard<std::mutex> lock(g_mutex);
            m_func();
        }
        return 0;
    });
}

void MyTimer::stopTimer()
{
    m_stop = true;
    m_future.wait();
}

MyTimer::~MyTimer()
{

}
