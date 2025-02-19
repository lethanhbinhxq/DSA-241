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
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (fromNode && toNode) {
            fromNode->connect(toNode, weight);
        }
        else {
            if (!fromNode) {
                typename AbstractGraph<T>::VertexNode missingNode(from, this->vertexEQ, this->vertex2str);
                throw VertexNotFoundException(this->vertex2Str(missingNode));
            }
            if (!toNode) {
                typename AbstractGraph<T>::VertexNode missingNode(to, this->vertexEQ, this->vertex2str);
                throw VertexNotFoundException(this->vertex2Str(missingNode));
            }
        }
    }
    void disconnect(T from, T to){
        //TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (fromNode && toNode) {
            typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
            if (edge) {
                fromNode->removeTo(toNode);
            }
            else {
                typename AbstractGraph<T>::Edge missingEdge(fromNode, toNode);
                throw EdgeNotFoundException(this->edge2Str(missingEdge));
            }
        }
        else {
            if (!fromNode) {
                typename AbstractGraph<T>::VertexNode missingNode(from, this->vertexEQ, this->vertex2str);
                throw VertexNotFoundException(this->vertex2Str(missingNode));
            }
            if (!toNode) {
                typename AbstractGraph<T>::VertexNode missingNode(to, this->vertexEQ, this->vertex2str);
                throw VertexNotFoundException(this->vertex2Str(missingNode));
            }
        }
    }
    void remove(T vertex){
        //TODO
        typename AbstractGraph<T>::VertexNode* node = this->getVertexNode(vertex);
        if (node) {
            for (auto vertex : this->nodeList) {
                typename AbstractGraph<T>::Edge* edge1 = vertex->getEdge(node);
                typename AbstractGraph<T>::Edge* edge2 = node->getEdge(vertex);
                if (edge1) vertex->removeTo(node);
                if (edge2) node->removeTo(vertex);
            }
            this->nodeList.removeItem(node);
            delete node;
        }
        else {
            typename AbstractGraph<T>::VertexNode missingNode(vertex, this->vertexEQ, this->vertex2str);
            throw VertexNotFoundException(this->vertex2Str(missingNode));
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

