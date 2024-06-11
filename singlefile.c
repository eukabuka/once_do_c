#include <stdatomic.h>
#include <stdio.h>
#include <pthread.h>

typedef struct Once {
	_Atomic(int) done; // TODO: Ensure operations are atomic.
	pthread_mutex_t m;
} Once;

void once_do_slow(Once *o, void (*once_func)(void))
{
	pthread_mutex_lock(&o->m);
	if (o->done == 0) { // TODO: Atomic load, use qatomic_read().
		o->done = 1; // Use qatomic_set().
		once_func();
	}
	pthread_mutex_unlock(&o->m);
}

void once_do(Once *o, void (*once_func)(void))
{
	if (o->done == 0) { // TODO: Atomic load, use qatomic_read().
		once_do_slow(o, once_func);
	}
}

#define INIT_ONCE() {0, PTHREAD_MUTEX_INITIALIZER};

// User.
void dummy_once_func(void)
{
	printf("only once wheeee\n");
}

void *thread(void *ptr)
{
	Once *o = (Once *)ptr;
	once_do(o, dummy_once_func);
	return NULL;
}
#define WCOUNT 32755
pthread_t ts[WCOUNT];
void workers(Once *o)
{
	int i;
	for (i = 0; i < WCOUNT; i++) {
		pthread_create(&ts[i], NULL, thread, o);
	}
	for (i = 0; i < WCOUNT; i++) {
		pthread_join(ts[i], NULL);
	}
}

int main(int argc, char **argv)
{
	Once o = INIT_ONCE();
	workers(&o);
	return 0;
}
