#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#define tq 4
int process_id=0;
struct PCB
{
    int burst,prior;
    char name[10];
};
struct QNode
{
    int bt,pt;
    char naam[10];
    struct QNode *next;
};
struct Queue
{
    struct QNode *front, *rear;
};
void enQ(struct Queue*,int,int,char*);
void enQP(struct Queue*,int,int,char*);
int isEmpty(struct Queue*);
struct QNode* deQ(struct Queue*);
struct Queue* Create();
int process_comp(char*,char*);
void display(struct Queue*);
void execute(struct Queue *a,struct Queue *b,struct Queue *c);
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
        itoa(process_id,temp,10);
        strcpy(arr[i].name,"P");
        strcat(arr[i].name,temp);
        scanf("%d%d",&arr[i].burst,&arr[i].prior);
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
            enQP(B,arr[i].burst,arr[i].prior,arr[i].name);
        }
        else if(arr[i].prior >=21 && arr[i].prior<=30)
        {
            enQ(C,arr[i].burst,arr[i].prior,arr[i].name);
        }
        ++i;
    }
    display(A);
    display(B);
    display(C);
    execute(A,B,C);
        return 0;
}
struct QNode* New(int bt,int pt,char *name)
{
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->bt= bt;
    temp->pt=pt;
    strcpy(temp->naam,name);
    temp->next = NULL;
    return temp;
}
struct Queue *Create()
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
void enQ(struct Queue *q, int bt,int pt,char *name)
{
    struct QNode *temp = New(bt,pt,name);
    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }
    q->rear->next = temp;
    q->rear = temp;
}
void enQP(struct Queue *q, int bt,int pt,char *name)
{
    struct QNode *temp = New(bt,pt,name);
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
            printf("%s-->",tmp->naam);
            tmp=tmp->next;
        }
        printf("%s-->NULL\n",tmp->naam);
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

}
int process_comp(char *a,char *b)
{
    int l1=strlen(a),l2=strlen(b);
    if(l1==l2)
        return strcmp(a,b);
    else if(l1>l2)
        return 1;
    else return -1;

}
