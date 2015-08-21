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

        switch (current_node->type)
        {
            case trienode_twig:
                // if this twig goes in the same direction
                if (next_node)
                {
                    break;
                }
                // else it will promote to a branch
            case trienode_leaf:
                current_node->type++;
        }

        // if next_node doesn't actually exist, create it
        if (!next_node) 
        {
            current_node->children[*key] = trie_create();
            next_node = current_node->children[*key];
            if (trienode_twig == current_node->type)
            {
                // children[0] is never used; we'll hijack it as a fast-forward key
                *current_node->children = next_node;
            }
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
    struct trie* current_node = trie_traverse(data, key);

    if (!current_node)
    {
        return NULL;
    }

    return current_node->val;
}

// If there is only one key that maches the given `char* prefix`, returns its value. If there are several, returns the given `void* ambiguous`, if there are none, returns null.
void* trie_lookup_prefix(struct trie* data, char* prefix, void* ambiguous)
{
    struct trie* current_node = trie_traverse(data, prefix);

    if (!current_node)
    {
        return NULL;
    }

    // exact match
    if(NULL!=current_node->val)
    {
        return current_node->val;
    }

    // prefix matched, but we still have to find the key itself
    while(NULL==current_node->val)
    {
        switch(current_node->type)
        {
            case trienode_leaf:
		// we can do nothing but return null
                return current_node->val;
            case trienode_twig:
		// fast-forward to the next (only) child
                current_node = *current_node->children;
		continue;
            case trienode_branch:
		return ambiguous;
        }
    }

    // we found a key with the requested prefix, but there are more
    if(trienode_twig==current_node->type)
    {
        return ambiguous;
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
    for (a = 1; a < 256; a++)
    {
        if (data->children[a])
        {
            trie_destroy(data->children[a]);
        }
    }

    free(data);
    return;
}
