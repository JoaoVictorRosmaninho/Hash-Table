#include "hash/hash.h"
#include "list/lista.h"

int main(void) {
    TableHash tableH;
    initHashTable(&tableH);
    Insert("Testname", "Testname", &tableH);
    Insert("Testname", "Testname2", &tableH);
    Insert("Testname", "Testname3", &tableH);
    Insert("Testname", "Testname4", &tableH);

    Insert("TestNameB", "TestNameB", &tableH);
    Insert("TestNameC", "TestNameC", &tableH);

    Insert("Testname", "Testname5", &tableH);
   for (int i = 0; i < tableH.size; i++) 
        display(tableH.table[i]);
   

    
}