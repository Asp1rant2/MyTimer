#include <iostream>
#include "mytimer.h"
#include <chrono>
#include <functional>

using namespace std;

void printWorld() {
    cout << "world" << endl;
}

class Router{
public:
    void countSelf() {
        cout << "Count is " << count << endl;
        count++;
    }

    Router(){
        count = 0;
        id = TimerService::setTimer(1000, std::bind(&Router::countSelf, this));
    }
    ~Router() {
        TimerService::killTimer(id);
    }

private:
    unsigned int count;
    unsigned long id;
};

int main()
{
    auto l1 = TimerService::setTimer(1000, [](){cout << "hello" << endl;});
    auto l2 = TimerService::setTimer(1000, std::bind(printWorld));
    Router *r = new Router;

    std::this_thread::sleep_for(std::chrono::seconds(3));
    TimerService::killTimer(l2);
    delete r;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
