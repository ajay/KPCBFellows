# KPCBFellows

/*
 * Ajay Srivastava
 * README --> KPCB Fellows Application Problem
 */

About
-----
This implementation creates a hashMap in C using void* pointers to hold object data. The hashMap is accessible by importing the 'fixedHashMap.h' file into the program you would like to use it with. C was chosen because it would make this implementation very fast, as well as memory efficient, as memory could be dynamically allocated as needed and removed when not in use anymore.


Data
----
There are two structs that exist in this implementation, one to hold the actual hashMap and another that serves as each entry in the hashMap.


Memory Efficiency
-----------------
In this implementation, memory is dynamically allocated as needed as data/objects are fed into the hashMap. Similarly, as data are removed, the memory that was allocated for these objects is freed. At the termination of the program, the destory(hashMapPointer hm) function should be called to free any additional objects or data that were not removed prior to termination.

Functions
---------
The following functions were implemented:

	hashMapPointer createNewHashMap(int size);

	bool set(hashMapPointer hm, char *key, void *value);

	void* get(hashMapPointer hm, char *key);

	void* delete(hashMapPointer hm, char *key);

	float load(hashMapPointer hm);

	void destroy(hashMapPointer hm);

Usage
-----
The attached hashMapRunner.c file shows basic usage of the hashMap implementation. It can be compiled and run using the included makefile on *nix systems, by executing the command 'make'. Then hashMapRunner can be executed by running ./hashMapTest . If we use the utility valgrind to run the program, we can see the amount of memory used, and how the program behaves when we choose to remove and add objects into the hashTable. For example, if we comment out the 'destroy(hashMap);' at the end of 'hashMapRunner.c', we can see how memory was free'd when we removed the keys "one", "two", and "three" from the hashMap.