//
// LIBHASH.C - part of libhash library
// by Rabbitlancer
//
// distibuted under GNU General Public License 3.0
//

#include "decl.h"

#define get16bits(d) (((unsigned int)((char *)(d)[1])<<8)\
				      +(unsigned int)((char *)(d)[0]))

static inline unsigned int get_input_length(char *input) {
	return sizeof(input)/sizeof(input[0]);
}

//FNV hash (classic)
unsigned long hash_fnv(char *input) {
	unsigned long hash = FNV_BASE;

	if (input == NULL) return ERRVAL;

	unsigned int len = get_input_length(input);

	for (unsigned int i = 0; i<len; i++) {
		hash *= FNV_MOD;
		hash ^= input[i];
	}

	return hash;
}

//FNV hash (swapped ops)
unsigned long hash_fnv_plus(char *input) {
	unsigned long hash = FNV_BASE;

	if (input == NULL) return ERRVAL;

	unsigned int len = get_input_length(input);

	for (unsigned int i = 0; i<len; i++) {
		hash ^= input[i];
		hash *= FNV_MOD;
	}

	return hash;
}

//Jenkins one-at-a-time hash
unsigned long hash_jenkins(char *input) {
	unsigned long hash = 0UL;

	if (input == NULL) return ERRVAL;

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

//"superfast" hash (found at http://www.azillionmonkeys.com/qed/hash.html)
//personal note:
//this one's hell of a complex for a "simple" hash function.
//beats me how come this one is faster than two above
unsigned long hash_superfast(char *input) {
	if (input == NULL) return ERRVAL;

	unsigned long hash = get_input_length(input);
	unsigned long tmp;
	unsigned int len = (unsigned int)hash, rem;

	rem = len & 3;
	len >>= 2;

	for (; len>0; len--) {
		hash += get16bits(input);
		tmp = (get16bits(input+2) << 11) ^ hash;
		hash = (hash << 16) ^ tmp;
		input += 4*sizeof(char);
		hash += hash >> 11;
	}

	switch (rem) {
		case 3:
			hash += get16bits(input);
			hash ^= hash << 16;
			hash ^= ((signed char)input[2*sizeof(char)]) << 18;
			hash += hash >> 11;
			break;
		case 2:
			hash += get16bits(input);
			hash ^= hash << 11;
			hash += hash >> 17;
			break;
		case 1:
			hash += (signed char)*input;
			hash ^= hash << 10;
			hash += hash >> 1;
	}

	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

	return hash;
}

//just a little something
inline char *return_rabbitlancer() {
	return "A LOGO IS COMING SOON!";
}