#include<stdio.h>
#include<stdlib.h>

int main()
{
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    int *bt = (int *)malloc(n * sizeof(int));
    int *at = (int *)malloc(n * sizeof(int));
    int *p_id = (int *)malloc(n * sizeof(int));
    // int totaltime = 0;

    printf("Enter the burst time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
        // totaltime += bt[i];
    }

    printf("Enter the arrival time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
    }

    for (int i = 0; i < n; i++)
    {
        p_id[i] = i + 1;
    }

    //preemptive sjf
    
    int t = 0;
    int done = 0;
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));
    int *rem_bt = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
    }

    while (done < n)
    {
        int min = 100;
        int min_index = -1;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0 && at[i] <= t && rem_bt[i] < min)
            {
                min = rem_bt[i];
                min_index = i;
            }
        }
        if (min_index != -1)
        {
            rem_bt[min_index]--;
            if (rem_bt[min_index] == 0)
            {
                done++;
                tat[min_index] = t + 1 - at[min_index];
                wt[min_index] = tat[min_index] - bt[min_index];
            }
        }
        t++;
    }

    printf("Process\tBT\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", p_id[i], bt[i], at[i], wt[i], tat[i]);
    }

    float avgwt = 0;
    float avgtat = 0;

    for (int i = 0; i < n; i++)
    {
        avgwt += wt[i];
        avgtat += tat[i];
    }

    avgwt /= n;
    avgtat /= n;

    printf("Average waiting time: %f\n", avgwt);
    printf("Average turnaround time: %f\n", avgtat);

    return 0;

    // for(int i = 0;i<totaltime;i++)
    // {
    //     int min = 100;
    //     int min_index = -1;
    //     for(int j = 0;j<n;j++)
    //     {
    //         if(rem_bt[j] > 0 && at[j] <= i && rem_bt[j] < min)
    //         {
    //             min = rem_bt[j];
    //             min_index = j;
    //         }
    //     }
    //     if(min_index != -1)
    //     {
    //         rem_bt[min_index]--;
    //         if(rem_bt[min_index] == 0)
    //         {
    //             // printf("Process %d completed at time %d\n",p_id[min_index],i+1);

    //         }
    //     }
    // }
}