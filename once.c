#include "once.h"

static void once_do_slow(Once *o, once_func ofn)
{
	pthread_mutex_lock(&o->m);
	if (o->done == 0) {
		o->done = 1;
		ofn();
	}
	pthread_mutex_unlock(&o->m);
}

void once_do(Once *o, once_func ofn)
{
	if (o->done == 0) {
		once_do_slow(o, ofn);
	}
}
