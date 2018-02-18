#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
struct PCB
{
    int burst,prior;
    char name[10];
}
int main()
{
    int n,i=0;
    read(0,n,sizeof(n));
    struct PCB arr[n];
    while(n--)
    {
        read(0,arr[i],sizeof(arr[i]));
        ++i;
    }
    return 0;
}