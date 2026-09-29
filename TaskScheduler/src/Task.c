//
// Pepe Gallardo, Data Structures, UMA.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Task.h"
#include "test/unit/UnitTest.h"


void checkNull(const struct Task *p_task) {
	assert(p_task != NULL && "Task_print: NULL p_task");
}

struct Task *Task_new(unsigned int id, const char name[], unsigned int quantum)
{
	// todo
	assert(name != NULL && "Null name");
	assert(strlen(name) <= MAX_NAME_LEN && "Name is superior to the max length");
	assert(quantum > 0 && "Quantum is negative");
	struct Task *p_task = malloc(sizeof(struct Task));
	checkNull(p_task);
	strcpy(p_task -> name, name);
	p_task -> id = id;
	p_task -> quantum = quantum;
	return p_task;
}

void Task_free(struct Task **p_p_task)
{
	// todo
	assert(p_p_task != NULL && "Null double pointer");
	checkNull(*p_p_task);
	free(*p_p_task);
	*p_p_task = NULL;
}

struct Task *Task_copyOf(const struct Task *p_task)
{
	// todo
	checkNull(p_task);
	return Task_new(p_task -> id, p_task -> name, p_task -> quantum);
}

void Task_print(const struct Task *p_task)
{
	// already implemented
	checkNull(p_task);
	printf("Task(ID: %u, Name: %s, Quantum: %u)", p_task->id, p_task->name, p_task->quantum);
}
