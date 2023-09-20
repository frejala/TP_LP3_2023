#include <malloc.h>
#include <pthread.h>

/* Allocate a temporary buffer.
 */
void *allocate_buffer(size_t size)
{
    return malloc(size);
}
/* Deallocate a temporary buffer.
 */
void deallocate_buffer(void *buffer)
{
    free(buffer);
}

void do_some_work()
{
    /* Allocate a temporary buffer.
     */
    void *temp_buffer = allocate_buffer(1024);
    /* Register a cleanup handler for this buffer, to deallocate it in
    case the thread exits or is cancelled. */
    pthread_cleanup_push(deallocate_buffer, temp_buffer);
    /* Do some work here that might call pthread_exit or might be
    cancelled... */
    pthread_exit(NULL);

    // unregister the cleanup handler because the thread succesfully terminated
    pthread_cleanup_pop(1);
}

void *function(void *_)
{
    do_some_work();
    return NULL;
}

// Thread Cleanup Handler
int main(int argc, char *argv[])
{
    printf("Example of thread cleanup handler\n");
    pthread_t hilo;
    pthread_create(&hilo, NULL, function, NULL);
    pthread_join(hilo, NULL);
    return 0;
}