#ifndef LINK_H
#define LINK_H
#include <sys/stat.h>
#include "node.h"
#include "node_visitor.h"
class Link: public Node{
public:
    Link(const char * path,Node * node = nullptr):Node(path){
        struct stat st;
    if (lstat(path,&st) == 0 && !S_ISLNK(st.st_mode))throw string ("Do not indicate the link path.");
        this->addLink(node);
    }

    void addLink(Node * node){
        _source = node;
    }

    void accept(NodeVisitor * nv){
        nv->visitLink(this);
    }

    void acceptJump(NodeVisitor * nv){
        nv->visitLink(this);
    }

    Node * getSource(){
        return _source;
    }
private:
    Node * _source;
};

#endif