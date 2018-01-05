#pragma once

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

// bkdr hash method that is used to hash a string usually.
int bkdr_hash(char *key) {
    uint seed = 1313; // it can be 13 131 1313 131313 etc.
    uint hash = 0;

    while( *key != '\n' && *key != 0) {
        hash = hash * seed  + (*key++);
    }

    return ( hash & 0x7FFFFFFF );
}

// use zippers to deal with hash conficit.
typedef struct _htSlot{
    struct _htSlot* next;
    char *key;
    uint value;
} htSlot;

uint ht_index(char *key, htSlot **ht) {
    uint hashed_key =  bkdr_hash(key);
    uint length = ht[0]->value - 1;
    return hashed_key % length + 1;
}

// record hash table length with the first element.
// eg: htSlot *ht[21]
void ht_init(htSlot **ht, uint length) {
    ht[0] = (htSlot *)malloc(sizeof(htSlot));
    ht[0]->key = NULL;
    ht[0]->value = length;
    for(uint i = 1; i < length; i++) {
        ht[i] = NULL;
    }
}

// insert or update a element.
uint ht_set(char *key, uint value, htSlot **ht) {
    uint slot_id = ht_index(key, ht);
    htSlot *item = ht[slot_id];
    while(item) {
        if(0 == strcmp(key, item->key)) {
            item->value = value;
            break;
        }

        if(NULL == item->next) {
            item->next = (htSlot *)malloc(sizeof(htSlot));
            item->key = key;
            item->value = value;
            break;
        }
    }

    return 0;
}

htSlot *ht_get(char *key, htSlot **ht) {
    uint slot_id = ht_index(key, ht);
    htSlot *item = ht[slot_id];
    while()
}
