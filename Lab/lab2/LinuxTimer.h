#include<iostream>
#include <sys/time.h>
class LinuxTimer
{
private:
    struct timeval tvBegin, tvEnd;
public:
    LinuxTimer(){};
    void Start(){
        gettimeofday(&tvBegin, NULL);
    }
    void End(){
        gettimeofday(&tvEnd, NULL);
    }
    double getTime(){     //��ȡ����Ϊ��λ��ʱ�䣬����Ϊ10^-6s
        double dDuration = 1000 * (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0);
        return dDuration;
    }
}LinuxTimer;
