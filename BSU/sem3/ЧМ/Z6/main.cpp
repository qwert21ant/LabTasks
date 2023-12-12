#include <iostream>

#include "Tasks.hpp"

using namespace std;


int main() {
	TasksPerformer tasks;

	while (tasks.hasMoreTasks()) {
		tasks.performTask();

		tasks.nextTask();
	}

	return 0;
}