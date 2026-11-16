//
// Pepe Gallardo, Data Structures, UMA.
//

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "Scheduler.h"
#include "Task.h"
#include "test/unit/UnitTest.h"

void checkNullNode(const struct Node *p) {
	assert(p != NULL && "Pointer is null");
}

void checkNullDoublePointer(struct Node **p) {
	assert(p != NULL && "Null double pointer");
}

struct Node *Scheduler_new(void)
{
	return NULL;
}

size_t Scheduler_size(const struct Node *p_last)
{
	if(p_last == NULL) {
		return 0;
	}
	size_t counter = 1;
	struct Node *p_aux = p_last -> p_next;
	while(p_aux != p_last) {
		p_aux = p_aux -> p_next;
		counter++;
	}
	return counter;
}

void Scheduler_clear(struct Node **p_p_last)
{
	checkNullDoublePointer(p_p_last);
	if(*p_p_last == NULL) {
		return;
	}
	struct Node* p_aux = (*p_p_last) -> p_next;
	(*p_p_last) -> p_next = NULL;
	while(p_aux != NULL) {
		struct Node* p = p_aux -> p_next;
		free(p_aux);
		p_aux = p;
	}
	*p_p_last = NULL;
}

struct Task *Scheduler_first(const struct Node *p_last)
{
	checkNullNode(p_last);
	return Task_copyOf(&(p_last -> p_next -> task));
}

void Scheduler_enqueue(struct Node **p_p_last, const struct Task *p_task)
{
	checkNullDoublePointer(p_p_last);
	assert(p_task != NULL && "Null task pointer");

	struct Node* p_aux = malloc(sizeof(struct Node));
	checkNullNode(p_aux);
	p_aux -> task = *p_task;

	if(*p_p_last == NULL) {
		p_aux -> p_next = p_aux;
		*p_p_last = p_aux;
	} else {
		p_aux -> p_next = (*p_p_last) -> p_next;
		(*p_p_last) -> p_next = p_aux;
		*p_p_last = p_aux;
	}
}

void Scheduler_dequeue(struct Node **p_p_last)
{
	assert(p_p_last != NULL && "Null double pointer");
	checkNullNode(*p_p_last);
	struct Node* p_aux = (*p_p_last) -> p_next;
	checkNullNode(p_aux);
	if(*p_p_last == p_aux) {
		*p_p_last = NULL;
	} else {
		(*p_p_last) -> p_next = p_aux -> p_next;
	}
	free(p_aux);
}

void Scheduler_print(const struct Node *p_last)
{
  // already implemented
  printf("Scheduler(");
  if (p_last != NULL)
  {
    struct Node *p_first = p_last->p_next;
    struct Node *p_current = p_first;
    do
    {
      printf("\n  ");
      Task_print(&(p_current->task));
      p_current = p_current->p_next;
      printf(p_current != p_first ? "," : "\n");
    } while (p_current != p_first);
  }
  printf(")");
}
