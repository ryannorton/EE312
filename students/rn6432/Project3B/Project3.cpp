/*
 * Replace this comment with the standard EE312 file header!
 */

#include <assert.h>
#include <string.h>
#include "MemHeap.h"
#include "String.h"

/* use these two macros and the function functions if you want -- not required */
#define SIGNATURE (~0xdeadbeef)
#define STRING(s) (((String*)s)-1)

/* allocate a utstring on the heap, initialize the string correctly by copying
 * the characters from 'src' and return a pointer to the first character of actual string data */
char* utstrdup(const char* src) { int count; char* s;
	// determine size 
	uint32_t str_length = strlen(src);
	String* new_string = (String*) malloc(sizeof(String) + str_length + 1);
	(*new_string).length = str_length;
	(*new_string).capacity = str_length;
	(*new_string).check = ~0xdeadbeef;
	// write data
	for (count=0; count< str_length; count++) {
		(*new_string).data[count] = src[count];
	}
	// end string with null
	(*new_string).data[str_length] = 0;
	// return pointer to string
	s = (*new_string).data;
	return s;
}

/* the parameter 'utstr' must be a utstring. Find the length of this string by accessing the meta-data
 * and return that length */
uint32_t utstrlen(const char* utstr) {
	String* string = (String*)(utstr-12);
	uint32_t length = (*string).length;	
	return length;
}

/* s must be a utstring. suffix can be an ordinary string (or a utstring)
 * append the characters from suffix to the string s. Do not allocate any additional storage, and
 * only append as many characters as will actually fit in s. Update the length meta-data for utstring s
 * and then return s */
char* utstrcat(char* s, const char* suffix) { int i;
	String* string = (String*)(s-12);
	uint32_t capacity = (*string).capacity;
	uint32_t length = (*string).length;
	uint32_t available = capacity - length; // difference between capacity and length
	uint32_t suffix_length = strlen(suffix);
	uint32_t string_length = utstrlen(s);
	if (suffix_length <= available) { // there is enough space
		for (i=0; i<suffix_length; i++) {
			s[string_length] = suffix[i];
			string_length++;
		}
	}
	else { // not enough space
		for (i=0; i<available; i++) {
			s[string_length] = suffix[i];
			string_length++;
		}
	}
	// end string with null
	s[string_length] = 0;

	// update length
	*(s-4) = string_length;

	return s;
}

/* 'dst' must be a utstring. 'src' can be an ordinary string (or a utstring)
 * overwrite the characters in dst with the characters from src. Do not overflow the capacity of dst
 * For example, if src has five characters and dst has capacity for 10, then copy all five characters
 * However, if src has ten characters and dst only has capacity for 8, then copy only the first 8
 * characters. Do not allocate any additional storage, do not change capacity. Update the length
 * meta-data for dst and then return dst */
char* utstrcpy(char* dst, const char* src) { int i;
	String* string = (String*)(dst-12);
	uint32_t srclen = strlen(src); 
	uint32_t utcap = (*string).capacity;
	if (srclen <= utcap) { // src fits
		for (i=0; i<srclen; i++) {
			dst[i] = src[i];
			*(dst-4) = srclen; // update length
		}
		dst[srclen] = 0; // end string with null
	}
	else { // src doesn't fit
		for (i=0; i<utcap; i++) {
			dst[i] = src[i];
			*(dst-4) = utcap;
		}
		dst[utcap] = 0; // end string with null
	}
	return dst;
}

/* self must be a utstring. deallocate the storage for this string
 * (i.e., locate the start of the chunk and call free to dispose of the chunk, note that the start of
 * the chunk will be 12 bytes before *self) */
void utstrfree(char* self) {
	free(self-12);
}

/* s must be a utstring.
 * ensure that s has capacity at least as large as 'new_capacity'
 * if s already has capacity equal to or larger than new_capacity, then return s
 * if s has less capacity than new_capacity, then allocate new storage with sufficient space to store
 * new_capacity characters (plus a terminating zero), copy the current characters from s into this
 * new storage. Update the meta-data to correctly describe new new utstring you've created, deallocate s
 * and then return a pointer to the first character in the newly allocated storage */
char* utstrrealloc(char* s, uint32_t new_capacity) {
	String* string = (String*)(s-12);
	uint32_t capacity = (*string).capacity;
	//uint32_t capacity = (uint32_t) *(s-8);
	if (capacity >= new_capacity) {
		return s;
	}
	else {
		uint32_t str_length = utstrlen(s);
		String* new_string = (String*) malloc(sizeof(String) + new_capacity + 1);
		(*new_string).length = str_length;
		(*new_string).capacity = new_capacity;
		(*new_string).check = ~0xdeadbeef;
		// write data
		utstrcpy((*new_string).data, s);
		// deallocate old string
		utstrfree(s);
		// return pointer to string
		return (*new_string).data;	
	}
}

int32_t utstrcmp(const char* s1, const char* s2) { char a, b;
	int i = 0;
	while (true) {
		a = s1[i];
		b = s2[i];
		if (a == 0) {
			if (b == 0) {
				return 0;
			}
			else {
				return -1;
			}
		}
		else if (b == 0) {
			return 1;
		}
		else if (a < b) {
			return -1;
		}
		else if (a > b) {
			return 1;
		}
		i++;
	}
}



