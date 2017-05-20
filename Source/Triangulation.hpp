//
//  Triangulation.hpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#ifndef Triangulation_hpp
#define Triangulation_hpp

#include "DCEL.hpp"
#include "primitives.hpp"
#include <algorithm>
#include <vector>
#include "Data.hpp"
#include "BST.hpp"
#define mergeVertex 1
#define splitVertex 2
#define startVertex 3
#define endVertex 4
#define regularVertex 5
#include <queue>
#include <stack>
class Triangulation
{
private:
    BST Tau;
private:
    int typeOfVertex(Vertex v,DCEL &X);
    
    void HandleStartVertex(Vertex v,DCEL &X);
    
    void HandleEndVertex(Vertex v,DCEL &X);
    
    void HandleSplitVertex(Vertex v,DCEL &X);
    
    void HandleMergeVertex(Vertex v,DCEL &X);
    
    bool check_polyIsToRight(Vertex v,Face f,DCEL &X);
    
    void HandleRegularVertex(Vertex v,DCEL &X);
    
    void makeMonotone(DCEL &X);
    
    bool leftChain(Vertex v,unordered_map<int,string> &chain); //CHANGE WHEREVER CALLED!!!!!!!!!!!!!!!!
    
    bool rightChain(Vertex v,unordered_map<int,string> &chain);   //CHANGE WHEREVER CALLED!!!!!!!!!!!!!!!!
    
    bool inside(Vertex a,Vertex b,Vertex c,unordered_map<int, string> &chain);
    
    bool diffchains(Vertex a,Vertex b,unordered_map<int,string> &chain);
    
    void triangulate(DCEL &X,Face &f);
    
public:
    void performTriangulation(DCEL &X);
    
};
#endif /* Triangulation_hpp */
