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
