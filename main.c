#include <stdio.h>
//#include "linked_list.h"
#define min(a,b) (((a) < (b)) ? (a) : (b))
#include <stdlib.h>

#include "generic_linked_list.h"

DEFINE_LINKED_LIST(double);

double_LinkedList* insertionSort_double_LinkedList(double_LinkedList* list) {
    double_LinkedList* sortedList = copy_double_LinkedList(list);
    double_Iterator* iterator = create_double_Iterator(sortedList);
    inc_double_Iterator(iterator);
    int i = 0;
    int size = get_double_Size(sortedList);
    while (!is_double_End(iterator)) {
        double_Node* curNode = get_double_Iterator(iterator);
        double curValue = get_double_NodeValue(curNode);
        int indToSearch = min(i+1, size);
        double_Node* node = get_double_IteratorNext(iterator);
        double value = get_double_NodeValue(node);
        i++;
        if (value < curValue) {
            double_Iterator* newIterator = create_double_Iterator(sortedList);
            int j = 0;
            while (!is_double_End(newIterator)) {
                double_Node* nextNode = get_double_IteratorNext(newIterator);
                double nextValue = get_double_NodeValue(nextNode);
                if (nextValue>value) {
                    delete_double_LinkedList(sortedList, indToSearch);
                    insert_double_LinkedList(sortedList, j, value);
                    destroy_double_LinkedListIterator(newIterator);
                    break;
                }
                j++;
                inc_double_Iterator(newIterator);
            }
        }
        else {
            inc_double_Iterator(iterator);
        }
    }
    destroy_double_LinkedListIterator(iterator);
    return sortedList;
}

void insertIntoSorted(double_LinkedList* list, double value) {
    double_Iterator* iterator = create_double_Iterator(list);
    inc_double_Iterator(iterator);
    int i = 0;
    while (!is_double_End(iterator)) {
        double_Node* curNode = get_double_Iterator(iterator);
        if (get_double_NodeValue(curNode)>value) {
            insert_double_LinkedList(list, i, value);
            return;
        }
        i++;
        inc_double_Iterator(iterator);
    }
    insert_double_LinkedList(list, get_double_Size(list), value);
}

int main(void) {
    double_LinkedList *list = create_double_LinkedList();
    append_double_LinkedList(list, 10);
    append_double_LinkedList(list, 20);
    append_double_LinkedList(list, 15);
    append_double_LinkedList(list, 30);
    append_double_LinkedList(list, 9);
    append_double_LinkedList(list, 8);
    append_double_LinkedList(list, 60);
    prepend_double_LinkedList(list, 100);

    double_Iterator* iterator = create_double_Iterator(list);
    while (!is_double_End(iterator)) {
        inc_double_Iterator(iterator);
        double val = get_double_NodeValue(get_double_Iterator(iterator));
        printf("%lf\n", val);
    }
    printf("----------------------\n");
    double_LinkedList* sorted = insertionSort_double_LinkedList(list);
    insertIntoSorted(sorted, 200);
    insertIntoSorted(sorted, 32.1);
    insertIntoSorted(sorted, 7);
    double_Iterator* iterator2 = create_double_Iterator(sorted);
    while (!is_double_End(iterator2)) {
        inc_double_Iterator(iterator2);
        double val = get_double_NodeValue(get_double_Iterator(iterator2));
        printf("%lf\n", val);
    }
    return 0;
}