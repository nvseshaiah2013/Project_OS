#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
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
struct Q
{
    struct Node *f,*r;
};
struct Q Create()
{
    struct Q a;
    a.f=NULL;
    a.r=NULL;
    return a;
}
struct Node* New(int a,int b,char *c)
{
    struct Node *t = (struct Node*)malloc(sizeof(struct Node));
    t->bt=a;
    t->pt=b;
    strcpy(t->naam,c);
    t->next=NULL;
    return t;
};
void enQ(struct Q q,int a,int b,char *c)
{
struct Node *temp = New(a,b,c);

    if (q.r == NULL)
    {
       q.f = q.r = temp;
       return;
    }
    q.r->next = temp;
    q.r = temp;
}
void deQ(struct Q q)
{
if (q.f == NULL)
       return NULL;
    struct QNode *temp = q.f;
    q.f = q.f->next;
    if (q.f == NULL)
       q.r = NULL;
    return temp;
}
int main()
{
    struct Q A,B,C;
    A=Create();
    B=Create();
    C=Create();
    int n,i=0;
    // write(1,"Enter the no of Processes:\n",27);
    printf("Enter the no of Processes: \n");
    // read(0,(char*)&n,sizeof(n));
   scanf("%d",&n);
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
            enQ(A,arr[i].burst,arr[i].prior,arr[i].name);
        }
        else if(arr[i].prior >=11 && arr[i].prior<=20)
        {
            enQ(B,arr[i].burst,arr[i].prior,arr[i].name);
        }
        else if(arr[i].prior >=21 && arr[i].prior<=30)
        {
            enQ(C,arr[i].burst,arr[i].prior,arr[i].name);
        }
        ++i;
    }
        return 0;
}
