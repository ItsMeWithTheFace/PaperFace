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

extern hash_table_s *create_hashtable(int size);
extern unsigned int hash(hash_table_s *hashtable, char *key);
extern entry_s *get_entry(hash_table_s *hashtable, char *key);
extern int insert_keyvalue(hash_table_s *hashtable, char *key, char *value);
extern void free_hashtable(hash_table_s *hashtable);
