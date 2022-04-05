#include <iostream>
#include <windows.h>

class Timer
{
private:
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;

public:
    Timer(){};
    void Start()
    {
        QueryPerformanceCounter(&nBeginTime);
    }
    void End()
    {
        QueryPerformanceCounter(&nEndTime);
    }
    //获取微秒为单位的时间，精度为10^-6s
    double getTime()
    {
        QueryPerformanceFrequency(&nFreq);
        double dDuration = 1000000 * (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
        return dDuration;
    }
} Timer;