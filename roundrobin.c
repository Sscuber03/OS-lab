#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    int *bt = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));
    int *at = (int *)malloc(n * sizeof(int));
    int *ct = (int *)malloc(n * sizeof(int));

    printf("Enter the burst time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    printf("Enter the arrival time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
    }

    printf("Enter the time quantum: ");
    int tq;
    scanf("%d", &tq);

    int *rem_bt = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
    }

    int t = 0;
    int done = 0;

    while (done != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                if (rem_bt[i] > tq)
                {
                    t += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    t += rem_bt[i];
                    rem_bt[i] = 0;
                    tat[i] = t - at[i];
                    wt[i] = tat[i] - bt[i];
                    ct[i] = t;
                    done++;
                }
            }
        }
    }

    printf("Process\t\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], at[i], wt[i], tat[i], ct[i]);
    }

    float avg_wt = 0;
    float avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    printf("Average waiting time: %f\n", avg_wt);
    printf("Average turnaround time: %f\n", avg_tat);

    return 0;
}