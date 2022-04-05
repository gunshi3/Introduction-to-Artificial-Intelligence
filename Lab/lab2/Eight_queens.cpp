#include "LinuxTimer.h"
#include <iostream>
using namespace std;
int a[9];        //a[2] = 3��ʾ�ڶ��еĻʺ��ڵ�����
int b[9] = {0};  //��¼��Щ���Ѿ���ռ��
int c[16] = {0}; //��¼i+j-1����Χ��1~15����¼���ϵ����µĶԽ����Ƿ�ռ
int d[16] = {0}; //��¼i-j+8����Χ��1~15����¼���ϵ����µĶԽ����Ƿ�ռ
int sum = 0;     //�ܽⷨ��

void printChess()
{
    for (int i = 1; i <= 8; i++)
    {
        printf("%d-%d\n", i, a[i]);
    }
    printf("\n");
}

void searchh(int i)
{
    for (int j = 1; j <= 8; j++) //8��λ�ñ���һ��
    {
        if ((!b[j]) && (!c[i + j - 1]) && (!d[i - j + 8]))
        {
            /********** Begin **********/
            if (i == 8)
            {   
                a[i] = j;
                printChess();
                sum++;
                return;
            }
            //��λ����Ϣ
            a[i] = j;
            b[j] = 1;
            c[i + j - 1] = 1;
            d[i - j + 8] = 1;
            searchh(i + 1); //��һ���ƻ�
            //���ݣ���λ����Ϣ�Ļ�ԭ��������
            b[j] = 0;
            c[i + j - 1] = 0;
            d[i - j + 8] = 0;
            /********** End **********/
        }
    }
}

int main()
{
    LinuxTimer.Start();
    searchh(1);
    LinuxTimer.End();
    cout << "Number of solutions:" << sum << endl;
    double t = LinuxTimer.getTime();
    cout << "time: " << t << "ms" << endl;
    return 0;
}