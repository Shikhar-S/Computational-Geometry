//
//  Face.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef Face_hpp
#define Face_hpp

class Edge;
#include "Edge.hpp"

class Face{
public:
    int myaddr;
    Edge *p_incident;
public:
    Face(int x=-1);
    
    bool operator==(const Face &other);
    
};

#endif /* Face_hpp */
