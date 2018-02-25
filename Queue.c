#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
struct PCB
{
    int burst,prior;
    char name[10];
};
int main()
{
    int n,i=0;
    printf("Enter the no of Processes:\n");
    scanf("%d",&n);
    struct PCB arr[n];
    printf("Enter the process_name,process_burst, process_priority\n");
    while(n--)
    {
        scanf("%s%d%d",arr[i].name,&arr[i].burst,&arr[i].prior);
        ++i;
    }
    return 0;
}
