//
// Pepe Gallardo, Data Structures, UMA.
//

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "LinkedStructure.h"


/// @brief Constructor for a new Node
/// @param element Element to be stored in node
/// @param p_next Pointer to next to be stored in node
/// @return Pointer to new node
static struct Node* Node_new(int element, struct Node* p_next) {
	struct Node* p_node = malloc(sizeof(struct Node));
	assert(p_node != NULL && "Node_new: not enough memory");

	p_node->element = element;
	p_node->p_next = p_next;
	return p_node;
}

/// @brief Destructor for a Node. Frees memory allocated for node and sets pointer to node to NULL
/// @param p_p_node Pointer to pointer to node to be freed
static void Node_free(struct Node** p_p_node) {
	free(*p_p_node);
	*p_p_node = NULL;
}

/// @brief Gets the pointer of the desired node at the index provided
/// @param p_first Pointer of the starting node
/// @param index The index of the node
/// @return The pointer of the node at the index
static struct Node* LinkedStructure_getPointer(struct Node* p_first, size_t index) {
	struct Node* p_aux = p_first;
	for(size_t i = 0; i < index; i++) {
		assert(p_aux != NULL && "Out of bounds");
		p_aux = p_aux -> p_next;
	}
	assert(p_aux != NULL && "Out of bounds");
	return p_aux;
}

struct Node* LinkedStructure_new(void) {
	return NULL;
}

struct Node* LinkedStructure_copyOf(const struct Node* p_first) {
	if(p_first == NULL) {
		return NULL;
	}
	struct Node* p_res = Node_new(p_first -> element, NULL);
	struct Node* p_aux = p_res;
	struct Node* p = p_first -> p_next;

	while(p != NULL) {
		p_aux -> p_next = Node_new(p -> element, NULL);
		p_aux = p_aux -> p_next;
		p = p -> p_next;
	}
	return p_res;
}

bool LinkedStructure_isEmpty(const struct Node* p_first) {
	return p_first == NULL;
}

size_t LinkedStructure_size(const struct Node* p_first) {
	size_t counter = 0;
	const struct Node* p_node = p_first;
	while(p_node != NULL) {
		counter++;
		p_node = p_node -> p_next;
	}
	return counter;
}

void LinkedStructure_clear(struct Node** p_p_first) {
	while(*p_p_first != NULL) {
		struct Node* p_aux = *p_p_first;
		*p_p_first = (*p_p_first) -> p_next;
		Node_free(&p_aux);
	}
}

void LinkedStructure_prepend(struct Node** p_p_first, int element) {
	// todo
	struct Node* p_node = Node_new(element, *p_p_first);
	*p_p_first = p_node;
}

void LinkedStructure_append(struct Node** p_p_first, int element) {
	// todo
	struct Node* p_node = Node_new(element, NULL);
	if(*p_p_first == NULL) {
		*p_p_first = p_node;
	} else {
		struct Node* p_last = *p_p_first;
		while(p_last -> p_next != NULL) {
		   	p_last = p_last -> p_next;
		}
		p_last -> p_next = p_node;
	}
}

void LinkedStructure_insert(struct Node** p_p_first, size_t index, int element) {
	// todo
	if(index == 0) {
		LinkedStructure_prepend(p_p_first, element);
		return;
	}
	struct Node* p_aux = LinkedStructure_getPointer(*p_p_first, index - 1);
	p_aux -> p_next = Node_new(element, p_aux -> p_next);
}

int LinkedStructure_get(const struct Node* p_first, size_t index) {
	const struct Node *p_aux = LinkedStructure_getPointer(
		(struct Node*) p_first, index
	);
	return p_aux->element;

}

void LinkedStructure_set(struct Node* p_first, size_t index, int element) {
	// todo
	struct Node* p_aux = LinkedStructure_getPointer(p_first, index);
	p_aux -> element = element;
}

void LinkedStructure_delete(struct Node** p_p_first, size_t index) {
	// todo
	assert(*p_p_first != NULL && "Empty LinkedStructure");
	if(index == 0) {
		struct Node* temp = *p_p_first;
		*p_p_first = (*p_p_first) -> p_next;
		Node_free(&temp);
	} else {
		struct Node* temp = LinkedStructure_getPointer(*p_p_first, index - 1);
		struct Node* target = temp -> p_next;
		assert(target != NULL && "Empty node");
		temp -> p_next = target -> p_next;
		Node_free(&target);
	}
}

void LinkedStructure_print(const struct Node* p_first) {
	printf("LinkedStructure(");
	for (const struct Node* p = p_first; p != NULL; p = p->p_next) {
		printf("%d", p->element);
		if (p->p_next != NULL) {
		    printf(", ");
		}
	}
	printf(")");
}
