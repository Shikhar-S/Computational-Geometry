//
//  Vertex.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "Vertex.hpp"
Vertex::Vertex(int x)
{
    myaddr=x;
    p_incident=NULL;
}
bool Vertex::operator==(const Vertex &other)
{
    return (coord.equals(other.coord));
}
bool Vertex::operator<(const Vertex &other)const
{
    return (coord.y<other.coord.y || (coord.y==other.coord.y && coord.x<other.coord.x));
}
bool Vertex::operator!=(const Vertex &other)
{
    return !(coord.equals(other.coord));
}
