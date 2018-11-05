#ifndef LORA_TIMER_H
#define LORA_TIMER_H

#include "Arduino.h"
#include "List.h"

typedef void (*timer_callback_t)();

struct Task {

		unsigned long start;
		unsigned long every;
		timer_callback_t timerCallback;

		Task(unsigned long start, unsigned long every, timer_callback_t timerCallback)
						: start(start), every(every), timerCallback(timerCallback) {}

		void UpdateStart() { start += every; }
};

class Timer {

private:

		List<Task> taskList;

public:

		void schedule(long after, timer_callback_t timerCallback, unsigned long every=0);
		void update();
};


#endif //LORA_TIMER_H