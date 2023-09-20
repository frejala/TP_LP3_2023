#include <pthread.h>
void *thread_function(void *thread_arg)
{
    double initial_balance = 1000.0;
    double interest_rate = 0.05;
    for (int year = 1; year <= 100; year++)
    {
        initial_balance *= (1 + interest_rate); // Simulate compound interest
        if (year % 25 == 0)
        {
            printf("Year %d balance: %f\n", year, initial_balance);
        }
    }
    printf("Final balance: %f\n", initial_balance);
    return NULL;
}
int main()
{
    pthread_attr_t attr;
    pthread_t thread;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread, &attr, &thread_function, NULL);
    pthread_attr_destroy(&attr);
    /* Do work here... */
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (j % 25 == 0 && i % 25 == 0)
            {
                printf("n: %d\n", j);
            }
        }
    }
    /* No need to join the second thread. */
    return 0;
}