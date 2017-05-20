//
//  DCEL.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef DCEL_hpp
#define DCEL_hpp

#include "Face.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

#include "Data.hpp"
#include <unordered_map>
class DCEL
{
public:
    unordered_map<int,Vertex> VertexRecord;
    unordered_map<int,Edge> EdgeRecord;
    unordered_map<int,Face> FaceRecord;
    int nF;
    int nE;
    int nV;
public:
    DCEL(Data ob);
    void addEdge(Vertex start,Vertex end);
    void splitEdge(Edge &e_l,Point p); ///implemented test this
    vector<Edge> walkAround(Face f);
    vector<Face> incidentFaces(Vertex v);
    vector<Vertex> generateFaceVertices(Face f);
    void flipEdge(Edge &e);
    void display();
    void output();
    void splitFace(Face &f,Point p);
   // void mergeDCEL(DCEL *X);
};
#endif /* DCEL_hpp */
