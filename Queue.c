#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
int process_id=0;
int timer=0;
int sum=0;
struct PCB
{
    int burst,prior,pid;
};
struct QNode
{
    int bt,pt,pid;
    struct QNode *next;
};
struct Queue
{
    struct QNode *front, *rear;
};

void enQ(struct Queue*,int,int,int);
void enQP(struct Queue*,int,int,int);
struct QNode *deQ(struct Queue*);
int isEmpty(struct Queue*);
struct QNode* deQ(struct Queue*);
struct Queue* Create();
void display(struct Queue*);
void execute(struct Queue *a,struct Queue *b,struct Queue *c);
void inner_round_robin(struct Queue*);
void priority_sch(struct Queue*);
void f2cs(struct Queue*);
int main()
{
    struct Queue *A,*B,*C;
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
    printf("Queue 1 (Round Robin): 0 - 10\n");
    printf("Queue 2 (Priority) : 11 - 20\n");
    printf("Queue 3 (First Come First Serve) : 21 - 30\n");
    while(n--)
    {
        char temp[5];
        printf("Enter process_burst, process_priority for P%d\n",++process_id);
        arr[i].pid=process_id;
        scanf("%d%d",&arr[i].burst,&arr[i].prior);
    //    read(0,&arr,sizeof(arr));
    if(arr[i].prior<0 || arr[i].prior> 30)
    {
         printf("Not a Valid process_priority\nPlease enter process_priority again");
            scanf("%d",&arr[i].prior);
    }
    if(arr[i].prior >=0 && arr[i].prior<=10)
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
        sum=sum+arr[i].burst;
        ++i;
    }
    execute(A,B,C);
    printf("%d\n",timer);
        return 0;
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
    if (q->front == NULL)
       return NULL;
    struct QNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
       q->rear = NULL;
    return temp;
}
void display(struct Queue *q)
{
    if(q->front==NULL)
    {
        printf("Queue is empty\n");
    }
    else
    {
        struct QNode *tmp = q->front;
        while(tmp->next!=NULL)
        {
            printf("P%d-->%d\n",tmp->pid,tmp->bt);
            tmp=tmp->next;
        }
        printf("P%s-->%d NULL\n",tmp->pid,tmp->bt);
    }
}
int isEmpty(struct Queue *a)
{
    if(a->front==NULL)
        return 1;
    else return 0;
}
void execute(struct Queue *a,struct Queue *b,struct Queue *c)
{
    int qa=0,qb=0,qc=0;
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
struct QNode *tmp = q->front;
int inner=0,outer=0;
while(tmp!=NULL && outer<10)
{
    while(tmp!=NULL && (inner+tmp->bt)<=4 && (outer+tmp->bt)<=10)
    {
        inner=inner+tmp->bt;
        outer=outer+tmp->bt;
        timer=timer+tmp->bt;
        printf("Having P%d Burst:%d \n",tmp->pid,tmp->bt);
        deQ(q);
        tmp=q->front;
    }
    if(tmp==NULL)
    {
        printf("No More ProcessRR\n");
        break;
    }
    else if((inner+tmp->bt)<=4)
    {
        tmp->bt-=(10-outer);
        inner+=(10-outer);
        timer+=(10-outer);
        outer=10;
         printf("P%d Burst:%d \n",tmp->pid,tmp->bt);
        struct QNode *n=deQ(q);
        enQ(q,n->bt,n->pt,n->pid);
        tmp=q->front;
    }
    else if((outer+tmp->bt)<=10)
    {
       if(inner!=4){
        tmp->bt-=(4-inner);
        outer+=(4-inner);
        timer+=(4-inner);
        inner=4;
         printf("P%d Burst:%d \n",tmp->pid,tmp->bt);
        struct QNode *n=deQ(q);
        enQ(q,n->bt,n->pt,n->pid);
        tmp=q->front;}
    }
    else
    {
        if(outer==10)break;
        int m=(10-outer)<(4-inner)?(10-outer):(4-inner);
        tmp->bt-=m;
        inner+=m;
        outer+=m;
        timer+=m;
        if(m!=0){
               printf("P%d Burst:%d \n",tmp->pid,tmp->bt);
        struct QNode *n=deQ(q);
        enQ(q,n->bt,n->pt,n->pid);
        tmp=q->front;
        }
    }
    if(inner==4)inner=0;
}

}
void priority_sch(struct Queue *q)
{
struct QNode *tmp1=q->front;
int i=0;
while(tmp1!=NULL && (i+tmp1->bt)<=10)
{
    i=i+tmp1->bt;
    timer+=tmp1->bt;
    deQ(q);
    tmp1=q->front;
}
if(i==10)
{
    return;
}
else
{
    if(tmp1!=NULL)
    {
    int tmp=10-i;
    tmp1->bt-=tmp;
    timer+=tmp;
    i=10;
    }
    else
    {
        printf("No More ProcessPRI\n");
    }
}
}
void f2cs(struct Queue *q)
{
struct QNode *tmp1=q->front;
int i=0;
while(tmp1!=NULL && (i+tmp1->bt)<=10)
{
    i=i+tmp1->bt;
    timer+=tmp1->bt;
    deQ(q);
    tmp1=q->front;
}
if(i==10)
{
return;
}
else
{
    if(tmp1!=NULL)
    {
    int tmp=10-i;
    tmp1->bt-=tmp;
    timer+=tmp;
    i=10;
    }
    else
    {
        printf("No More ProcessFCFS\n");
    }
}
}
