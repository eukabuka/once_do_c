#include <stdio.h>

#include "once.h"

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
// #define WCOUNT 32755
#define WCOUNT 99999
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
