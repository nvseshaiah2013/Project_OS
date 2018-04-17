#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#define MAX 1000
int process_id=0,timer=0;
float total_wt=0,total_ta=0;
struct PCB
{
    int burst,prior,pid,wt,last_Comp,ta;
};
struct PCB arr[MAX];
struct Gantt
{
    int pid,burst;
    struct Gantt *next;
};
struct Gantt *head=NULL;
struct QNode
{
    int bt,pt,pid;
    struct QNode *next;
};
struct Queue
{
    struct QNode *front, *rear;
};
void Calculate(int);
void push(int pi,int burs);
void enQ(struct Queue*,int,int,int);
void enQP(struct Queue*,int,int,int);
struct QNode *deQ(struct Queue*);
int isEmpty(struct Queue*);
struct QNode* deQ(struct Queue*);
struct Queue* Create();
void display(int);
void execute(struct Queue *a,struct Queue *b,struct Queue *c);
void inner_round_robin(struct Queue*);
void priority_sch(struct Queue*);
void f2cs(struct Queue*);
void displayL();
int main()
{
    struct Queue *A,*B,*C;
    A=Create();
    B=Create();
    C=Create();
    int n,i=0;
    printf("Enter the no of Processes: \n");
   scanf("%d",&n);
   int n1=n;
   printf("Priority Ranges :\n");
    printf("Queue 1 (Round Robin): 1 - 10\n");
    printf("Queue 2 (Priority) : 11 - 20\n");
    printf("Queue 3 (First Come First Serve) : 21 - 30\n");
    while(n--)
    {
        printf("Enter process_burst, process_priority for P%d\n",++process_id);
        arr[i].pid=process_id;
        arr[i].last_Comp=0;
        arr[i].wt=0;
        arr[i].ta=0;
        scanf("%d%d",&arr[i].burst,&arr[i].prior);
        if(arr[i].burst<1)
        {
            printf("Please enter process_burst again It should be >0\n");
            scanf("%d",&arr[i].burst);
        }
    if(arr[i].prior<=0 || arr[i].prior> 30)
    {
         printf("Not a Valid process_priority\nPlease enter process_priority again");
            scanf("%d",&arr[i].prior);
    }
    if(arr[i].prior >0 && arr[i].prior<=10)
        {
            enQ(A,arr[i].burst,arr[i].prior,arr[i].pid);
        }
        else if(arr[i].prior >=11 && arr[i].prior<=20)
        {
            enQP(B,arr[i].burst,arr[i].prior,arr[i].pid);
        }
        else if(arr[i].prior >=21 && arr[i].prior<=30)
        {
            enQ(C,arr[i].burst,arr[i].prior,arr[i].pid);
        }
        ++i;
    }
    execute(A,B,C);
    Calculate(n1);
    displayL();
    printf("\n");
    display(n1);
        return 0;
}
void Calculate(int n)
{
    int i,twt=0,tat=0;
    for(i=0;i<n;i++)
    {
        arr[i].ta=arr[i].wt+arr[i].burst;
        tat+=arr[i].ta;
        twt+=arr[i].wt;
    }
    total_ta=(float)tat/n;
    total_wt=(float)twt/n;
}
void push(int pi,int burs)
{
    struct Gantt *n=(struct Gantt*)malloc(sizeof(struct Gantt));
    struct Gantt *temp=head;
    n->burst=burs;
    n->pid=pi;
    n->next=NULL;
    if(head==NULL)
    {
        head=n;
        return;
    }
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=n;
}
void displayL()
{
    int k=0;
    if(head==NULL)
       {
        printf("Empty\n");
        return;
       }
       printf("\n            Gantt Chart           ");
       struct Gantt *temp=head;
       printf("\n---------------------------------------\n");
       printf("PID  |  Burst |  Started At | Ended At |\n");
         printf("---------------------------------------");
       while(temp!=NULL)
       {
           printf("\n| P%d |%6d  |%11d  |%8d  |\n",temp->pid,temp->burst,k,k+temp->burst);
           k=k+temp->burst;
           temp=temp->next;
       }
       printf("---------------------------------------");
}
struct QNode* New(int bt,int pt,int pid)
{
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->bt= bt;
    temp->pt=pt;
    temp->pid=pid;
    temp->next = NULL;
    return temp;
}
struct Queue *Create()
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
void enQ(struct Queue *q, int bt,int pt,int pid)
{
    struct QNode *temp = New(bt,pt,pid);
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
    q->rear->next = temp;
    q->rear = temp;
}
void enQP(struct Queue *q, int bt,int pt,int pid)
{
    struct QNode *temp = New(bt,pt,pid);
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
    else if(q->front->pt>pt)
    {
        temp->next=q->front;
        q->front=temp;
    }
    else
    {
        struct QNode *tmp =q->front;
        while(tmp->next!=NULL && tmp->next->pt<=pt)
            tmp=tmp->next;
        temp->next=tmp->next;
        tmp->next=temp;
    }

}
struct QNode *deQ(struct Queue *q)
{
    if (isEmpty(q))
       return NULL;
    struct QNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
       q->rear = NULL;
    return temp;
}
void display(int n)
{    int i=0;
printf("\n\n ------------------------------------------------------");
        printf("\n| Process | Burst | Priority | Wait Time | TurnA. Time |\n");
          printf(" ------------------------------------------------------");
        while(i<n)
        {

            printf("\n|   P%d    |%5d  |%7d   |%8d    |%9d   |\n",i+1,arr[i].burst,arr[i].prior,arr[i].wt,arr[i].ta);
               printf(" ------------------------------------------------------");
               ++i;
        }
    printf("\nAverage Waiting Time is %f: ",total_wt);
    printf("\nAverage TurnAround Time is :%f ",total_ta);
}
int isEmpty(struct Queue *a)
{
    if(a->front==NULL)
        return 1;
    else return 0;
}
void execute(struct Queue *a,struct Queue *b,struct Queue *c)
{
    while(1)
    {
        if(a->front!=NULL){
    inner_round_robin(a);}
    if(b->front!=NULL){
    priority_sch(b);}
    if(c->front!=NULL){
    f2cs(c);}
    if(a->front==NULL && b->front==NULL && c->front==NULL)
        break;
    }
}
void inner_round_robin(struct Queue *q)
{
    printf("\nExecuting Q1 Round Robin\n");
struct QNode *tmp1 = q->front;
int inner=0,outer=0;
while(tmp1!=NULL && outer<10)
{
    while(tmp1!=NULL && (inner+tmp1->bt)<=4 && (outer+tmp1->bt)<=10)
    {
        (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
        inner=inner+tmp1->bt;
        outer=outer+tmp1->bt;
        timer=timer+tmp1->bt;
        push(tmp1->pid,tmp1->bt);
         arr[tmp1->pid-1].last_Comp=timer;
        deQ(q);
        tmp1=q->front;
    }
    if(tmp1==NULL)
    {
        printf("Inner Round Robin Queue Processes Exhausted\n");
        break;
    }
    else if((inner+tmp1->bt)<=4)
    {
        (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
        tmp1->bt-=(10-outer);
        inner+=(10-outer);
        timer+=(10-outer);
        push(tmp1->pid,(10-outer));
         arr[tmp1->pid-1].last_Comp=timer;
        outer=10;
        struct QNode *n=deQ(q);
        enQ(q,n->bt,n->pt,n->pid);
        tmp1=q->front;
    }
    else if((outer+tmp1->bt)<=10)
    {
       if(inner!=4){
            (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
        tmp1->bt-=(4-inner);
        outer+=(4-inner);
        timer+=(4-inner);
        push(tmp1->pid,(4-inner));
         arr[tmp1->pid-1].last_Comp=timer;
        inner=4;
        struct QNode *n=deQ(q);
        enQ(q,n->bt,n->pt,n->pid);
        tmp1=q->front;}
    }
    else
    {
        if(outer==10)break;
        int m=(10-outer)<(4-inner)?(10-outer):(4-inner);
        (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
        tmp1->bt-=m;
        inner+=m;
        outer+=m;
        timer+=m;
         arr[tmp1->pid-1].last_Comp=timer;
        if(m!=0){
               push(tmp1->pid,m);
        struct QNode *n=deQ(q);
        enQ(q,n->bt,n->pt,n->pid);
        tmp1=q->front;
        }
    }
    if(inner==4)inner=0;
}
printf("\nExiting Q1 RoundRobin\n");
}
void priority_sch(struct Queue *q)
{
    printf("\nExecuting Q2 Priority Based");
struct QNode *tmp1=q->front;
int i=0;
while(tmp1!=NULL && (i+tmp1->bt)<=10)
{
    (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
    i=i+tmp1->bt;
     push(tmp1->pid,tmp1->bt);
    timer+=tmp1->bt;
    arr[tmp1->pid-1].last_Comp=timer;
    deQ(q);
    tmp1=q->front;
}
if(i==10)
{
    printf("\nExiting Q2 Priority Based\n");
    return;
}
else
{
    if(tmp1!=NULL)
    {
    (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
    int tmp=10-i;
    tmp1->bt-=tmp;
     push(tmp1->pid,tmp);
    timer+=tmp;
    arr[tmp1->pid-1].last_Comp=timer;
    i=10;
    }
    else
    {
        printf("\nPriority Queue Processes Exhausted\n");
    }
}
printf("\nExiting Q2 Priority Based\n");
}
void f2cs(struct Queue *q)
{
    printf("\nExecuting Q3 FCFS based\n");
struct QNode *tmp1=q->front;
int i=0;
while(tmp1!=NULL && (i+tmp1->bt)<=10)
{
    (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
    i=i+tmp1->bt;
    push(tmp1->pid,tmp1->bt);
    timer+=tmp1->bt;
     arr[tmp1->pid-1].last_Comp=timer;
    deQ(q);
    tmp1=q->front;
}
if(i==10)
{
    printf("\nExiting Q3 FCFS Based");
return;
}
else
{
    if(tmp1!=NULL)
    {
         (arr[tmp1->pid-1].wt)+=(timer-(arr[tmp1->pid-1].last_Comp));
    int tmp=10-i;
    tmp1->bt-=tmp;
    push(tmp1->pid,tmp);
    timer+=tmp;
     arr[tmp1->pid-1].last_Comp=timer;
    i=10;
    }
    else
    {
        printf("\nFCFS Queue Processes Exhausted\n");
    }
}
printf("\nExiting Q3 FCFS Based");
}
