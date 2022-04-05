#include "LinuxTimer.h"
#include <iostream>
using namespace std;
int a[9];        //a[2] = 3表示第二行的皇后在第三列
int b[9] = {0};  //记录哪些列已经被占了
int c[16] = {0}; //记录i+j-1，范围是1~15，记录右上到左下的对角线是否被占
int d[16] = {0}; //记录i-j+8，范围是1~15，记录左上到右下的对角线是否被占
int sum = 0;     //总解法数

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
    for (int j = 1; j <= 8; j++) //8个位置遍历一遍
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
            //改位置信息
            a[i] = j;
            b[j] = 1;
            c[i + j - 1] = 1;
            d[i - j + 8] = 1;
            searchh(i + 1); //下一步计划
            //回溯，将位置信息改回原来的样子
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