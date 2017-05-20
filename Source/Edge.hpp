//
//  Edge.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
class Vertex;
#include "Vertex.hpp"
class Face;
#include "Face.hpp"
class Edge{
public:
    Vertex *p_start;
    Edge *p_next;
    Edge *p_prev;
    Edge *p_twin;
    Face *p_incident;
    int myaddr;
public:
    Edge(int x=-1);
    bool operator==(const Edge &other);
    bool operator!=(const Edge &other);
    
};
#endif /* Edge_hpp */
