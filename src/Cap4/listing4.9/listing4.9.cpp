/* Descripcion:
Ejemplo de parada segura de hilos con lanzamiento de excepciones en C++
 */
#include <iostream>
#include <pthread.h>
#include <random>
#include <stdio.h>

int should_exit_thread_immediately()
{
    // generate a random number between 0 and 9
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    int random_number = dis(gen);

    // if the random number is 0, return true, otherwise return false
    return random_number == 0;
}

class ThreadExitException
{
public:
    /* Create  an  exception-signaling  thread  exit  with  RETURN_VALUE.  */
    ThreadExitException(void *return_value)
        : thread_return_value_(return_value) {}

    /*  Actually  exit  the  thread,  using  the  return  value  provided  in  the
      constructor.  */
    void *DoThreadExit()
    {
        printf("Safely exiting thread\n");
        pthread_exit(thread_return_value_);
    }

private:
    /*  The  return  value  that  will  be  used  when  exiting  the  thread.*/
    void *thread_return_value_;
};

void do_some_work()
{
    while (1)
    {
        /*  Do  some  useful  things  here...  */
        if (should_exit_thread_immediately())
            throw ThreadExitException(NULL);
    }
}

void *thread_function(void *)
{
    try
    {
        do_some_work();
    }
    catch (ThreadExitException ex)
    {
        ex.DoThreadExit();
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    printf("Example of safe thread exit in C++\n");
    pthread_t hilo;
    pthread_create(&hilo, NULL, thread_function, NULL);
    pthread_join(hilo, NULL);
    return 0;
}