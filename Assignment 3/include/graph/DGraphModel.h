/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"
#include "stacknqueue/PriorityQueue.h"
#include "sorting/DLinkedListSE.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //TODO
        VertexNode* fromNode = getVertexNode(from);
        VertexNode* toNode = getVertexNode(to);
        if (fromNode && toNode) {
            fromNode->connect(toNode, weight);
        }
        else {
            VertexNode missingNode;
            if (!fromNode) missingNode = *fromNode;
            else missingNode = *toNode;
            throw VertexNotFoundException(vertex2Str(missingNode));
        }
    }
    void disconnect(T from, T to){
        //TODO
        VertexNode* fromNode = getVertexNode(from);
        VertexNode* toNode = getVertexNode(to);
        if (fromNode && toNode) {
            Edge* edge = fromNode->getEdge(toNode);
            if (edge) {
                fromNode->removeTo(toNode);
            }
            else {
                throw EdgeNotFoundException(edge2Str(*edge));
            }
        }
        else {
            VertexNode missingNode;
            if (!fromNode) missingNode = *fromNode;
            else missingNode = *toNode;
            throw VertexNotFoundException(vertex2Str(missingNode));
        }
    }
    void remove(T vertex){
        //TODO
        VertexNode* node = getVertexNode(vertex);
        if (node) {
            for (auto vertex : this->nodeList) {
                Edge* edge1 = vertex->getEdge(node);
                Edge* edge2 = node->getEdge(vertex);
                if (edge1) vertex->removeTo(node);
                if (edge2) node->removeFrom(vertex);
            }
            this->nodeList.removeItem(node);
        }
        else {
            throw VertexNotFoundException(vertex2Str(*node));
        }
    }
    
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)){
        //TODO
        DGraphModel<T>* graph = new DGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; i++) {
            graph->add(vertices[i]);
        }
        for (int i = 0; i < nedges; i++) {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

