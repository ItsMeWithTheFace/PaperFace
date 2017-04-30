#include <pebble.h>
#include <string.h>
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

entry_s *get_entry(hash_table_s *hashtable, char *key) {
	entry_s *entrys;
	unsigned int hashval = hash(hashtable, key);
	
	// After hashing the key find it in the hashtable and return corresponding value; else NULL
	for(entrys = hashtable->table[hashval]; entrys != NULL; entrys = entrys->next) {
		if(strcmp(key, entrys->key) == 0) {
			return entrys;
		} 
	}
	
	return NULL;
}

int insert_keyvalue(hash_table_s *hashtable, char *key, char *value) {
	entry_s *new_entry;
	entry_s *existing_entry;
	unsigned int hashval = hash(hashtable, key);
	
	// Allocate memory for new entry
	if ((new_entry = malloc(sizeof(entry_s))) == NULL) return 1;
	
	// Check if item already exists
	// If so, do not insert and return error code 17 
	// (see errno-base.h for error code details)
	if ((existing_entry = get_entry(hashtable, key)) != NULL) return 17;

	// Insert into hashtable at the beginning of linked list
	strcpy(new_entry->key, key);
	strcpy(new_entry->value, value);
	new_entry->next = hashtable->table[hashval];	// new entry points to original head
	hashtable->table[hashval] = new_entry;			// new entry becomes head
	
	return 0;
}

void free_hashtable(hash_table_s *hashtable) {
	int i;
	entry_s *entry_to_free, *rest;
	
	// Iterate through linked list and free each element and their strings
	for (i = 0; i < hashtable->size; i++) {
		entry_to_free = hashtable->table[i];
		while (entry_to_free != NULL) {
			rest = entry_to_free->next;
			free(entry_to_free->key);
			free(entry_to_free->value);
			free(entry_to_free);
			entry_to_free = rest;
		}
	}
}

