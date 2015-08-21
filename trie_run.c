#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

// quick and dirty test cases for trie

int main(int argc, char* argv[])
{

	int *a, *b, *c, *d;
	a = malloc(sizeof(int));
	*a = 1;
	b = malloc(sizeof(int));
	*b = 2;
	c = malloc(sizeof(int));
	*c = 3;
	d = malloc(sizeof(int));
	*d = 4;

	struct trie* test_trie = trie_create();
	printf("created new trie at %p\n", test_trie);
	
	void* inserted = trie_insert(test_trie, "aa", a);
	printf("inserted %d at %p\n", *a, inserted);

	int *trie_value = trie_lookup(test_trie, "aa");
	printf("lookup got %d\n", *trie_value);

	inserted = trie_insert(test_trie, "ab", b);
	printf("inserted %d at %p\n", *a, inserted);

	trie_value = trie_lookup(test_trie, "ab");
	printf("lookup got %d\n", *trie_value);

	inserted = trie_insert(test_trie, "ccz", c);
	printf("inserted %d at %p\n", *a, inserted);

	trie_value = trie_lookup(test_trie, "ccz");
	printf("lookup got %d\n", *trie_value);

	trie_value = trie_lookup_prefix(test_trie, "c", NULL);
	printf("prefix lookup got %d\n", *trie_value);

	trie_value = trie_lookup_prefix(test_trie, "a", d);
	printf("ambiguous prefix lookup got %d\n", *trie_value);

	trie_destroy(test_trie);
	printf("freed trie\n");
	
	return 0;
}
