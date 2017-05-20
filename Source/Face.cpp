//
//  Face.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "Face.hpp"


Face::Face(int x)
{
    myaddr=x;
    p_incident=NULL;
}
bool Face::operator==(const Face &other)
{
    return (*(p_incident)==*(other.p_incident));
}
