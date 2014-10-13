#include <stdbool.h>
#include <limits.h>

// trie struct declaration
struct trie {
    void* val; // void* pointing at this node's data
    struct trie* children[256]; // constant size array of 256 child tries (one for each character)
};

// creates a new trie and returns a pointer to that trie.
struct trie* trie_create();

// inserts val at key
void* trie_insert(struct trie* data, char* key, void* val);

// returns thing at key
void* trie_lookup(struct trie* data, char* key);

// removes thing at key
void trie_remove(struct trie* data, char* key);

// destroys trie at pointer
void trie_destroy(struct trie* data);