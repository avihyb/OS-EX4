#include <pthread.h>
#include <stdio.h>

int accum = 0;
pthread_mutex_t accum_mutex = PTHREAD_MUTEX_INITIALIZER;

void* square(void* arg) {
    int x = *((int*)arg);
    
    pthread_mutex_lock(&accum_mutex);
    accum += x * x;
    pthread_mutex_unlock(&accum_mutex);
    
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int x1 = 3, x2 = 4;
    
    pthread_create(&t1, NULL, square, &x1);
    pthread_create(&t2, NULL, square, &x2);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Final accum value: %d\n", accum);
    
    return 0;
}
