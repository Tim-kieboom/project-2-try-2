#include "Timer.h"

Timer::Timer(bool isMillis)
: isMillis(isMillis)
{
    startTimer();
}

void Timer::startTimer()
{
    timeBegin = getCurrentTime();
    timeNow   = getCurrentTime();
}

bool Timer::waitTime(uint32_t time)
{
    updateTimer();
    
    if(timeNow - timeBegin > time)
    {
        resetBeginTime();
        return true;
    }

    return false;
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