#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void e1()
{
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
}

void e2()
{
    pthread_mutex_lock(&lock2);
    pthread_mutex_lock(&lock1);
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
}

void *thread(void *v)
{
    e1();
    e2();
}

int main()
{
    e1();
    e2();
    pthread_t t;
    pthread_create(&t, NULL, thread, NULL);
    pthread_join(t, NULL);
	
    return 0;
}
