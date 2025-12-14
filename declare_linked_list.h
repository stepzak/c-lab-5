//
// Created by zakatinstepan on 09.12.2025.
//

#ifndef DECLARE_LINKED_LIST_H
#define DECLARE_LINKED_LIST_H
#define DECLARE_LINKED_LIST(PREFIX, T) \
typedef struct PREFIX##_Node PREFIX##_Node; \
struct PREFIX##_Node { \
    T value; \
    PREFIX##_Node* next; \
}; \
typedef struct { \
    PREFIX##_Node* first; \
    PREFIX##_Node* last; \
    int size; \
} PREFIX##_LinkedList; \
typedef struct { \
    PREFIX##_Node* prev; \
    PREFIX##_LinkedList* list; \
} PREFIX##_Iterator; \
\
PREFIX##_LinkedList* create_##PREFIX##_LinkedList(void); \
PREFIX##_Iterator* create_##PREFIX##_Iterator(PREFIX##_LinkedList* linkedList); \
void destroy_##PREFIX##_LinkedListIterator(PREFIX##_Iterator* iterator); \
bool is_##PREFIX##_End(PREFIX##_Iterator* iterator); \
void inc_##PREFIX##_Iterator(PREFIX##_Iterator* iterator); \
T get_##PREFIX##_NodeValue(PREFIX##_Node* node); \
void set_##PREFIX##_NodeValue(PREFIX##_Node* node, T value); \
PREFIX##_Node* get_##PREFIX##_Iterator(PREFIX##_Iterator* iterator); \
PREFIX##_Node* get_##PREFIX##_IteratorNext(PREFIX##_Iterator* iterator); \
int insert_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, int index, T value); \
void append_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, T value); \
void prepend_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, T value); \
PREFIX##_Node* get_##PREFIX##_LinkedListByIndex(PREFIX##_LinkedList* linkedList, int index); \
void set_##PREFIX##_LinkedListValue(PREFIX##_LinkedList* linkedList, int index, T value); \
void set_##PREFIX##_LinkedListNextValue(PREFIX##_LinkedList* linkedList, int index, T value); \
int get_##PREFIX##_Size(PREFIX##_LinkedList* linkedList); \
void delete_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, int index); \
bool is_##PREFIX##_Empty(PREFIX##_LinkedList* linkedList); \
PREFIX##_LinkedList* copy_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList);

#endif  //DECLARE_LINKED_LIST_H