#include "lista.h"

void *makenode(uint16_t size) {
    void *temp;
    if ((temp = calloc(1, size)) == 0) /* NULL */
        return 0;
    return temp;
}

List *initList(void) { 
    return (List *) makenode(sizeof(List)); 
}

void insert(List *list, uint16_t pos, char *value) {
    Node *temp = (Node *) makenode(sizeof(Node));
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = strdup(value);
   // if (pos > list->size)

    if (pos == 1) { //inicio 
        if (list->node_ini == NULL) {
            list->node_ini = list->node_end = temp;
        } else {
            temp->next = list->node_ini;
            list->node_ini->prev = temp;
            list->node_ini = temp;
        }
    } else if (pos == 0) { //final
        temp->prev = list->node_end;
        list->node_end->next = temp;
        list->node_end = temp;
        
    } else if (pos > (list->size / 2)) {
            Node *tmp = list->node_end;
            uint16_t aux_pos = list->size -  pos;
            while (aux_pos--) tmp = tmp->prev;
            tmp->prev->next = temp; // last point to new
            temp->next = tmp; // new point to old pos
            temp->prev = tmp->prev; // new prev points to tmp prev
            tmp->prev = temp; // old prev points to new prev
    } else {
            Node *tmp = list->node_ini;
            while (--pos) tmp = tmp->next;
            tmp->prev->next = temp;
            temp->next = tmp;
            temp->prev = tmp->prev;
            tmp->prev = temp;
    }
    list->size++;
}

void add(List *list, char *data) {
    if (list->node_ini == 0)
        insert(list, 1, data);
    else 
        insert(list, 0, data);
}

void display(List * list) {
    if (list == NULL) {
        puts("[]");
        return;
    }
    Node *temp = list->node_ini;
    putchar('[');
    char *delimiter = ", ";
    while (temp) {
        if (temp->next == NULL)
            delimiter = "";
        printf("%s%s", temp->data, delimiter);
        temp = temp->next;
    }
    putchar(']');
    putchar('\n');
}

void save(List *list) {
    Node *node = list->node_ini;
    FILE *fp;
    if ((fp = fopen("list.dat", "wb")) == NULL) return;
    while(node) {
        fwrite(node, sizeof(Node), 1, fp);
        node = node->next;
    }
    fclose(fp);
}

List *load(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) return 0;
    List *new_list = initList();
    Node *node = makenode(sizeof(Node));
    while (fread(node, sizeof(Node), 1, fp) == 1) 
        add(new_list, node->data);
    free(node);
    return new_list;
}




