/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        //TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
        if (mode == DFS) {
            return dfsSort(sorted);
        }
        return bfsSort(sorted);
    }
    DLinkedList<T> bfsSort(bool sorted=true){ 
        //TODO
        DLinkedList<T> bfsSortedList;
        xMap<T, int> inDegreeMap = vertex2inDegree(this->hash_code);
        DLinkedListSE<T> zeroIndegreeList = listOfZeroInDegrees();
        Queue<T> zeroIndegreeQueue;

        if (sorted) {
            zeroIndegreeList.sort();
        }

        while (!zeroIndegreeList.empty()) {
            zeroIndegreeQueue.push(zeroIndegreeList.removeAt(0));
        }

        while (!zeroIndegreeQueue.empty()) {
            T curVertex = zeroIndegreeQueue.pop();
            bfsSortedList.add(curVertex);
            DLinkedListSE<T> neighborList = this->graph->getOutwardEdges(curVertex);
            if (sorted) neighborList.sort();
            for (auto neighbor : neighborList) {
                if (bfsSortedList.contains(neighbor) || zeroIndegreeQueue.contains(neighbor)) {
                    continue;
                }
                int inDegree = inDegreeMap.get(neighbor);
                inDegreeMap.put(neighbor, inDegree - 1);
                if (inDegree - 1 == 0) {
                    zeroIndegreeQueue.push(neighbor);
                }
            }
        }
        return bfsSortedList;
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
        DLinkedList<T> dfsSortedList;
        xMap<T, int> outDegreeMap = vertex2outDegree(this->hash_code);
        DLinkedListSE<T> zeroIndegreeList = listOfZeroInDegrees();
        Stack<T> processingStack;

        if (sorted) {
            zeroIndegreeList.sort();
        }

        while (!zeroIndegreeList.empty()) {
            processingStack.push(zeroIndegreeList.removeAt(0));   
        }

        while (!processingStack.empty()) {
            T curVertex = processingStack.peek();
            int outDegree = outDegreeMap.get(curVertex);
            if (outDegree) {
                DLinkedListSE<T> neighborList = this->graph->getOutwardEdges(curVertex);
                if (sorted) neighborList.sort();
                for (auto neighbor : neighborList) {
                    if (processingStack.contains(neighbor)) {
                        processingStack.remove(neighbor);
                        processingStack.push(neighbor);
                    }
                    if (!processingStack.contains(neighbor) && !dfsSortedList.contains(neighbor)) {
                        processingStack.push(neighbor);
                    }
                    outDegreeMap.put(curVertex, outDegree - 1);
                }
            }
            else {
                processingStack.pop();
                dfsSortedList.add(0, curVertex);
            }
        }
        return dfsSortedList;
    }

protected:

    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int)) {
        xMap<T, int> inDegreeMap(hash);
        for (auto vertex : *(this->graph)) {
            int inDegree = this->graph->inDegree(vertex);
            inDegreeMap.put(vertex, inDegree);
        }
        return inDegreeMap;
    }
    xMap<T, int> vertex2outDegree(int (*hash)(T&, int)) {
        xMap<T, int> outDegreeMap(hash);
        for (auto vertex : *(this->graph)) {
            int outDegree = this->graph->outDegree(vertex);
            outDegreeMap.put(vertex, outDegree);
        }
        return outDegreeMap;
    }
    DLinkedList<T> listOfZeroInDegrees() {
        DLinkedList<T> zeroIndegreeList;
        for (auto vertex : *(this->graph)) {
            if (this->graph->inDegree(vertex) == 0) {
                zeroIndegreeList.add(vertex);
            }
        }
        return zeroIndegreeList;
    }

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

