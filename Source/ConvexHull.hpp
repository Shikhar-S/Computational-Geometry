//
//  ConvexHull.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef ConvexHull_hpp
#define ConvexHull_hpp

#include "primitives.hpp"
#include "Data.hpp"
class ConvexHull{
    /**
     *To provide algorithms for Generating Convex Hull
     */
private:
    Data inp; ///< input for generating Hull
public:
    ConvexHull(Data obj);
    Data getInput();
    Data grahamScan();
    /**
     *Performs Graham Scan on the given input data object
     */
    Data jarvisMarch();
    /**
     *Computes Convex Hull via Jarvis March algorithm Complexity: O(NH)
     *where H := number of points on Hull.
     */
    Data andrewAlgorithm();
    /**
     *Computes Convex Hull via Andrew algorithm Complexity: O(Nlog N)
     */
    void display();
    /**
     *displays input and output list of points
     */
};

#endif /* ConvexHull_hpp */
