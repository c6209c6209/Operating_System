#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define N 5
enum states {
    THINKING, EATING, HUNGRY
};

struct Philosophers {
    pthread_mutex_t lock;
    pthread_cond_t condition[N];
    enum states state[N];
};

struct Philosophers philosophers;

void *philosopher(void *philosopher_number);
void pickup_forks(int philosopher_number);
void test(int philosopher_number);
void return_forks(int philosopher_number);

int main() {
    pthread_t thread_id[N];
    int id[N];
    pthread_mutex_init(&philosophers.lock, NULL);

    for(int i = 0; i < N; i++) {
        philosophers.state[i] = THINKING;
        id[i] = i;
        pthread_cond_init(&philosophers.condition[i], NULL);
        pthread_create(&thread_id[i], NULL, &philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}

void *philosopher(void *philosopher_number) {
    int id = *(int *)philosopher_number;

    srand(time(NULL) + id);
    int think_time = rand() % 3 + 1;
	printf("Philosopher %d is now THINKING for %d seconds.\n", id, think_time);
	sleep(think_time);

	pickup_forks(id);
	int eat_time = rand() % 3 + 1;
    printf("Philosopher %d is now EATING.\n", id);
	sleep(eat_time);

	return_forks(id);
}

void pickup_forks(int philosopher_number) {
    pthread_mutex_lock(&philosophers.lock);

    philosophers.state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is now HUNGRY and trying to pick up forks.\n", philosopher_number);
    test(philosopher_number);

    if (philosophers.state[philosopher_number] != EATING) {
        printf("Philosopher %d can't pick up forks and start waiting.\n", philosopher_number);
        pthread_cond_wait(&philosophers.condition[philosopher_number], &philosophers.lock);
    }

    pthread_mutex_unlock(&philosophers.lock);
}

void test(int philosopher_number) {
    if (philosophers.state[philosopher_number] == HUNGRY &&
        philosophers.state[(philosopher_number+1)%N] != EATING &&
        philosophers.state[(philosopher_number+N-1)%N] != EATING)
    {
        philosophers.state[philosopher_number] = EATING;
        pthread_cond_signal(&philosophers.condition[philosopher_number]);
    }
}

void return_forks(int philosopher_number) {
    pthread_mutex_lock(&philosophers.lock);

    philosophers.state[philosopher_number] = THINKING;
    printf("Philosopher %d returns forks and then starts TESTING %d and %d.\n", 
            philosopher_number, (philosopher_number+N-1)%N, (philosopher_number+1)%N);

    test((philosopher_number+N-1)%N);
    test((philosopher_number+1)%N);

    pthread_mutex_unlock(&philosophers.lock);
}

