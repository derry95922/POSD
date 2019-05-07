#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "node_iterator.h"
class NullIterator:public NodeIterator{
public:
    NullIterator(){}
    void first(){
      //definition by yourself
    }
    Node* currentItem(){
        return nullptr;
    }
    void next() {
      //definition by yourself  
    }
    bool isDone(){
        return true;
    }
};

#endif