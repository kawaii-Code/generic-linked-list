#include <stdio.h>

typedef const char* string;
#define LINKED_LIST_TYPE string
#include "../linked_list.h"

void print_node(struct LINKED_LIST_NODE *node) {
    printf("(%p, %s) -> ", node, node->data);
}

void print_linked_list(struct LINKED_LIST_NODE *head) {
    printf("[");
    linked_list_foreach_nodes(head, &print_node);
    printf("X ]\n");
}

int main() {
    struct LINKED_LIST_NODE *first = linked_list_node_new("Hello, ", NULL);
    struct LINKED_LIST_NODE *second = linked_list_insert_after(first, "generics in C!");

    print_linked_list(first);
}
