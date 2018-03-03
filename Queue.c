#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#define tq 4
struct PCB
{
    int burst,prior;
    char name[10];
};
struct Node
{
    int bt,pt;
    char naam[10];
    struct Node *next;
};
struct Q1
{
    struct Node *f1,r1;
};
struct Q2
{
    struct Node *f2,*r2;
};
struct Q3
{
    struct Node *f3,*r3;
};
void enQ1(int a,int b,char *c)
{

}
void deQ1()
{

}
void enQ2(int a,int b,char *c)
{

}
void deQ2()
{

}
void enQ3(int a,int b,char *c)
{

}
void deQ3()
{

}
int main()
{
    int n,i=0;
    //write(1,"Enter the no of Processes:\n",27);
    printf("Enter the no of Processes: \n");
    read(0,(char*)&n,sizeof(n));
   // scanf("%d",&n);
    struct PCB arr[n];
    //write(1,"Enter the process_name,process_burst, process_priority\n",55);
   printf("Priority Ranges :\n");
    printf("Queue 1 (Round Robin): 0 - 10");
    printf("Queue 2 (Priority) : 11 - 20");
    printf("Queue 3 (First Come First Serve) : 21 - 30");

   printf("Enter the process_name,process_burst, process_priority\n");
    while(n--)
    {
        scanf("%s%d%d",arr[i].name,&arr[i].burst,&arr[i].prior);
    //    read(0,&arr,sizeof(arr));
    if(arr[i].prior<0 || arr[i].prior> 30)
    {
         printf("Not a Valid process_priority\nPlease enter process_priority again");
            scanf("%d",&arr[i].prior);
    }
    if(arr[i].prior >=0 && arr[i].prior<=10)
        {
            enQ1(arr[i].burst,arr[i].prior,arr[i].name);
        }
        else if(arr[i].prior >=11 && arr[i].prior<=20)
        {
            enQ2(arr[i].burst,arr[i].prior,arr[i].name);
        }
        else if(arr[i].prior >=21 && arr[i].prior<=30)
        {
            enQ3(arr[i].burst,arr[i].prior,arr[i].name);
        }
        ++i;
    }
        return 0;
}
