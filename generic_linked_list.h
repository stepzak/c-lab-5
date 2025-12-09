//
// Created by zakatinstepan on 09.12.2025.
//

#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H
#define DEFINE_LINKED_LIST(PREFIX, T) \
    typedef struct PREFIX##_Node PREFIX##_Node; \
    struct PREFIX##_Node { \
        T value; \
        PREFIX##_Node *next;\
    }; \
    typedef struct { \
        PREFIX##_Node *first; \
        PREFIX##_Node *last; \
        int size; \
    } PREFIX##_LinkedList; \
    typedef struct { \
        PREFIX##_Node *prev; \
        PREFIX##_LinkedList *list; \
    } PREFIX##_Iterator; \
    static inline PREFIX##_LinkedList* create_##PREFIX##_LinkedList() { \
        PREFIX##_LinkedList* linkedList = malloc(sizeof(PREFIX##_LinkedList)); \
        linkedList -> size = 0; \
        linkedList -> first = nullptr; \
        linkedList -> last = nullptr; \
        return linkedList; \
    } \
\
    static inline PREFIX##_Iterator* create_##PREFIX##_Iterator(PREFIX##_LinkedList* linkedList) { \
        PREFIX##_Iterator* iterator = malloc(sizeof(PREFIX##_Iterator)); \
        iterator->list = linkedList; \
        iterator->prev = nullptr; \
        return iterator; \
    } \
    \
    static inline void destroy_##PREFIX##_LinkedListIterator(PREFIX##_Iterator* iterator) { \
        free(iterator); \
    } \
    \
    static inline bool is_##PREFIX##_End(PREFIX##_Iterator* iterator) { \
        if (iterator->prev == nullptr) { \
            return false; \
        } \
        return iterator->prev->next == nullptr; \
    } \
    \
    static inline void inc_##PREFIX##_Iterator(PREFIX##_Iterator* iterator) {\
\
        if (iterator->prev == nullptr) { \
            iterator -> prev = iterator -> list -> first;\
            return;\
        }\
        iterator->prev = iterator->prev->next;\
    }\
\
    static inline T get_##PREFIX##_NodeValue(PREFIX##_Node* node) { \
        return node -> value;\
    }\
\
    static inline void set_##PREFIX##_NodeValue(PREFIX##_Node* node, T value) {\
        node -> value = value;\
    }\
    \
    static inline PREFIX##_Node* get_##PREFIX##_Iterator(PREFIX##_Iterator* iterator) { \
        return iterator -> prev; \
    }\
\
    static inline PREFIX##_Node* get_##PREFIX##_IteratorNext(PREFIX##_Iterator* iterator) { \
        PREFIX##_Node* prev = iterator->prev;\
        if (prev == nullptr) {\
            return iterator -> list -> first;\
        }\
        return prev->next;\
    }\
\
    static inline int insert_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, int index, T value) {\
        if (index >= linkedList -> size + 1 || index < 0) {\
            return -1;\
        }\
        PREFIX##_Node* newNode = malloc(sizeof(PREFIX##_Node));\
        newNode -> value = value;\
        PREFIX##_Iterator* iterator = create_##PREFIX##_Iterator(linkedList);\
        if (index == linkedList -> size) {\
            newNode -> next = nullptr;\
            if (linkedList -> last !=nullptr) {\
                linkedList -> last -> next = newNode;\
            }\
            linkedList -> last = newNode;\
            if (index == 0) {\
                linkedList -> first = newNode;\
            }\
        }\
        else {\
            int currIndex = 0;\
            while (currIndex < index)  {\
                inc_##PREFIX##_Iterator(iterator);\
                currIndex++;\
            }\
            if (iterator->prev == nullptr) {\
                newNode -> next = linkedList -> first;\
                linkedList -> first = newNode;\
            }\
            else {\
                newNode -> next = iterator->prev -> next;\
                iterator->prev -> next = newNode;\
            }\
        }\
        linkedList -> size++;\
        destroy_##PREFIX##_LinkedListIterator(iterator);\
        return 0;\
    }\
\
    static inline void append_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, T value) {\
        insert_##PREFIX##_LinkedList(linkedList, linkedList->size, value);\
    }\
\
    static inline void prepend_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, T value) {\
        insert_##PREFIX##_LinkedList(linkedList, 0, value);\
    }\
\
    static inline PREFIX##_Node* get_##PREFIX##_LinkedListByIndex(PREFIX##_LinkedList* linkedList, int index) {\
        if (index == linkedList -> size - 1) {\
            return linkedList -> last;\
        }\
        PREFIX##_Iterator* iterator = create_##PREFIX##_Iterator(linkedList);\
        int currIndex = 0;\
        while (currIndex < index) {\
            inc_##PREFIX##_Iterator(iterator);\
            currIndex++;\
        }\
\
        return get_##PREFIX##_IteratorNext(iterator);\
    }\
\
    static inline void set_##PREFIX##_LinkedListValue(PREFIX##_LinkedList* linkedList, int index, T value) {\
        PREFIX##_Iterator* iterator = create_##PREFIX##_Iterator(linkedList);\
        int currIndex = 0;\
        while (currIndex < index) {\
            inc_##PREFIX##_Iterator(iterator);\
            currIndex++;\
        }\
        get_##PREFIX##_IteratorNext(iterator) -> value = value;\
    }\
\
    static inline void set_##PREFIX##_LinkedListNextValue(PREFIX##_LinkedList* linkedList, int index, T value) {\
        PREFIX##_Iterator* iterator = create_##PREFIX##_Iterator(linkedList);\
        int currIndex = 0;\
        do  {\
            inc_##PREFIX##_Iterator(iterator);\
            currIndex++;\
        } while (currIndex < index);\
        get_##PREFIX##_IteratorNext(iterator) -> value = value;\
    }\
    \
    static inline int get_##PREFIX##_Size(PREFIX##_LinkedList* linkedList) {\
    return linkedList -> size;\
    }\
    static inline void delete_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList, int index) {\
        if (index == 0) {\
            linkedList -> first = linkedList -> first -> next;\
        }\
        else {\
    \
            PREFIX##_Iterator* iterator = create_##PREFIX##_Iterator(linkedList);\
            int currIndex = 0;\
            while (currIndex < index) {\
                inc_##PREFIX##_Iterator(iterator);\
                currIndex++;\
            }\
            iterator->prev->next = iterator->prev -> next -> next;\
            if (iterator -> prev -> next == nullptr) {\
                iterator->list -> last = iterator->prev -> next;\
            }\
            if (index == get_##PREFIX##_Size(linkedList)-1) {\
                linkedList -> last = iterator->prev;\
            }\
            destroy_##PREFIX##_LinkedListIterator(iterator);\
    \
        }\
        linkedList -> size--;\
    \
    }\
    \
        static inline bool is_##PREFIX##_Empty(PREFIX##_LinkedList* linkedList) {\
            return linkedList -> size == 0;\
        }\
        \
        static inline PREFIX##_LinkedList* copy_##PREFIX##_LinkedList(PREFIX##_LinkedList* linkedList) {\
            PREFIX##_LinkedList* copy = create_##PREFIX##_LinkedList();\
            PREFIX##_Iterator* iterator = create_##PREFIX##_Iterator(linkedList);\
            while(!is_##PREFIX##_End(iterator)){\
                inc_##PREFIX##_Iterator(iterator);\
                PREFIX##_Node* node = get_##PREFIX##_Iterator(iterator);\
                T val = get_##PREFIX##_NodeValue(node);\
                append_##PREFIX##_LinkedList(copy, val);\
                }\
            return copy;\
        }\



#endif //GENERIC_LIST_H