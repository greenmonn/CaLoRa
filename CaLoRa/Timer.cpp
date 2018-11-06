#include "Timer.h"

void Timer::update() {

	List<Task>::Iterator iter = taskList.Begin();

	// for all tasks in task list
	while(iter != taskList.End()){

		// if task needs to be executed
		if((*iter).start <= millis()){
			(*iter).timerCallback();

			// if this task is not periodic, remove
			if((*iter).every == 0) {
				iter = taskList.Erase(iter);
			}
				// if periodic, update time
			else {
				(*iter).UpdateStart();
				iter++;
			}
		}
		else{
			iter++;
		}
	}
}

void Timer::schedule(long after, timer_callback_t timerCallback, unsigned long every) {

	Task newTask(after+millis(), every, timerCallback);
	taskList.Insert(taskList.Begin(), newTask);
}