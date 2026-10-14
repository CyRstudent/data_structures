#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "PlayList.h"
#include "test/unit/UnitTest.h"


struct PlayList* PlayList_new() {
	struct PlayList* res = malloc(sizeof(struct PlayList));
	assert(res != NULL && "Playlist_new(): Malloc failed");
	res -> p_playing = NULL;
	res -> p_first = NULL;
	return res;
}

// private function to allocate a new node on the heap
static struct Node* Node_new(const char* songName, struct Node* p_previous, struct Node* p_next) {
	struct Node* p_node = malloc(sizeof(struct Node));

	// Asserts go here
	assert(p_node != NULL && "Node_new(): not enough memory");
	assert(songName != NULL && "Node_new(): songName null");
	assert(strlen(songName) <= MAX_NAME_LENGTH && "Node_new(): songName too long");

	strcpy(p_node->songName, songName);
	p_node->p_next = p_next;
	p_node->p_previous = p_previous;
	if(p_next != NULL) {
		p_next -> p_previous = p_node;
	}
	if(p_previous != NULL) {
		p_previous -> p_next = p_node;
	}
	return p_node;
}

// Only call when adding the first song of an empty playlist
void PlayList_addFirstSong(struct PlayList* p_playlist, const char* songName)  {
	assert(p_playlist != NULL && "Null playlist");
	struct Node* p_aux = Node_new(songName, NULL, NULL);
	p_playlist -> p_first = p_aux;
	p_playlist -> p_playing = p_aux;
}

void PlayList_insertAtFront(struct PlayList* p_playList, const char* songName) {
	assert(p_playList != NULL && "PlayList_insertAtFront(): p_playList is NULL");
	struct Node* p_aux = p_playList -> p_first;
	if(p_aux == NULL) {
		PlayList_addFirstSong(p_playList, songName);
	} else {
		struct Node* p_new = Node_new(songName, NULL, p_aux);
		p_playList -> p_first = p_new;
	}
}

void PlayList_insertInOrder(struct PlayList* p_playList, const char* songName) {
	assert(p_playList != NULL && "PlayList_insertInOrder(): p_playList is NULL");
	if(p_playList -> p_first == NULL || p_playList -> p_playing == NULL) {
		PlayList_addFirstSong(p_playList, songName);
	} else {
		bool found = false;
		struct Node* p_aux = p_playList -> p_first;
		while(p_aux != NULL && !found) {
			found = strcmp(songName, p_aux -> songName) <= 0;
			if(!found) {
				p_aux = p_aux -> p_next;
			}
		}
		if(!found) {
			PlayList_insertAtEnd(p_playList, songName);
			return;
		}
		struct Node* p_res = Node_new(songName, p_aux -> p_previous, p_aux);
		p_aux -> p_previous = p_res;
		if(p_playList -> p_first == p_aux) {
			p_playList -> p_first = p_res;
		}
	}
}

void PlayList_insertAtEnd(struct PlayList* p_playList, const char* songName) {
	assert(p_playList != NULL && "PlayList_insertAtEnd(): p_playList is NULL");
	if(p_playList -> p_first == NULL || p_playList -> p_playing == NULL) {
		PlayList_addFirstSong(p_playList, songName);
	} else {
		struct Node* p_aux = p_playList -> p_playing;
		while(p_aux -> p_next != NULL) {
			p_aux = p_aux -> p_next;
		}
		p_aux -> p_next = Node_new(songName, p_aux, NULL);
	}
}

// private function to find node with a gigen song name in the playList.
// returns pointer to node containing such song or NULL if song is not in the playList.
static struct Node *FindNode(struct Node* p_first, const char* songName) {
    struct Node* p_current = p_first;
    while ((p_current != NULL) && (strcmp(songName, p_current->songName) != 0)) {
        p_current = p_current->p_next;
    }
    return p_current;
}

bool PlayList_insertAfter(struct PlayList* p_playList, const char* targetSong, const char* newSong) {
	assert(p_playList != NULL && "PlayList_insertAfter(): p_playList is NULL");
	struct Node* p_target = FindNode(p_playList -> p_first, targetSong);
	if(p_target == NULL) {
		return false;
	}
	Node_new(newSong, p_target, p_target -> p_next);
	return true;
}

bool PlayList_insertBefore(struct PlayList* p_playList, const char* targetSong, const char* newSong) {
	assert(p_playList != NULL && "PlayList_insertBefore(): p_playList is NULL");
	struct Node* p_target = FindNode(p_playList -> p_first, targetSong);
	if(p_target == NULL) {
		return false;
	}
	struct Node* p_res = Node_new(newSong, p_target -> p_previous, p_target);
	if(p_target == p_playList -> p_first) {
		p_playList -> p_first = p_res;
	}
	return true;
}

void PlayList_deleteFromFront(struct PlayList* p_playList) {
	assert(p_playList != NULL && "PlayList_deleteFromFront(): p_playList is NULL");
	assert(p_playList->p_first != NULL && "PlayList_deleteFromFront(): p_playList is empty");

	struct Node* p_del = p_playList -> p_first;
	struct Node* p_aux = p_del -> p_next;
	p_playList -> p_first = p_aux;

	if(p_aux != NULL) {
		p_aux -> p_previous = NULL;
		if(p_playList -> p_playing == p_del) {
			p_playList -> p_playing = p_aux;
		}
	} else {
		p_playList -> p_playing = NULL;
	}
	free(p_del);
}

bool PlayList_deleteSong(struct PlayList* p_playList, const char* songName) {
	assert(p_playList != NULL && "PlayList_deleteSong(): p_playList is NULL");
	struct Node* p_target = FindNode(p_playList -> p_first, songName);
	if(p_target == NULL) {
		return false;
	}
	if(p_target == p_playList -> p_first) {
		PlayList_deleteFromFront(p_playList);
		return true;
	}
	if(p_playList -> p_playing == p_target) {
		p_playList -> p_playing = p_playList -> p_first;
	}
	(p_target -> p_previous) -> p_next = p_target -> p_next;
	if(p_target -> p_next != NULL) {
		(p_target -> p_next) -> p_previous = p_target -> p_previous;
	}
	free(p_target);
	return true;
}

void PlayList_print(const struct PlayList* p_playList) {
    assert(p_playList != NULL && "PlayList_print(): p_playList is NULL");
    struct Node* p_current = p_playList->p_first;
    while (p_current != NULL) {
        printf("%s\n", p_current->songName);
        p_current = p_current->p_next;
    }
}

void swap(struct Node* p1, struct Node* p2) {
	char temp[MAX_NAME_LENGTH + 1];

	strcpy(temp, p1 -> songName);
	strcpy(p1 -> songName, p2 -> songName);
	strcpy(p2 -> songName, temp);
}

void PlayList_sort(struct PlayList* p_playList) {
	assert(p_playList != NULL && "PlayList_sort(): p_playList is NULL");
	// The time complexity for bubble sort is O(n²)
	// Now, instead of swapping the whole pointers and just reconnecting everything, we'll swap the data
	if(p_playList -> p_first == NULL || p_playList -> p_first -> p_next == NULL) {
		return;
	}

	bool swapped;
	struct Node* p_curr;
	do {
		swapped = false;
		p_curr = p_playList -> p_first;
		while(p_curr -> p_next != NULL) {
			if(strcmp(p_curr -> songName, p_curr -> p_next -> songName) > 0) {
				swap(p_curr, p_curr -> p_next);
				swapped = true;
			}
			p_curr = p_curr -> p_next;
		}
	} while(swapped);
}

void PlayList_deleteAll(struct PlayList* p_playList) {
	assert(p_playList != NULL && "PlayList_deleteAll(): p_playList is NULL");
	while(p_playList -> p_first != NULL) {
		PlayList_deleteFromFront(p_playList);
	}
}

char* PlayList_playingSong(const struct PlayList* p_playList) {
	assert(p_playList != NULL && "PlayList_playingSong(): p_playList is NULL");
	if(p_playList -> p_playing == NULL) {
		return NULL;
	}
	char* thingy = (char*) malloc(strlen(p_playList -> p_playing -> songName) + 1);
	assert(thingy != NULL && "Malloc failed");

	strcpy(thingy, p_playList -> p_playing -> songName);
	return thingy;
}

void PlayList_playNext(struct PlayList* p_playList) {
	assert(p_playList != NULL && "PlayList_playNext(): p_playList is NULL");
	if(p_playList -> p_playing != NULL && p_playList -> p_playing -> p_next != NULL) {
		p_playList -> p_playing = p_playList -> p_playing -> p_next;
	}
}

void PlayList_playPrevious(struct PlayList* p_playList) {
	assert(p_playList != NULL && "PlayList_playPrevious(): p_playList is NULL");
	if(p_playList -> p_playing != NULL && p_playList -> p_playing -> p_previous != NULL) {
		p_playList -> p_playing = p_playList -> p_playing -> p_previous;
	}
}

void PlayList_free(struct PlayList** p_p_playList) {
	assert(p_p_playList != NULL && "PlayList_free(): p_p_playList is NULL");
	assert(*p_p_playList != NULL && "PlayList_free(): Empty playlist");
	PlayList_deleteAll(*p_p_playList);
	free(*p_p_playList);
	*p_p_playList = NULL;
}
