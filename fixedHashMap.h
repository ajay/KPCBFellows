/*
 * Ajay Srivastava
 * fixedHashMap.h --> KPCB Fellows Application Problem
 */

#ifndef FIXEDHASHMAP
#define FIXEDHASHMAP

#include <stdbool.h>

struct entry
{
	char *key;
	void *value;
	struct entry *next;
};
typedef struct entry *entryPointer;

struct hashMap
{
	entryPointer *members;
	int size;
	char **keys;
};
typedef struct hashMap *hashMapPointer;

/* constructor(size):
 * return an instance of the class with pre-allocated space
 * for the given number of objects.
 */
hashMapPointer createNewHashMap(int size);

/* boolean set(key, value): stores the given key/value pair
 * in the hash map. Returns a boolean value indicating
 * success / failure of the operation.
 */
bool set(hashMapPointer hm, char *key, void *value);

/* get(key): return the value associated with the given key,
 * or null if no value is set.
 */
void* get(hashMapPointer hm, char *key);

/* delete(key): delete the value associated with the given
 * key, returning the value on success or null if the key
 * has no value.
 */
void* delete(hashMapPointer hm, char *key);

/* float load(): return a float value representing the load
 * factor (`(items in hash map)/(size of hash map)`) of the
 * data structure. Since the size of the dat structure is
 * fixed, this should never be greater than 1.
 */
float load(hashMapPointer hm);

void destroy(hashMapPointer hm);

#endif