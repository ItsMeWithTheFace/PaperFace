#include <pebble.h>

typedef struct _entry_s {		// Entry that will be held inside hashtable
	char *key;					// Identifier of the value
	char *value;
	struct _entry_s *next;
} entry_s;

typedef struct _hash_table_s {
	int size;			// Size of the hashtable
	entry_s **table;	// Elements in table
} hash_table_s;
