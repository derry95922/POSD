#ifndef FIND_LINK_VISITOR_H
#define FIND_LINK_VISITOR_H

#include <vector>
#include "node.h"
#include "node_visitor.h"
class Folder;
class File;
class Link;

class FindLinkVisitor:public NodeVisitor{
public:
    FindLinkVisitor(){}

    void visitFolder(Folder * folder);
    void visitFile(File * file);
    void visitLink(Link * link);
    void clear();
    vector<Node*>  getLinks();//return the Link objects.

private:
    vector<Node*>ans;
};

#endif