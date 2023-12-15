#include <iostream>

#include "TasksExplicit.hpp"
#include "TasksImplicit.hpp"

using namespace std;

int main() {
	cout << "Explicit method: " << endl;

	TasksExplicitPerformer tasksExplicit;

	//while (tasksExplicit.hasMoreTasks()) {
		tasksExplicit.performTask();

	//	tasksExplicit.nextTask();
	//}

	cout << "Implicit method: " << endl;

	TasksImplicitPerformer tasksImplicit(1, 2, 3);
	tasksImplicit.performTask();

	return 0;
}