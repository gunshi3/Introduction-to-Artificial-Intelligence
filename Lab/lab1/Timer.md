# Timer.h

```cpp
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
    //��ȡ΢��Ϊ��λ��ʱ�䣬����Ϊ10^-6s
    double getTime()
    {
        QueryPerformanceFrequency(&nFreq);
        double dDuration = 1000000 * (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
        return dDuration;
    }
} Timer;
```
