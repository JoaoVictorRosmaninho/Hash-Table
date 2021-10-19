#include "hash/hash.h"
#include "list/lista.h"

int main(void) {
    TableHash tableH;
    initHashTable(&tableH);
    List *ny = initList();
    add(ny, "Denver");
    add(ny, "Torontto");
    add(ny, "Chicago");

    List *chicago = initList();
    add(chicago, "Denver");

    List *Denver = initList();
    add(Denver, "Los Angeles");
    add(Denver, "Houston");
    add(Denver, "Urbana");

    List *Houston = initList();
    add(Houston, "Los Angeles");

    List *Toronto = initList();
    add(Toronto, "Los Angeles");
    add(Toronto, "Chicago");
    add(Toronto, "Calgary");




    Insert("New York", ny, &tableH);
    Insert("Denver", Denver, &tableH);
    Insert("Chicago", chicago, &tableH);
   
    Insert("Houston", Houston, &tableH);
    Insert("Toronto", Toronto, &tableH);
    /*for (int i = 0; i < tableH.size; i++) {
        display(tableH.values[i]);
    }*/
    get("Houston", &tableH);

   

    
}