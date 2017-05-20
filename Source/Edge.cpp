//
//  Edge.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "Edge.hpp"
Edge::Edge(int x)
{
    myaddr=x;
    p_start=NULL;
    
    p_next=NULL;
    p_prev=NULL;
    p_incident=NULL;
}
bool Edge::operator==(const Edge &other)
{
    return (*(other.p_start)==*(p_start) && *(p_twin->p_start)==*(other.p_twin->p_start));
}
bool Edge::operator!=(const Edge &other)
{
    return !(*(other.p_start)==*(p_start) && *(p_twin->p_start)==*(other.p_twin->p_start));
}
