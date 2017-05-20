//
//  BST.cpp
//  ComputationalGeometryFinal
//
//  Created by Shikhar  on 19/04/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include "BST.hpp"
int max(int a,int b){
    return a<b?a:b;
}

double AVLtree::getPriority(const Edge & e)
{
    Vertex start=*(e.p_start);
    Vertex end=*(e.p_twin->p_start);
    if(end.coord.y==start.coord.y)
        return start.coord.x;
    double r=(end.coord.y-start.coord.y);
    //cout<<e.myaddr<<"PRiority---> "<<r<<endl;
    
    return (((compareAt-start.coord.y)*(end.coord.x-start.coord.x))/r)+start.coord.x;
    
}

int AVLtree::height(node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
node* AVLtree::newNode(Edge ei)
{
    node* n = (node*)malloc(sizeof(node));
    n->e   = ei;
    n->left   = NULL;
    n->right  = NULL;
    n->height = 1;  // new node is initially added at leaf
    return(n);
}
node* AVLtree::rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    // Return new root
    return x;
}
node* AVLtree::leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    // Return new root
    return y;
}
int AVLtree::getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
node* AVLtree::insert(node* n, Edge ei)
{
    /* 1.  Perform the normal BST insertion */
    if (n == NULL)
        return(newNode(ei));
    
    if (getPriority(ei) < getPriority(n->e))
        n->left  = insert(n->left, ei);
    else if (getPriority(ei) > getPriority(n->e))
        n->right = insert(n->right, ei);
    else // Equal keys are not allowed in BST
        return n;
    
    /* 2. Update height of this ancestor n */
    n->height = 1 + max(height(n->left),
                        height(n->right));
    
    /* 3. Get the balance factor of this ancestor
     n to check whether this n became
     unbalanced */
    int balance = getBalance(n);
    
    // If this n becomes unbalanced, then
    // there are 4 cases
    
    // Left Left Case
    if (balance > 1 && getPriority(ei) < getPriority(n->left->e))
        return rightRotate(n);
    
    // Right Right Case
    if (balance < -1 && getPriority(ei) > getPriority(n->right->e))
        return leftRotate(n);
    
    // Left Right Case
    if (balance > 1 && getPriority(ei) > getPriority(n->left->e))
    {
        n->left =  leftRotate(n->left);
        return rightRotate(n);
    }
    
    // Right Left Case
    if (balance < -1 && getPriority(ei) < getPriority(n->right->e))
    {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
    
    /* return the (unchanged) n pointer */
    return n;
}
node* AVLtree::minValueNode(node* n)
{
    node* current = n;
    
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

node* AVLtree::deleteNode(node* roo, Edge ei)
{
    // STEP 1: PERFORM STANDARD BST DELETE
    
    if (roo == NULL)
        return roo;
    
    // If the key to be deleted is smaller than the
    // roo's key, then it lies in left subtree
    if ( getPriority(ei) < getPriority(roo->e) )
        roo->left = deleteNode(roo->left, ei);
    
    // If the key to be deleted is greater than the
    // roo's key, then it lies in right subtree
    else if( getPriority(ei) > getPriority(roo->e) )
        roo->right = deleteNode(roo->right, ei);
    
    // if key is same as roo's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (roo->left == NULL) || (roo->right == NULL) )
        {
            node *temp = roo->left ? roo->left :
            roo->right;
            
            // No child case
            if (temp == NULL)
            {
                temp = roo;
                roo = NULL;
            }
            else // One child case
                *roo = *temp; // Copy the contents of
            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            node* temp = minValueNode(roo->right);
            
            // Copy the inorder successor's data to this node
            roo->e = temp->e;
            
            // Delete the inorder successor
            roo->right = deleteNode(roo->right, temp->e);
        }
    }
    
    // If the tree had only one node then return
    if (roo == NULL)
        return roo;
    
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    roo->height = 1 + max(height(roo->left),
                          height(roo->right));
    
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(roo);
    
    // If this node becomes unbalanced, then there are 4 cases
    
    // Left Left Case
    if (balance > 1 && getBalance(roo->left) >= 0)
        return rightRotate(roo);
    
    // Left Right Case
    if (balance > 1 && getBalance(roo->left) < 0)
    {
        roo->left =  leftRotate(roo->left);
        return rightRotate(roo);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(roo->right) <= 0)
        return leftRotate(roo);
    
    // Right Left Case
    if (balance < -1 && getBalance(roo->right) > 0)
    {
        roo->right = rightRotate(roo->right);
        return leftRotate(roo);
    }
    
    return roo;
}



node* AVLtree::pred(Edge e)
{
    node *r=root;
    node *g=NULL;
    std::cout<<getPriority(r->e)<<std::endl;
    std::cout<<getPriority(e)<<std::endl;
    while(r!=NULL)
    {
        if(getPriority(e)>getPriority(r->e))
        {
            g=r;
            r=r->right;
        }
        else if(getPriority(e)<getPriority(r->e))
        {
            r=r->left;
        }
        else
        {
            std::cout<<"exceptional case\n";
            break;
        }
    }
    if(g!=NULL)
        return g;
    std::cout<<"Min value function called\n";
    return minValueNode(root);
}





/*
 int main()
 {
 int ch,y=0;
 RBtree obj;
 do
 {
 cout<<"\n\t RED BLACK TREE " ;
 cout<<"\n 1. Insert in the tree ";
 cout<<"\n 2. Delete a node from the tree";
 cout<<"\n 3. Search for an element in the tree";
 cout<<"\n 4. Display the tree ";
 cout<<"\n 5. Exit " ;
 cout<<"\nEnter Your Choice: ";
 cin>>ch;
 switch(ch)
 {
 case 1 : obj.insert();
 cout<<"\nNode Inserted.\n";
 break;
 case 2 : obj.del();
 break;
 case 3 : obj.search();
 break;
 case 4 : obj.disp();
 break;
 case 5 : y=1;
 break;
 default : cout<<"\nEnter a Valid Choice.";
 }
 cout<<endl;
 
 }while(y!=1);
 return 1;
 }
 */








void BST::insert(Edge e,Vertex v)
{
    S.compareAt=v.coord.y; //use this
    //S.push_back(e);
    S.root=S.insert(S.root,e);
}
void BST::setHelper(Edge e,Vertex v)
{
    helper[e.myaddr]=v;
}
void BST::remove(Edge e)
{
    S.compareAt=e.p_twin->p_start->coord.y;
    //for(vector<Edge>::iterator it=S.begin();it!=S.end();it++)
    //  if(*it==e)
    //{
    //  S.erase(it);
    //break;
    
    //}
    S.root=S.deleteNode(S.root,e);
}
Edge BST::find(Vertex v)
{
    //cout<<"Reached hurray\n"<<endl;
    S.compareAt=v.coord.y;
    Edge e;
    Edge etwin;
    etwin.p_start=&v;
    e.p_twin=&etwin;
    e.p_start=&v;
    //set<Edge,edge_compare>::iterator it=S.lower_bound(e);
    std::cout<<"Called\n";
    node *predes=S.pred(e);
    std::cout<<predes->e.myaddr<<std::endl;
    return predes->e;
    //comp.getPriority(e);
    //cout<<"HELPER RETURNED FOR "<<v.myaddr<<"is-->";
    //cout<<it->myaddr<<endl;
    
}
