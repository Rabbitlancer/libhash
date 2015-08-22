//
// LIBHASH.C - (sole) part of libhash library
// by Rabbitlancer
//
// distibuted under GNU General Public License 3.0
//

#include <stdlib.h> //NULL

static inline unsigned int get_input_length(char *input) {
	return sizeof(input)/sizeof(input[0]);
}

unsigned long hash_fnv(char *input) { //FNV hash
	unsigned long hash = 14695981039346656037UL;

	if (input == NULL) return 0UL;

	unsigned int len = get_input_length(input);

	for (unsigned int i = 0; i<len; i++) {
		hash ^= input[i];
		hash *= 1099511628211UL;
	}

	return hash;
}

unsigned long hash_jenkins(char *input) { //Jenkins one-at-a-time hash
	unsigned long hash = 0UL;

	if (input == NULL) return 0UL;

	unsigned int len = get_input_length(input);

	for (unsigned int i = 0; i<len; i++) {
		hash += input[i];
		hash += (hash<<10);
		hash ^= (hash>>6);
	}

	hash += (hash<<3);
	hash ^= (hash>>11);
	hash += (hash<<15);

	return hash;
}