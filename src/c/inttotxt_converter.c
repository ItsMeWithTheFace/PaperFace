#define HT_SIZE 10

#include <pebble.h>
#include "src/c/hashtable.h"
#include "inttotxt_converter.h"

static hash_table_s *ones;
static hash_table_s *tens;

void populate_hashtables(){
	// Create the hashtables
	ones = create_hashtable(HT_SIZE);
	tens = create_hashtable(HT_SIZE);
	
	// Insert ones conversions into hashtable
	insert_keyvalue(ones, "1", "ONE");
	insert_keyvalue(ones, "2", "TWO");
	insert_keyvalue(ones, "3", "THREE");
	insert_keyvalue(ones, "4", "FOUR");
	insert_keyvalue(ones, "5", "FIVE");
	insert_keyvalue(ones, "6", "SIX");
	insert_keyvalue(ones, "7", "SEVEN");
	insert_keyvalue(ones, "8", "EIGHT");
	insert_keyvalue(ones, "9", "NINE");
	insert_keyvalue(ones, "0", "CLOCK");
	
	// Insert tens conversions into hashtable
	insert_keyvalue(tens, "10", "TEN");
	insert_keyvalue(tens, "20", "TWENTY");
	insert_keyvalue(tens, "30", "THIRTY");
	insert_keyvalue(tens, "40", "FOURTY");
	insert_keyvalue(tens, "50", "FIFTY");
}
