#include <malloc.h>
#include <pthread.h>
typedef struct job
{
    struct job *next;
    int job_id;
} job;

struct job *job_queue;
job *last;
job *first;
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void process_job(int thread_id, int job_id)
{
    printf("Thread %d, job %d\n", thread_id, job_id);
    int random_number = 1 + rand() % 3;
    sleep(random_number);
    return;
}

void *thread_function(void *arg)
{
    int *thread_id = (int *)arg;
    while (1)
    {
        pthread_mutex_lock(&job_queue_mutex);
        if (last == NULL)
        {
            pthread_mutex_unlock(&job_queue_mutex);
            return NULL;
        }
        job *next_job = last;
        last = last->next;
        pthread_mutex_unlock(&job_queue_mutex);

        process_job(*thread_id, next_job->job_id);
        free(next_job);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    sleep(2);
    job *temp = malloc(sizeof(job));
    temp->job_id = 0;
    last = temp;
    first = temp;

    for (int i = 1; i < 100; i++)
    {
        job *n = malloc(sizeof(job));
        n->job_id = i;
        first->next = n;
        first = n;
    }

    pthread_t threads[10];
    int ids[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, &ids[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
