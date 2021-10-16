#include "hash/hash.h"
#include "list/lista.h"

int main(void) {
    TableHash tableH;
    initHashTable(&tableH);
    List *joao = initList();
    add(joao, "pedro");
    add(joao, "maria");
    add(joao, "alice");
    add(joao, "marcos");

    List *maria = initList();
    add(maria, "jorgina");
    add(maria, "maria");
    add(maria, "alice");
    add(maria, "marcos");

    Insert("joao", joao, &tableH);
    Insert("maria", maria, &tableH);
    /*for (int i = 0; i < tableH.size; i++) {
        display(tableH.values[i]);
    }*/
    get("joao", &tableH);

   

    
}