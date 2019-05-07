#ifndef FILE_H
#define FILE_H

#include <sys/stat.h>
#include "node.h"
#include "node_visitor.h"
#include "info_content_visitor.h"
#include "find_visitor.h"
#include "null_iterator.h"

class File: public Node{
public:
  File(char * path): Node(path){
    struct stat st;
    if (lstat(path, &st) == 0 && !S_ISREG(st.st_mode))throw string ("Do not indicate the file path.");
  }

  void accept(NodeVisitor * nv)
  {
    nv->visitFile(this);
  }

  void acceptJump(NodeVisitor * nv){
    nv->visitFile(this);
  }

  NodeIterator * createIterator(){
    return new NullIterator();
  }

};

#endif
