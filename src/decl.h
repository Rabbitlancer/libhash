//
// DECL.H - part of libhash library (function prototypes)
// by Rabbitlancer
//
// distibuted under GNU General Public License 3.0
//

/*
	This library is a collection of simple non-
	cryptographic hash functions. Currently,
	these functions are available:
	- FNV hash (both classic and "plus" versions);
	- Jenkins one-at-a-time hash;
	- "superfast" hash (not tested).
	More to come.

	All of the provided functions take a string
	(or other buffer pointer) as an argument
	and return hash value or 0 on error (bad
	buffer).
*/

#include <stdlib.h> //NULL

//this stuff is internal

static inline unsigned int get_input_length(char *input);
//function prototypes:
unsigned long hash_fnv(char *input);
unsigned long hash_fnv_plus(char *input);
unsigned long hash_jenkins(char *input);
unsigned long hash_superfast(char *input);

//a little bonus
inline char *return_rabbitlancer();