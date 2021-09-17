//# Deadlock: false
//# Lockgraph:
//#   - lock1 -> lock2

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int ready_flag = false;

void *thread1(void *v)
{
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    ready_flag = true;
    pthread_cond_signal(&cond);

    return NULL;
}

void *thread2(void *v)
{
    pthread_mutex_lock(&lock2); // <--
   
    // Nonterminating code in sequential analysis
    while(1)
    {
        pthread_cond_wait(&cond, &lock2);
        if (ready_flag)
            break;
    }

    pthread_mutex_unlock(&lock2); // <--

    pthread_mutex_lock(&lock1);  // <--
    pthread_mutex_unlock(&lock1); // <---

    return NULL;
}

int main(int argc, char **argv)
{	
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, thread1, NULL);
    pthread_create(&threads[1], NULL, thread2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
	
    return 0;
}
