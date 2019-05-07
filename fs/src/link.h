#ifndef LINK_H
#define LINK_H
//proxy
#include <sys/stat.h>
#include "node.h"
#include "node_visitor.h"
class Link : public Node{ 
public:
  Link(char * path, Node * node = nullptr) : Node(path){
    struct stat st;
    if(lstat(path,&st) == 0 && !S_ISLNK(st.st_mode))throw string ("Do not indicate the link path.");
    this->addLink(node);
  }

  void accept(NodeVisitor * nv){
    nv->clear();
    nv->visitLink(this);
  }

  void acceptJump(NodeVisitor * nv){
    nv->visitLink(this);
  }

  void addLink(Node * node){
    _source = node;
  }

  Node * getSource(){
    return _source;
  }

private:
  Node * _source;
};

#endif
