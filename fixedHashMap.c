/*
 * Ajay Srivastava
 * fixedHashMap.c --> KPCB Fellows Application Problem
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fixedHashMap.h"

#define reset	"\x1b[0m"
#define	red		"\x1b[31m"
#define green	"\x1b[32m"

// Hash Function obtained from http://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hashFunction(hashMapPointer hm, char *string)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *string++))
	{
		hash = ((hash << 5) + hash) + c;
	}

	return (hash % hm->size);
}

void destroy(hashMapPointer hm)
{
	for (int i=0; i<hm->size; i++)
	{
		if (hm->keys[i] != NULL)
		{
			if (strcmp(hm->keys[i], "\0") != 0)
			{
				delete(hm, hm->keys[i]);
			}
		}
	}

	for (int i=0; i<hm->size; i++)
	{
		if (hm->keys[i] != NULL)
		{
			free(hm->keys[i]);
		}
	}

	free(hm->keys);
	free(hm->members);
	free(hm);
}

void removeFromKeyList(hashMapPointer hm, char *key)
{
	for (int i=0; i<hm->size; i++)
	{
		if ((hm->keys[i] != NULL) && (strcmp(hm->keys[i], "\0") != 0))
		{
			if (strcmp(hm->keys[i], key) == 0)
			{
				strcpy(hm->keys[i], "\0");
			}
		}
	}
}

/* constructor(size):
 * return an instance of the class with pre-allocated space
 * for the given number of objects.
 */
hashMapPointer createNewHashMap(int size)
{
	if (size <= 0)
		printf(red "ERROR: Can not allocate a " green "%d" red " hashMap\n" reset, size);

	hashMapPointer hm = (hashMapPointer) malloc(sizeof(struct hashMap));
	hm->members = malloc(size*sizeof(entryPointer));
	hm->keys = malloc(size * sizeof(char*));

	for (int i=0; i<size; i++)
	{
		hm->keys[i] = NULL;
	}

	for (int i=0; i<size; i++)
	{
		hm->members[i] = NULL;
	}
	hm->size = size;
	return hm;
}

/* boolean set(key, value): stores the given key/value pair
 * in the hash map. Returns a boolean value indicating
 * success / failure of the operation.
 */
bool set(hashMapPointer hm, char *key, void *value)
{
	if (hm == NULL)
	{
		printf(red "ERROR: Need a hashMap to load into\n" reset);
		return false;
	}

	if (key == NULL)
	{
		printf(red "ERROR: Need a key to load into hashMap\n" reset);
		return false;
	}

	if (value == NULL)
	{
		printf(red "ERROR: Need a value to load into hashMap\n" reset);
		return false;
	}

	int index = 0;
	while (hm->keys[index] != NULL)
	{
		index++;
	}

	hm->keys[index] = malloc(strlen(key)+1);
	strcpy(hm->keys[index], key);

	int i = hashFunction(hm, key);

	if (hm->members[i] != NULL)
	{
		entryPointer tempEntryPointer = hm->members[i];
		while (tempEntryPointer->next != NULL)
		{
			tempEntryPointer = tempEntryPointer->next;
		}

		entryPointer newNode = malloc(sizeof(struct entry));
		newNode->key = malloc(strlen(key)+1);
		strcpy(newNode->key, key);
		newNode->value = value;
		newNode->next = NULL;
		tempEntryPointer->next = newNode;
		return true;
	}
	else
	{
		hm->members[i] = malloc(sizeof(struct entry));
		hm->members[i]->key = malloc(strlen(key)+1);
		strcpy(hm->members[i]->key, key);
		hm->members[i]->value = value;
		hm->members[i]->next = NULL;
		return true;
	}

	return false;
}

/* get(key): return the value associated with the given key,
 * or null if no value is set.
 */
void* get(hashMapPointer hm, char *key)
{
	int i = hashFunction(hm, key);
	if (hm->members[i] == NULL)
	{
		printf(red "ERROR: Can not find an entry in hashMap with key: " green "%s\n" reset, key);
		return NULL;
	}

	entryPointer tempEntryPointer = hm->members[i];
	while (tempEntryPointer != NULL)
	{
		if (strcmp(tempEntryPointer->key, key) == 0)
		{
			return tempEntryPointer->value;
		}
		tempEntryPointer = tempEntryPointer->next;
	}

	printf(red "ERROR: Can not find an entry in hashMap with key: " green "%s\n" reset, key);
	return NULL;
}

/* delete(key): delete the value associated with the given
 * key, returning the value on success or null if the key
 * has no value.
 */
void* delete(hashMapPointer hm, char *key)
{
	int i = hashFunction(hm, key);
	if (hm->members[i] == NULL)
	{
		printf(red "ERROR: Can not find an entry in hashMap with key: " green "%s\n" reset, key);
		return NULL;
	}

	if (strcmp(hm->members[i]->key, key) == 0)
	{
		entryPointer tempEntryPointer = hm->members[i];
		hm->members[i] = (entryPointer)hm->members[i]->next;
		void *val = tempEntryPointer->value;
		free(tempEntryPointer->key);
		free(tempEntryPointer);
		removeFromKeyList(hm, key);
		return val;
	}

	entryPointer tempEntryPointer = hm->members[i];
	while (tempEntryPointer != NULL)
	{
		entryPointer previous = tempEntryPointer;
		if (strcmp(tempEntryPointer->key, key) == 0)
		{
			void *val = tempEntryPointer->value;
			previous->next = tempEntryPointer->next;
			free(tempEntryPointer->key);
			free(tempEntryPointer);
			removeFromKeyList(hm, key);
			return val;
		}
		tempEntryPointer = tempEntryPointer->next;
	}

	printf(red "ERROR: Can not find an entry in hashMap with key: " green "%s\n" reset, key);
	return NULL;
}


/* float load(): return a float value representing the load
 * factor (`(items in hash map)/(size of hash map)`) of the
 * data structure. Since the size of the dat structure is
 * fixed, this should never be greater than 1.
 */
float load(hashMapPointer hm)
{
	int items = 0;

	for (int i=0; i<hm->size; i++)
	{
		if (hm->keys[i] != NULL)
		{
			if (strcmp(hm->keys[i], "\0") != 0)
			{
				items++;
			}
		}
	}

	return  (float)((float)items / (float)hm->size);
}