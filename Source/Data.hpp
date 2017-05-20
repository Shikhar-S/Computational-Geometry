//
//  Data.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 18/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef Data_hpp
#define Data_hpp
#include "primitives.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Data{
    /*
     * To represent a list of Points and provide functions for sorting the list.
     */
private:
    vector<Point> points; ///< list of points encapsulated in Data object
    int N; ///< Number of points in list
    Point origin;
public:
    Data();
    /**
     *Constructor to generate Data object from given array of points
     */
    Data(vector<Point> p);
    Data(Point arg_points[],int sz);
    void getInput();
    /**
     *To get input from user.
     */
    void add(Point x);
    /**
     *inserts Point into Data
     *Complexity: O(1)
     */

    bool remove(Point x);
    /**
     *removes Point from Data object
     *returns true on success
     *Complexity: O(N)
     */

    static bool comp_andrew(const Point &a,const Point &b)
    /**
     *To order points by increasing value of x coordiantes
     *and then y coordiante.
     *
     */
    {
        if(a.x<b.x) // if a.x<b.x
            return true;
        else if(a.x==b.x) //if a.x==b.x
        {
            return a.y<b.y; //order by y coordinate
        }
        else
            return false;
    }
    bool comp_graham(const Point &a,const Point &b);
    static bool comp_ysweep(const Point &a,const Point &b)
    {
        if(a.y>b.y) // if a.x<b.x
            return true;
        else if(a.y==b.y) //if a.x==b.x
        {
            return a.x<b.x; //order by y coordinate
        }
        else
            return false;
    }
    void orderSweep();
    void orderLexicographically();
    /**
     *sorts list Lexicographically
     */
    
    void orderRadially();
    /**
     *sorts list radially assuming first element as anchor
     */

    
    Point getPoint(int idx);
    /**accessor method for list
     */

    void setPoint(int idx,Point value);
    /**mutator method for list
     */

    int getSize();
    /**
     *accessor method for size of list
     */

    void setSize(int x);
    /**mutator method for size of list
     */

    void setOrigin(Point x);
    void display();
    /**displays list of points*/
    void swap(int a,int b);
    /** swap element at index a and b*/
    bool exists(Point p);
    
};
#endif /* Data_hpp */
