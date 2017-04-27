#include <pebble.h>
#include "hashtable.h"

hash_table_s *create_hash_table(int size) {
	int i;
	hash_table_s *new_table;
	
	// Allocate memory for the hashtable struct
	if ((new_table = malloc(sizeof(hash_table_s))) == NULL) {
		return NULL;
	}
	
	// Allocate memory for the entries
	if ((new_table->table = malloc(sizeof(entry_s *) * size)) == NULL) {
		return NULL;
	}
	
	// Initialize elements of the table
	for(i = 0; i < size; i++) new_table->table[i] = NULL;
	
	// Set the hashtable's size
	new_table->size = size;
	
	return new_table;
}


unsigned int hash(hash_table_s *hashtable, char *key) {
	unsigned int hashval = 0;	// Initialize it as 0 for hashing loop
	
	// Shift hashval left by 5 bits and add the current char to it
	for (; *key != '\0'; key++) {
		hashval = hashval << 5;
		hashval += *key;
	}
	
	// Apply mod so that result is in range of the size
	return hashval % hashtable->size;
}

char *get_value(hash_table_s *hashtable, char *key) {
	entry_s *entrys;
	unsigned int hashval = hash(hashtable, key);
	
	// After hashing the key find it in the hashtable and return corresponding value; else NULL
	for(entrys = hashtable->table[hashval]; entrys != NULL; entrys = entrys->next) {
		if(strcmp(key, entrys->key) == 0) {
			return entrys->value;
		} 
	}
	
	return NULL;
}

