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
#include "stacknqueue/PriorityQueue.h"

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
        VertexNode* fromNode = getVertexNode(from);
        VertexNode* toNode = getVertexNode(to);
        if (fromNode && toNode) {
            fromNode->connect(toNode, weight);
            toNode->connect(fromNode, weight);
        }
        else {
            VertexNode missingNode;
            if (!fromNode) missingNode = *fromNode;
            else missingNode = *toNode;
            throw VertexNotFoundException(vertex2Str(missingNode));
        }
    }
    void disconnect(T from, T to)
    {
        // TODO
        VertexNode* fromNode = getVertexNode(from);
        VertexNode* toNode = getVertexNode(to);
        if (fromNode && toNode) {
            Edge* edge = fromNode->getEdge(toNode);
            if (edge) {
                fromNode->removeTo(toNode);
                toNode->removeTo(fromNode);
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
    void remove(T vertex)
    {
        // TODO
        VertexNode* node = getVertexNode(vertex);
        if (node) {
            for (auto vertex : this->nodeList) {
                Edge edge = vertex->getEdge(node);
                if (edge) {
                    node->removeTo(vertex);
                    vertex->removeTo(node);
                }
            }
            this->nodeList.removeItem(node);
        }
        else {
            throw VertexNotFoundException(vertex2Str(*node));
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
