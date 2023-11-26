// write a code to stimulate producer consumer problem with semaphore

#include <stdio.h>
#include <stdlib.h>

int muter = 1, full = 0, empty = 3, x = 0;

int wait(int s)
{
    return (--s);
}

int signal(int s)
{
    return (++s);
}

void producer()
{
    muter = wait(muter);
    full = signal(full);
    empty = wait(empty);
    x++;
    printf("\nProducer produces the item %d", x);
    muter = signal(muter);
}

void consumer()
{
    muter = wait(muter);
    full = wait(full);
    empty = signal(empty);
    printf("\nConsumer consumes item %d", x);
    x--;
    muter = signal(muter);
}

int main()
{
    int n;
    printf("Enter 1 for Producer, 2 for Consumer, 3 to Exit\n");
    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            if (muter == 1 && empty != 0)
                producer();
            else
                printf("Buffer is full!\n");
            break;
        case 2:
            if (muter == 1 && full != 0)
                consumer();
            else
                printf("Buffer is empty!\n");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
