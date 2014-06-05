/*
 * rttimer.h
 *
 *  Created on: Jun 5, 2014
 *      Author: pv
 */

#ifndef RTTIMER_H_
#define RTTIMER_H_

#define BYTES_PER_TICK 1764
#define MS_PER_TICK 10
#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN


int timer_setup(void);
int timer_remove(void);
void timer_wait_for_tick(void);

#endif /* RTTIMER_H_ */
