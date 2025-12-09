//
// Created by zakatinstepan on 09.12.2025.
//

#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H
#define DEFINE_LINKED_LIST(T) \
    typedef struct T##_Node T##_Node; \
    struct T##_Node { \
        T value; \
        T##_Node *next;\
    }; \
    typedef struct { \
        T##_Node *first; \
        T##_Node *last; \
        int size; \
    } T##_LinkedList; \
    typedef struct { \
        T##_Node *prev; \
        T##_LinkedList *list; \
    } T##_Iterator; \
    static inline T##_LinkedList* create_##T##_LinkedList() { \
        T##_LinkedList* linkedList = malloc(sizeof(T##_LinkedList)); \
        linkedList -> size = 0; \
        linkedList -> first = nullptr; \
        linkedList -> last = nullptr; \
        return linkedList; \
    } \
\
    static inline T##_Iterator* create_##T##_Iterator(T##_LinkedList* linkedList) { \
        T##_Iterator* iterator = malloc(sizeof(T##_Iterator)); \
        iterator->list = linkedList; \
        iterator->prev = nullptr; \
        return iterator; \
    } \
    \
    static inline void destroy_##T##_LinkedListIterator(T##_Iterator* iterator) { \
        free(iterator); \
    } \
    \
    static inline bool is_##T##_End(T##_Iterator* iterator) { \
        if (iterator->prev == nullptr) { \
            return false; \
        } \
        return iterator->prev->next == nullptr; \
    } \
    \
    static inline void inc_##T##_Iterator(T##_Iterator* iterator) {\
\
        if (iterator->prev == nullptr) { \
            iterator -> prev = iterator -> list -> first;\
            return;\
        }\
        iterator->prev = iterator->prev->next;\
    }\
\
    static inline T get_##T##_NodeValue(T##_Node* node) { \
        return node -> value;\
    }\
\
    static inline void set_##T##_NodeValue(T##_Node* node, T value) {\
        node -> value = value;\
    }\
    \
    static inline T##_Node* get_##T##_Iterator(T##_Iterator* iterator) { \
        return iterator -> prev; \
    }\
\
    static inline T##_Node* get_##T##_IteratorNext(T##_Iterator* iterator) { \
        T##_Node* prev = iterator->prev;\
        if (prev == nullptr) {\
            return iterator -> list -> first;\
        }\
        return prev->next;\
    }\
\
    static inline int insert_##T##_LinkedList(T##_LinkedList* linkedList, int index, T value) {\
        if (index >= linkedList -> size + 1 || index < 0) {\
            return -1;\
        }\
        T##_Node* newNode = malloc(sizeof(T##_Node));\
        newNode -> value = value;\
        T##_Iterator* iterator = create_##T##_Iterator(linkedList);\
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
                inc_##T##_Iterator(iterator);\
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
        destroy_##T##_LinkedListIterator(iterator);\
        return 0;\
    }\
\
    static inline void append_##T##_LinkedList(T##_LinkedList* linkedList, T value) {\
        insert_##T##_LinkedList(linkedList, linkedList->size, value);\
    }\
\
    static inline void prepend_##T##_LinkedList(T##_LinkedList* linkedList, T value) {\
        insert_##T##_LinkedList(linkedList, 0, value);\
    }\
\
    static inline T##_Node* get_##T##_LinkedListByIndex(T##_LinkedList* linkedList, int index) {\
        if (index == linkedList -> size - 1) {\
            return linkedList -> last;\
        }\
        T##_Iterator* iterator = create_##T##_Iterator(linkedList);\
        int currIndex = 0;\
        while (currIndex < index) {\
            inc_##T##_Iterator(iterator);\
            currIndex++;\
        }\
\
        return get_##T##_IteratorNext(iterator);\
    }\
\
    static inline void set_##T##_LinkedListValue(T##_LinkedList* linkedList, int index, T value) {\
        T##_Iterator* iterator = create_##T##_Iterator(linkedList);\
        int currIndex = 0;\
        while (currIndex < index) {\
            inc_##T##_Iterator(iterator);\
            currIndex++;\
        }\
        get_##T##_IteratorNext(iterator) -> value = value;\
    }\
\
    static inline void set_##T##_LinkedListNextValue(T##_LinkedList* linkedList, int index, T value) {\
        T##_Iterator* iterator = create_##T##_Iterator(linkedList);\
        int currIndex = 0;\
        do  {\
            inc_##T##_Iterator(iterator);\
            currIndex++;\
        } while (currIndex < index);\
        get_##T##_IteratorNext(iterator) -> value = value;\
    }\
    \
    static inline int get_##T##_Size(T##_LinkedList* linkedList) {\
    return linkedList -> size;\
    }\
    static inline void delete_##T##_LinkedList(T##_LinkedList* linkedList, int index) {\
        if (index == 0) {\
            linkedList -> first = linkedList -> first -> next;\
        }\
        else {\
    \
            T##_Iterator* iterator = create_##T##_Iterator(linkedList);\
            int currIndex = 0;\
            while (currIndex < index) {\
                inc_##T##_Iterator(iterator);\
                currIndex++;\
            }\
            iterator->prev->next = iterator->prev -> next -> next;\
            if (iterator -> prev -> next == nullptr) {\
                iterator->list -> last = iterator->prev -> next;\
            }\
            if (index == get_##T##_Size(linkedList)-1) {\
                linkedList -> last = iterator->prev;\
            }\
            destroy_##T##_LinkedListIterator(iterator);\
    \
        }\
        linkedList -> size--;\
    \
    }\
    \
        static inline bool is_##T##_Empty(T##_LinkedList* linkedList) {\
            return linkedList -> size == 0;\
        }\
        \
        static inline T##_LinkedList* copy_##T##_LinkedList(T##_LinkedList* linkedList) {\
            T##_LinkedList* copy = create_##T##_LinkedList();\
            T##_Iterator* iterator = create_##T##_Iterator(linkedList);\
            while(!is_##T##_End(iterator)){\
                inc_##T##_Iterator(iterator);\
                T##_Node* node = get_##T##_Iterator(iterator);\
                T val = get_##T##_NodeValue(node);\
                append_##T##_LinkedList(copy, val);\
                }\
            return copy;\
        }\



#endif //GENERIC_LIST_H