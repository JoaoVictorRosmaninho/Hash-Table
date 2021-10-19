#include "hash.h"



unsigned int hashCalc(char *key) {
    unsigned int hash = 5381;
	int c;
	while ((c = *key++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}

unsigned int hashC(char *key, unsigned int tableSize) {
    return hashCalc(key) % tableSize;
}
static inline unsigned int hashD(char *key, unsigned int tableSize)  {
    return hashCalc(key) % (tableSize - 2);
}

void resize(TableHash *table) {
    List **temp; 
    temp = (List **) calloc((table->size * GROWTH_FACTOR), sizeof(List *));
    for (int i = 0; i < table->size; i++)
        if (table->values[i] != NULL) {
            unsigned int new_size = table->size * GROWTH_FACTOR;
            unsigned int hash = hashC(table->values[i]->key, new_size);
            unsigned int hashAux = hashD(table->values[i]->key, new_size);
            while(temp[hash] != NULL) {
                hash += hashAux;      
                if (hash > new_size)
                    hash -= new_size;
            }
            temp[hash] = table->values[i];
        }
    free(table->values);
    table->values = temp;
    table->size *= GROWTH_FACTOR;
}

void Insert(char *key, List *value, TableHash *table) {   
    if (table->occupation_tax > LOAD_FACTOR)
        resize(table);

    unsigned int hash = hashC(key, table->size);
    unsigned int hashAux = hashD(key, table->size);
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
    unsigned int hash = hashC(key, table->size);
    unsigned int hashAux = hashD(key, table->size);
    while ((table->values[hash] != NULL) && (strcmp(key, table->values[hash]->key) != 0)) {
        hash += hashAux;   
        if (hash > table->size)
            hash -= table->size;
    }
    if (table->values[hash] == NULL)
       puts("Valor não encontrado");
    else 
       display(table->values[hash]);
}

void initHashTable(TableHash *table) {
    table->values = (List **) calloc(TABLE_SIZE, sizeof(List *));
    table->occupation = 0;
    table->occupation_tax = 0.0;
    table->size = TABLE_SIZE;
}