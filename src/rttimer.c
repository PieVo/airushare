#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>

#include "rttimer.h"
#include "trace.h"

timer_t timer_id;
sem_t sem;

static void handler(int sig, siginfo_t *si, void *uc)
{
	sem_t *sem = si->si_value.sival_ptr;
	sem_post(sem);
}

int timer_remove(void)
{
	sigset_t mask;
	int status;

	log_verbose("Removing timer\n");
    status = timer_delete(timer_id);
    if (status == -1) {
        log_verbose ("Error deleting timer");
        return -1;
    }

    sem_destroy(&sem);
	return 0;
}

int timer_setup(void)
{
	int status;
	struct itimerspec ts;
	struct sigevent se;
	sigset_t mask;
	struct sigaction sa;

	sem_init(&sem, 0, 0);
	log_verbose("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIG, &sa, NULL) == -1) {
		log_verbose ("sigaction failed\n");
		return -1;
	}

	se.sigev_notify = SIGEV_SIGNAL;
	se.sigev_signo = SIG;
	se.sigev_value.sival_ptr = &sem;

	log_verbose ("Creating timer\n");
    status = timer_create(CLOCKID, &se, &timer_id);
    if (status == -1) {
        log_verbose ("Error creating timer");
        return -1;
    }
    log_verbose ("timer ID is 0x%lx\n", (long) timer_id);

    ts.it_value.tv_sec = 1;
	ts.it_value.tv_nsec = 0;
	ts.it_interval.tv_sec = 0;
	ts.it_interval.tv_nsec = MS_PER_TICK * 1000 * 1000;

    status = timer_settime(timer_id, 0, &ts, NULL);
    if (status == -1) {
        log_verbose ("Error setting timer");
        return -1;
    }

    return 0;
}

void timer_wait_for_tick(void)
{
	sem_wait(&sem);
}
