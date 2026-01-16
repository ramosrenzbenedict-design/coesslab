#include<stdio.h>

int main()
{
    int p[20], bt[20], wt[20], tat[20], i, k, n, temp; 
    float wtavg, tatavg;
    
    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);
    
    // Number of Processes should be less than or equal to 20
    for(i=0;i<n;i++)
    {
        p[i]=i;
        printf("Enter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
    }
    
    // Bubble Sort in respect to sort Burst Time
    for(i=0;i<n;i++)
    {
        
        for(k=i+1;k<n;k++)
        {
            
            if(bt[i]>bt[k])
                {
                    // swap bt values
                    temp=bt[i];
                    bt[i]=bt[k];
                    bt[k]=temp;
                    // swap p values
                    temp=p[i];
                    p[i]=p[k];
                    p[k]=temp;
                }
        
        }
    
    }
    
    //Waiting Time and Turnaround Time Calculation
    wt[0] = 0;
    wtavg = 0;
    tat[0] = bt[0];
    tatavg = bt[0]; 
    
    //Loop for initializing values of waiting time and turnaround time and getting the averages
    for(i=1;i<n;i++)
    {
        wt[i] = wt[i-1] +bt[i-1];
        tat[i] = tat[i-1] +bt[i];
        wtavg = wtavg + wt[i];
        tatavg = tatavg + tat[i];
    }
    
    // Ramos Renz Benedict
    // Printing The Table of Values
    printf("\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n");
    
    for(i=0;i<n;i++)
    {
        printf("\n\t P%d \t\t %d \t\t %d \t\t %d", p[i], bt[i], wt[i], tat[i]);
    }
    
    printf("\n\nAverage Waiting Time -- %.2f", wtavg);
    printf("\nAverage Turnaround Time -- %.2f", tatavg);
    printf("\n");
}
