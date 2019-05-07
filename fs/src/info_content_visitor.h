#ifndef INFO_CONTENTVISITOR
#define INFO_CONTENTVISITOR
#include "node_visitor.h"
class File;
class Folder;
class Link;

class InfoContentVisitor:public NodeVisitor{
public:
  InfoContentVisitor();

  void visitFile(File * file);
  void visitFolder(Folder * folder);
  void visitLink(Link * link);

  int getContentSize();
  
private:
  int _size;
};

#endif