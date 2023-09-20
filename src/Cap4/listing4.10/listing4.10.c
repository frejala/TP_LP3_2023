#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
struct job
{
    /* Link field for linked list. */
    struct job *next;
    /* Other fields describing work to be done... */
    int job_id; // Example: Adding a job identifier.
};

/* A linked list of pending jobs. */
struct job *job_queue = NULL; // Initialize job_queue to NULL.

/* Function to process a job. */
void process_job(struct job *job)
{
    printf("Processing job %d...\n", job->job_id);
    // Add your job processing logic here.
    sleep(1);
    printf("Job %d processed.\n", job->job_id);
}

/* Process queued jobs until the queue is empty. */
void *thread_function(void *arg)
{
    while (job_queue != NULL)
    {
        /* Get the next available job. */
        struct job *next_job = job_queue;
        /* Remove this job from the list. */
        job_queue = job_queue->next;
        /* Carry out the work. */
        process_job(next_job);
        /* Clean up. */
        free(next_job);
    }
    return NULL;
}

int main()
{
    // Example: Adding jobs to the queue.
    for (int i = 1; i <= 5; i++)
    {
        struct job *new_job = (struct job *)malloc(sizeof(struct job));
        new_job->job_id = i;
        new_job->next = NULL;
        // Add other job initialization here.

        // Add the job to the queue.
        if (job_queue == NULL)
        {
            job_queue = new_job;
        }
        else
        {
            struct job *current_job = job_queue;
            while (current_job->next != NULL)
            {
                current_job = current_job->next;
            }
            current_job->next = new_job;
        }
    }

    // Create threads and start processing jobs.
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_function, NULL);
    pthread_join(thread_id, NULL);
    return 0;
}
