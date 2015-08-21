#include <stdbool.h>
#include <limits.h>

// trie struct declaration
struct trie {
    void* val; // void* pointing at this node's data
    struct trie* children[256]; // constant size array of 256 child tries (one for each character)
    enum {
        trienode_leaf = 0, // has no children
        trienode_twig, // has one child
        trienode_branch, // has more than one child
    } type; // hint about how many children there are
};

// creates a new trie and returns a pointer to that trie.
struct trie* trie_create();

// inserts val at key
void* trie_insert(struct trie* data, char* key, void* val);

// returns thing at key
void* trie_lookup(struct trie* data, char* key);

// returns thing at key matching prefix, if there are multiple matches, returns the ambiguous pointer
void* trie_lookup_prefix(struct trie* data, char* prefix, void* ambiguous);

// removes thing at key
void trie_remove(struct trie* data, char* key);

// destroys trie at pointer
void trie_destroy(struct trie* data);
