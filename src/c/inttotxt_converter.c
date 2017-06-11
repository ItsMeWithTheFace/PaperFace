#define HT_SIZE 10

#include <pebble.h>
#include <string.h>
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
	insert_keyvalue(ones, "0", "CLOCK");	// If minutes in the form of XX:X0
	
	// Insert tens conversions into hashtable
	insert_keyvalue(tens, "0", "O'");		// if minutes in the form of XX:0X
	insert_keyvalue(tens, "10", "TEN");
	insert_keyvalue(tens, "11", "ELEVEN");
	insert_keyvalue(tens, "12", "TWELVE");
	insert_keyvalue(tens, "13", "THIRTEEN");
	insert_keyvalue(tens, "14", "FOURTEEN");
	insert_keyvalue(tens, "15", "FIFTEEN");
	insert_keyvalue(tens, "16", "SIXTEEN");
	insert_keyvalue(tens, "17", "SEVENTEEN");
	insert_keyvalue(tens, "18", "EIGHTEEN");
	insert_keyvalue(tens, "19", "NINETEEN");
	insert_keyvalue(tens, "20", "TWENTY");
	insert_keyvalue(tens, "30", "THIRTY");
	insert_keyvalue(tens, "40", "FOURTY");
	insert_keyvalue(tens, "50", "FIFTY");
}

void destroy_hashtables(){
	free_hashtable(ones);
	free_hashtable(tens);
}

char ** tokenize(char * curr_time){
	// assumes time is of format HH:MM
	const char delimiter = ":";
	char [2][5] tokenized_time;
	char *token;

	// getting the first token (hours)
	token = strtok(curr_time, delimiter);
	strcpy(tokenized_time[0], token);

	//getting the second token (minutes)
	token = strtok(NULL, delimiter);
	strcpy(tokenized_time[1], token);

	return tokenized_time;
}
