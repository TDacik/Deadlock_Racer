//# Deadlock: true
//# Lockgraph:
//#   - lock1 -> lock2
//#   - lock2 -> lock1

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

bool x = false;

void fn()
{

    if (x)
    {
        pthread_mutex_lock(&lock1);
        pthread_mutex_lock(&lock2);
        pthread_mutex_unlock(&lock2);
        pthread_mutex_unlock(&lock1);
    }
    else 
    {
        pthread_mutex_lock(&lock2);
        pthread_mutex_lock(&lock1);
        pthread_mutex_unlock(&lock1);
        pthread_mutex_unlock(&lock2);
    }
}

void *thread1(void *v)
{
    fn();
    return NULL;
}

void *thread2(void *v)
{
    fn();
    return NULL;
}

int main(int argc, char **argv)
{	
    pthread_t threads[2];

    x = !(argc > 2);

    pthread_create(&threads[0], NULL, thread1, NULL);
    
    x = !x;
    
    pthread_create(&threads[1], NULL, thread2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
	
    return 0;
}
