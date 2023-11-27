#include <stdio.h>

void firstfit(int blocksize[], int m, int processsize[], int n)
{
    int allocation[n];
    int blocksizecopy[m];
    for (int i = 0; i < m; i++)
        blocksizecopy[i] = blocksize[i];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            if (blocksizecopy[j] >= processsize[i])
            {
                allocation[i] = j;
                blocksizecopy[j] -= processsize[i];
                break;
            }
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d \t\t %d \t\t", i + 1, processsize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestfit(int blocksize[], int m, int processsize[], int n)
{
    int allocation[n];
    int blocksizecopy[m];
    for (int i = 0; i < m; i++)
        blocksizecopy[i] = blocksize[i];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int best = -1;
        for (int j = 0; j < m; j++)
        {
            if (blocksizecopy[j] >= processsize[i])
            {
                if (best == -1)
                    best = j;
                else if (blocksizecopy[best] > blocksizecopy[j])
                    best = j;
            }
        }
        if (best != -1)
        {
            allocation[i] = best;
            blocksizecopy[best] -= processsize[i];
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d \t\t %d \t\t", i + 1, processsize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstfit(int blocksize[], int m, int processsize[], int n)
{
    int allocation[n];
    int blocksizecopy[m];
    for (int i = 0; i < m; i++)
        blocksizecopy[i] = blocksize[i];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int worst = -1;
        for (int j = 0; j < m; j++)
        {
            if (blocksizecopy[j] >= processsize[i])
            {
                if (worst == -1)
                    worst = j;
                else if (blocksizecopy[worst] < blocksizecopy[j])
                    worst = j;
            }
        }
        if (worst != -1)
        {
            allocation[i] = worst;
            blocksizecopy[worst] -= processsize[i];
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d \t\t %d \t\t", i + 1, processsize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blocksize[10], processsize[10], m, n;
    printf("Enter no. of blocks: ");
    scanf("%d", &m);
    printf("Enter size of each block: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &blocksize[i]);
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &processsize[i]);
    printf("\nFirst Fit\n");
    firstfit(blocksize, m, processsize, n);
    printf("\nBest Fit\n");
    bestfit(blocksize, m, processsize, n);
    printf("\nWorst Fit\n");
    worstfit(blocksize, m, processsize, n);
    return 0;
}