#include <stdio.h>
#include <stdlib.h>

#define LINKED_LIST_TYPE int
#include "../linked_list.h"

void print_int(int value) {
    printf("%d ", value);
}

void print_node(struct LinkedListNode_int *node) {
    printf("(%p, %d) -> ", node, node->data);
}

int int_equal(int a, int b) {
    return a == b;
}

void print_linked_list(struct LinkedListNode_int *head) {
    printf("[ ");
    linked_list_foreach_nodes(head, &print_node);
    printf("X ]");
    printf("\n");
}

int main() {
    struct LinkedListNode_int *head = linked_list_node_new(1, NULL);
    print_linked_list(head);
    
    struct LinkedListNode_int *second = linked_list_insert_after(head, 2);
    print_linked_list(head);

    head = linked_list_insert_before(&head, head, 0);
    print_linked_list(head);

    struct LinkedListNode_int *oneandhalf = linked_list_insert_before(&head, second, 15);
    print_linked_list(head);

    linked_list_remove(&head, second);
    print_linked_list(head);

    linked_list_remove(&head, linked_list_find(head, 1, int_equal));
    print_linked_list(head);

    linked_list_foreach(head, &print_int);
}
