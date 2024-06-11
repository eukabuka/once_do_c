#ifndef _ONCE_H
#define _ONCE_H

#include <stdatomic.h>
#include <pthread.h>

typedef struct Once {
	_Atomic(int) done; // TODO: Ensure operations are atomic.
	pthread_mutex_t m;
} Once;

typedef void (*once_func)(void);

void once_do(Once *, once_func);

#define INIT_ONCE() {0, PTHREAD_MUTEX_INITIALIZER};

#endif /* _ONCE_H */

