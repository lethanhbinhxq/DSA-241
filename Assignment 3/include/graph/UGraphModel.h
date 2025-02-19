/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (fromNode && toNode) {
            if (fromNode->equals(toNode)) {
                fromNode->connect(toNode, weight);
            }
            else {
                fromNode->connect(toNode, weight);
                toNode->connect(fromNode, weight);
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
    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (fromNode && toNode) {
            typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
            if (edge) {
                if (fromNode->equals(toNode)) {
                    fromNode->removeTo(toNode);
                }
                else {
                    fromNode->removeTo(toNode);
                    toNode->removeTo(fromNode);
                }
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
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* node = this->getVertexNode(vertex);
        if (node) {
            for (auto vertex : this->nodeList) {
                typename AbstractGraph<T>::Edge* edge = vertex->getEdge(node);
                if (edge) {
                    if (node->equals(vertex)) {
                        node->removeTo(vertex);
                    }
                    else {
                        node->removeTo(vertex);
                        vertex->removeTo(node);
                    }
                }
            }
            this->nodeList.removeItem(node);
            delete node;
        }
        else {
            typename AbstractGraph<T>::VertexNode missingNode(vertex, this->vertexEQ, this->vertex2str);
            throw VertexNotFoundException(this->vertex2Str(missingNode));
        }
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T>* graph = new UGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; i++) {
            graph->add(vertices[i]);
        }
        for (int i = 0; i < nedges; i++) {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
