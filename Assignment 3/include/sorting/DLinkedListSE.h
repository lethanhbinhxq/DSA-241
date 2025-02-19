/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        //TODO: implement this function
        //     - You should implement the merge sort algorithm
        if (this->empty()) {
            return;
        }
        typename DLinkedList<T>::Node* sortHead = this->head->next;
        
        sortHead->prev = nullptr;
        this->tail->prev->next = nullptr;

        mergeSort(sortHead, comparator);

        typename DLinkedList<T>::Node* currentTail = sortHead;
        while (currentTail->next) {
            currentTail = currentTail->next;
        }

        this->head->next = sortHead;
        sortHead->prev = this->head;

        this->tail->prev = currentTail;
        currentTail->next = this->tail;
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }

    void mergeSort(typename DLinkedList<T>::Node*& firstHead, int (*comparator)(T&,T&)=nullptr) {
        if (firstHead && firstHead->next) {
            typename DLinkedList<T>::Node* secondHead;
            divide(firstHead, secondHead);
            mergeSort(firstHead, comparator);
            mergeSort(secondHead, comparator);
            merge(firstHead, secondHead, comparator);
        }
    }

    void divide(typename DLinkedList<T>::Node* &firstHead, typename DLinkedList<T>::Node* &secondHead) {
        if (!firstHead || !firstHead->next) {
            secondHead = nullptr;
            return;
        }

        typename DLinkedList<T>::Node* slow = firstHead;
        typename DLinkedList<T>::Node* fast = firstHead->next;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        secondHead = slow->next;
        if (secondHead) {
            secondHead->prev = nullptr;
        }
        slow->next = nullptr;
    }

    void merge(typename DLinkedList<T>::Node*& firstHead, typename DLinkedList<T>::Node*& secondHead, int (*comparator)(T&,T&) = nullptr) {
        typename DLinkedList<T>::Node mergeList;
        typename DLinkedList<T>::Node* mergePtr = &mergeList;

        while (firstHead && secondHead) {
            if (compare(firstHead->data, secondHead->data, comparator) <= 0) {
                mergePtr->next = firstHead;
                firstHead->prev = mergePtr;
                mergePtr = firstHead;
                firstHead = firstHead->next;
            }
            else {
                mergePtr->next = secondHead;
                secondHead->prev = mergePtr;
                mergePtr = secondHead;
                secondHead = secondHead->next;
            }
        }

        if (!firstHead) {
            mergePtr->next = secondHead;
            if (secondHead) {
                secondHead->prev = mergePtr;
            }
            secondHead = nullptr;
        }
        else {
            mergePtr->next = firstHead;
            if (firstHead) {
                firstHead->prev = mergePtr;
            }
        }
        firstHead = mergeList.next;
    }
};

#endif /* DLINKEDLISTSE_H */

