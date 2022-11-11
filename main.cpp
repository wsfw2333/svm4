#include <stdio.h>
#include "temp.h"

extern void printHello_extern();
extern int etn;
int a = 88;
void count();
int main()
{
   
//    printHello();
//    printHello_two();
//     layout();
// //    printHello_extern();
//     printf("main.cpp: The etn is %d\n", etn);
//     printf("sum:%d\n",sum);

   int i=0;
    for (i = 0;i <= 5;i++)
    {
            count();
    }
    return 0;
 



}

void count()
{
    /*声明一个静态局部变量*/
    static int num = 0;
    num++;
    printf("%d\n",num);
}