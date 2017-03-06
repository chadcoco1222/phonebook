#include <stdlib.h>
#include <string.h>

#include "phonebook_hash.h"

entry *findName(char lastName[], entry *e[])
{
    unsigned int hashValue = BKDRHash(lastName);

    while (e[hashValue] != NULL) {
        if (!strcasecmp(lastName, e[hashValue]->lastName))
            return e[hashValue];
        e[hashValue] = e[hashValue]->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e[])
{
    unsigned int hashValue = BKDRHash(lastName);
    entry *tmp;

    if (!e[hashValue]) {
        e[hashValue] = (entry *) malloc(sizeof(entry));
        e[hashValue]->pNext = NULL;
        strcpy(e[hashValue]->lastName, lastName);
    } else {
        tmp = (entry *) malloc(sizeof(entry));
        e[hashValue]->pNext = tmp;
        tmp->pNext = NULL;
        strcpy(tmp->lastName, lastName);
    }
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF) % TABLE_SIZE;
}
