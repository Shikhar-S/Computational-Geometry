//
//  Vertex.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include "primitives.hpp"
class Edge;
#include "Edge.hpp"

class Vertex
{
public:
    int myaddr;
    Point coord;
    Edge *p_incident;
public:
    Vertex(int x=-1);
    bool operator==(const Vertex &other);
    
    bool operator<(const Vertex &other)const;
    
    bool operator!=(const Vertex &other);
    
};
#endif /* Vertex_hpp */
