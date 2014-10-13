#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

// creates a new trie.
struct trie* trie_create()
{
    return malloc(sizeof(struct trie));
}

// returns pointer to thing at key
void* trie_traverse(struct trie* data, char* key)
{
    struct trie* current_node = data;

    // increment the pointer position of key until null terminator is reached
    while (*key != 0)
    {
        // try to find the correct child node
        struct trie* next_node = current_node->children[*key];

        // if next_node doesn't actually exist, return NULL
        if (!next_node) 
        {
            return NULL;
        }

        // set current node to the correct child node
        current_node = next_node;

        // increment key pointer position
        key++;
    }

    return current_node;
}

// inserts val at key
void* trie_insert(struct trie* data, char* key, void* val)
{
    struct trie* current_node = data;

    // increment the pointer position of key until null terminator is reached
    while (*key != 0)
    {
        // try to find the correct child node
        struct trie* next_node = current_node->children[*key];

        // if next_node doesn't actually exist, create it
        if (!next_node) 
        {
            current_node->children[*key] = trie_create();
            next_node = current_node->children[*key];
        }

        // set current node to the correct child node
        current_node = next_node;

        // increment key pointer position
        key++;
    }

    // set val at current_node
    current_node->val = val;

    return current_node;
}

// returns void pointer of thing at key
void* trie_lookup(struct trie* data, char* key)
{   
    struct trie* current_node = data;

    printf("looking up key %s\n", key);

    // increment the pointer position of key until null terminator is reached
    while (*key != 0)
    {
        printf("current prefix %c (%d)\n", *key, *key);

        // try to find the correct child node
        struct trie* next_node = current_node->children[*key];

        // if next_node doesn't actually exist, return NULL
        if (!next_node) 
        {
            return NULL;
        }

        // set current node to the correct child node
        current_node = next_node;

        // increment key pointer position
        key++;
    }

    return current_node->val;
}

// removes thing at key
void trie_remove(struct trie* data, char* key)
{
    struct trie* current_node = data;

    // increment the pointer position of key until null terminator is reached
    while (*key != 0)
    {
        // try to find the correct child node
        struct trie* next_node = current_node->children[*key];

        // if next_node doesn't actually exist, return NULL
        if (!next_node) 
        {
            return NULL;
        }

        // set current node to the correct child node
        current_node = next_node;

        // increment key pointer position
        key++;
    }

    free(current_node->val);
    return;
}

// destroys trie at pointer
void trie_destroy(struct trie* data)
{
    int a;
    for (a = 0; a < 256; a++)
    {
        if (data->children[a])
        {
            trie_destroy(data->children[a]);
        }
    }

    free(data);
    return;
}