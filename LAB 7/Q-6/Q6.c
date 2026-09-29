#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int year;
    int type;
};

/* Function used for sorting events */
int compareEvents(const void *a, const void *b)
{
    struct Event *event1 = (struct Event *)a;
    struct Event *event2 = (struct Event *)b;

    /* First sort according to year */
    if (event1->year != event2->year)
    {
        return event1->year - event2->year;
    }

    /* If year is same, death (-1) comes before birth (+1) */
    return event1->type - event2->type;
}

int main()
{
    int n;
    int i;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    /* There are two events for every scientist */
    struct Event events[2 * n];

    for (i = 0; i < n; i++)
    {
        char name[50];
        int birth, death;

        printf("Enter name, birth year and death year: ");
        scanf("%s %d %d", name, &birth, &death);

        /* Birth event */
        events[2 * i].year = birth;
        events[2 * i].type = 1;

        /* Death event */
        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events */
    qsort(events, 2 * n, sizeof(struct Event), compareEvents);

    int alive = 0;
    int maxAlive = 0;
    int bestYear = 0;

    /* Process events one by one */
    for (i = 0; i < 2 * n; i++)
    {
        alive = alive + events[i].type;

        if (alive > maxAlive)
        {
            maxAlive = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nMaximum number of scientists alive = %d\n", maxAlive);
    printf("Best year = %d\n", bestYear);

    return 0;
}