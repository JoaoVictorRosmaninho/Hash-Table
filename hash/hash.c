#include "hash.h"



unsigned int hashCalc(char *key) {
   	unsigned int h = 5381;
	while(*key) {
		h = ((h << 5) + h) + (*key);
        key++;
    }
	return h;
}

static inline unsigned int hashC(char *key, unsigned int tableSize) {
    return hashCalc(key) % tableSize + 1;
}
static inline unsigned int hashD(char *key, unsigned int tableSize)  {
    return hashCalc(key) % (tableSize - 2) + 1;
}

void resize(TableHash *table) {
    List **temp; 
    temp = (List **) calloc((table->size * GROWTH_FACTOR), sizeof(List *));
    for (int i = 0; i < table->size; i++)
        temp[i] = table->table[i];
    free(table->table);
    table->table = temp;
    table->size *= GROWTH_FACTOR;
}

void Insert(char *key, char *value, TableHash *table) {
    unsigned int hash = hashC(key, table->size);
    unsigned int hashAux = hashD(key, table->size);
   
    if (table->occupation_tax > LOAD_FACTOR)
        resize(table);
    while ((table->table[hash] != NULL) && (strcmp(key, table->key) != 0)) {
        hash += hashAux;      
        if (hash > table->size)
            hash -= table->size;
    }
    if (table->table[hash] == NULL) {
        
        table->table[hash] = initList();
        table->key = strdup(key);
    } else 
        table->occupation--;
    add(table->table[hash], value);
    table->occupation++;
    table->occupation_tax = (float) table->occupation / table->size;
}

void get(char *key, TableHash *table) {
    display(table->table[hashC(key, table->size)]);
}

void initHashTable(TableHash *table) {
    table->table = calloc((TABLE_SIZE * GROWTH_FACTOR), sizeof(List *));
    table->occupation = 0;
    table->occupation_tax = 0.0;
    table->key = NULL;
    table->size = TABLE_SIZE;
}