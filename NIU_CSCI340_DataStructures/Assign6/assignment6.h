#ifndef ASSIGNMENT6
#define ASSIGNMENT6
#include "assign5.h"

class BST : public binTree {
    public:
        BST() : binTree() {}
        void insert( int );
        bool search( int );
       bool remove( int );
       bool removeNode(Node*& ptr);
       void GetPredecessor(Node * ptr, int &data);
       int sumLeftLeaves();
    private:
        void insert( Node*&, int );
        bool search( Node*&, int );
        bool remove( Node*&, int );
        int sumLeftLeaves(Node*&);
};

#endif
