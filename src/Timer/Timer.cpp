#include "Timer.h"

Timer::Timer(bool isMillis)
: isMillis(isMillis)
{

}

void Timer::startTimer()
{
    timeBegin = getCurrentTime();
    timeNow = getCurrentTime();
}

void Timer::updateTimer()
{
    timeNow = getCurrentTime();
}

void Timer::resetBeginTime()
{
    timeBegin = getCurrentTime();
}

uint64_t Timer::getCurrentTime()
{
    if(isMillis)
        return millis();
    
    return micros();
}