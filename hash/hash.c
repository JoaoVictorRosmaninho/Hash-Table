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
        temp[i] = table->values[i];
    free(table->values);
    table->values = temp;
    table->size *= GROWTH_FACTOR;
}

void Insert(char *key, List *value, TableHash *table) {
    unsigned int hash = hashC(key, table->size);
    unsigned int hashAux = hashD(key, table->size);
   
    if (table->occupation_tax > LOAD_FACTOR)
        resize(table);
    while ((table->values[hash] != NULL)) {
        hash += hashAux;      
        if (hash > table->size)
            hash -= table->size;
    }
    if (table->values[hash] != NULL) return; // posicao já ocupada 
    value->key = strdup(key);
    table->values[hash] = value;
    table->occupation++;
    table->occupation_tax = (float) table->occupation / table->size;
}

void get(char *key, TableHash *table) {
    display(table->values[hashC(key, table->size)]);
}

void initHashTable(TableHash *table) {
    table->values = (List **) calloc(TABLE_SIZE, sizeof(List *));
    table->occupation = 0;
    table->occupation_tax = 0.0;
    table->size = TABLE_SIZE;
}