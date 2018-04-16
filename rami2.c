#include<stdio.h>
#include<pthread.h>
struct record
{
       int p,at,bt,wt,tat,rt;
};


void sortarrivaltime(struct record a[],int processes)   //selection sort
{
       int i,j;
       struct record temp;
       for(i=0;i<processes;i++)
       {
              for(j=i+1;j<processes;j++)
              {
                     if(a[i].at > a[j].at)
                     {
                           temp = a[i];
                           a[i] = a[j];
                           a[j] = temp;
                     }
              }
       }
       return;
}

int main()
{
	
       int i,j,processes,time,remain,flag=0,ts;
       struct record a[7];
       float avgturnaround=0;
       printf("Round robin algorithm \n");
       printf("Number Of processes");
       scanf("%d",&processes);
       remain=processes;
       for(i=0;i<processes;i++)
       {
              printf("Enter arrival time and Burst time for processes P%d : ",i);
              scanf("%d%d",&a[i].at,&a[i].bt);
              a[i].p = i;
              a[i].rt = a[i].bt;
       }
       sortarrivaltime(a,processes);
       printf("Enter Time Quantum for each process: ");
       scanf("%d",&ts);
       for(time=0,i=0;remain!=0;)
       {
              if(a[i].rt<=ts && a[i].rt>0)
              {
                     time = time + a[i].rt;
                     a[i].rt=0;
                     flag=1;
              }
              else if(a[i].rt > 0)
              {
                     a[i].rt = a[i].rt - ts;
                     time = time + ts;
              }
              if(a[i].rt==0 && flag==1)
              {
                     remain--;
                     a[i].tat = time-a[i].at;
                     a[i].wt = time-a[i].at-a[i].bt;
                     avgturnaround = avgturnaround + time-a[i].at;
                     flag=0;
              }
              if(i==processes-1)
                     i=0;
              else if(a[i+1].at <= time)
                     i++;
              else
                     i=0;
       }
       printf("\n processes\t	arrivaltime\t	bursttime\t	turnaround\t	waittime\n");
       printf("======================================================================================================================================\n");
       for(i=0;i<processes;i++)
       {
              printf("P%d\t		%d\t		%d\t		%d\t		%d\n",a[i].p,a[i].at,a[i].bt,a[i].tat,a[i].wt);
       }
       avgturnaround = avgturnaround/processes;
       printf("Average Turnaround Time : %.2f 	\n",avgturnaround);
}
