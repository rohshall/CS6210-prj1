/*
 * gt_uthread.h
 *
 *  Created on: Feb 3, 2012
 *      Author: sam
 */

#ifndef GT_UTHREAD_H_
#define GT_UTHREAD_H_

#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>

#include "gt_typedefs.h"

/* schedulers should detect and correct these defaults */
#define UTHREAD_ATTR_PRIORITY_DEFAULT -1
#define UTHREAD_ATTR_GROUP_DEFAULT -1

struct uthread_attr {
	int priority;
	uthread_gid group_id;
	struct timeval execution_time;
	struct timeval timeslice_start; // last time of day, used for bookkeeping
};

struct uthread_attr *uthread_attr_create(void);
void uthread_attr_set_elapsed_cpu_time(struct uthread_attr *attr);


enum uthread_state {
	UTHREAD_INIT,
	UTHREAD_RUNNABLE,
	UTHREAD_RUNNING,
	UTHREAD_DONE
};

typedef struct uthread {
	uthread_tid tid;
	enum uthread_state state;
	struct uthread_attr *attr;
	int (*start_routine)(void *);
	void *arg;

	sigjmp_buf env;
	stack_t stack;
} uthread_t;

int uthread_init(uthread_t *uthread);

/* Suspends the currently running uthread and causes the next to be scheduled */
void uthread_yield();

#endif /* GT_UTHREAD_H_ */