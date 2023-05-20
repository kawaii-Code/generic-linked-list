// Copyright 2023 kawaii-Code.
// Subject to the MIT License.

#ifdef LINKED_LIST_TYPE

#define LINKED_LIST_CALL(macro, args) macro(args)
#define LINKED_LIST_CONCAT(arg1, arg2) arg1 ## arg2

#ifndef LINKED_LIST_CUSTOM_MEMORY_MANAGEMENT
#include <stdlib.h>
#define LINKED_LIST_MALLOC malloc
#define LINKED_LIST_FREE free
#endif // LINKED_LIST_CUSTOM_MEMORY_MANAGEMENT
 
#define LINKED_LIST_STRUCT_NAME(type) LinkedListNode_ ## type
#define LINKED_LIST_NODE LINKED_LIST_CALL(LINKED_LIST_STRUCT_NAME, LINKED_LIST_TYPE)
struct LINKED_LIST_NODE {
    LINKED_LIST_TYPE data;
    struct LINKED_LIST_NODE *next;
}; 

// The generics work by using a
// macro that concatenates 'LinkedListNode_' 
// and a given type name.
// It's as simple as that.

typedef int (*LinkedListElementEqualityCompare)(LINKED_LIST_TYPE, LINKED_LIST_TYPE);
typedef void (*LinkedListAction)(LINKED_LIST_TYPE);
typedef void (*LinkedListNodeAction)(struct LINKED_LIST_NODE*);

struct LINKED_LIST_NODE *linked_list_node_new(LINKED_LIST_TYPE data, struct LINKED_LIST_NODE *next) {
    struct LINKED_LIST_NODE *node = LINKED_LIST_MALLOC(sizeof *node);
    node->data = data;
    node->next = next;
    return node;
}

struct LINKED_LIST_NODE *linked_list_insert_before(struct LINKED_LIST_NODE **head, struct LINKED_LIST_NODE *node, LINKED_LIST_TYPE data) {
    struct LINKED_LIST_NODE **indirect = head;

    while (*indirect != node) {
        indirect = &(*indirect)->next;
    }

    return (*indirect = linked_list_node_new(data, node));
}

struct LINKED_LIST_NODE *linked_list_insert_after(struct LINKED_LIST_NODE *node, LINKED_LIST_TYPE data) {
    return (node->next = linked_list_node_new(data, node->next));
}

struct LINKED_LIST_NODE *linked_list_find(struct LINKED_LIST_NODE *head, LINKED_LIST_TYPE value, LinkedListElementEqualityCompare compare) {
    struct LINKED_LIST_NODE *walk = head;

    while (walk != NULL) {
        if (compare(walk->data, value)) {
            return walk;
        }
        walk = walk->next;
    }

    return NULL;
}

void linked_list_remove(struct LINKED_LIST_NODE **head, struct LINKED_LIST_NODE *node) {
    struct LINKED_LIST_NODE **indirect = head;

    while (*indirect != node) {
        indirect = &(*indirect)->next;
    }

    *indirect = node->next;
    LINKED_LIST_FREE(node);
}

void linked_list_foreach(struct LINKED_LIST_NODE *head, LinkedListAction action) {
    while (head != NULL) {
        action(head->data);
        head = head->next;
    }
}

void linked_list_foreach_nodes(struct LINKED_LIST_NODE *head, LinkedListNodeAction action) {
    while (head != NULL) {
        action(head);
        head = head->next;
    }
}

#endif // LINKED_LIST_TYPE
