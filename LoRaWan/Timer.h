#ifndef LORA_TIMER_H
#define LORA_TIMER_H

// TODO: implement timer class, schedule, update methods

typedef void (*timer_callback_t)();

class Timer {

private:

		// TODO: add list of task here

public:

		void schedule(long after, timer_callback_t timerCallback, unsigned long start=0, unsigned long every=0);
		void update();
};


#endif //LORA_TIMER_H