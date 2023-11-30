// code to simulate bankers problem

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int alloc[n][m], maxmat[n][m], need[n][m], avail[m], finish[n], sequence[n];
    printf("Enter allocation matrix: \n");
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<m;j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter max matrix: \n");
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<m;j++)
        {
            scanf("%d", &maxmat[i][j]);
        }
    }
    printf("Enter available matrix: \n");
    for(i = 0;i<m;i++)
    {
        scanf("%d", &avail[i]);
    }
    for(i = 0;i<n;i++)
    {
        finish[i] = 0;
    }
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<m;j++)
        {
            need[i][j] = maxmat[i][j] - alloc[i][j];
        }
    }
    int count = 0;
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<n;j++)
        {
            if(finish[j] == 0)
            {
                int flag = 0;
                for(k = 0;k<m;k++)
                {
                    if(need[j][k] > avail[k])
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    sequence[count++] = j;
                    finish[j] = 1;
                    for(k = 0;k<m;k++)
                    {
                        avail[k] += alloc[j][k];
                    }
                }
            }
        }
    }
    int flag = 0;
    for(i = 0;i<n;i++)
    {
        if(finish[i] == 0)
        {
            flag = 1;
            printf("Unsafe system\n");
            break;
        }
    }
    if(flag == 0)
    {
        printf("Safe system\n");
        printf("Safe sequence: ");
        for(i = 0;i<n;i++)
        {
            printf("P%d ", sequence[i]);
        }
        printf("\n");
    }
}