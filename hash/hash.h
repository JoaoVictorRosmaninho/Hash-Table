#ifndef HASH_H
# define HASH_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../list/lista.h"


# define TABLE_SIZE 3
# define LOAD_FACTOR 0.6
# define GROWTH_FACTOR 1.5

  typedef struct tableHash {
      List **values;
      unsigned int occupation;
      unsigned int size;
      float occupation_tax;
    } TableHash;

  unsigned int hashC(char *key, unsigned int tableSize);

  static inline unsigned int hashD(char *key, unsigned int tableSize);

  void resize(TableHash *table);

  void Insert(char *key, List *value, TableHash *table);

  void get(char *key, TableHash *table);
 
  void initHashTable(TableHash *table);

#endif