/*
 * Ajay Srivastava
 * hashMapRunner.c --> KPCB Fellows Application Problem
 */

#include <stdio.h>
#include <stdint.h>
#include "fixedHashMap.h"

int main(int argc, char **argv)
{
	hashMapPointer hashMap = createNewHashMap(10);

	int64_t one = 1;
	int64_t two = 2;
	int64_t three = 3;
	int64_t four = 4;
	int64_t five = 5;
	int64_t big = 1463786218743;

	set(hashMap, "one", (void *)one);
	set(hashMap, "two", (void *)two);
	set(hashMap, "three", (void *)three);
	set(hashMap, "four", (void *)four);
	set(hashMap, "five", (void *)five);
	set(hashMap, "veryBigNumber", (void *)big);

	printf("key: one --> \tvalue: %ld\n", (int64_t)get(hashMap, "one"));
	printf("key: two --> \tvalue: %ld\n", (int64_t)get(hashMap, "two"));
	printf("key: three --> \tvalue: %ld\n", (int64_t)get(hashMap, "three"));
	printf("key: four --> \tvalue: %ld\n", (int64_t)get(hashMap, "four"));
	printf("key: five --> \tvalue: %ld\n", (int64_t)get(hashMap, "five"));
	printf("key: veryBigNumber --> \tvalue: %ld\n", (int64_t)get(hashMap, "veryBigNumber"));

	printf("Load of Hashmap: %f\n", load(hashMap));

	delete(hashMap, "one");
	delete(hashMap, "two");
	delete(hashMap, "three");
	// delete(hashMap, "four");
	// delete(hashMap, "five");
	// delete(hashMap, "veryBigNumber");

	destroy(hashMap);
	return 0;
}