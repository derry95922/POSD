#ifndef FIND_NODE_BY_PATHNAME_VISITOR_H
#define FIND_NODE_BY_PATHNAME_VISITOR_H

#include <vector>
#include <string>
#include "node.h"
#include "node_visitor.h"
// #include 
class Folder;
class File;
class Link;
class FindNodeByPathnameVisitor:public NodeVisitor{
public:
    FindNodeByPathnameVisitor(vector<string>*pathnames):_pathnames(pathnames){
        index=0;
    }
    void visitFolder(Folder * folder);
    void visitFile(File * file);
    void visitLink(Link * link);
    void clear();
    Node * getNode() const;
private:
    vector<string>*_pathnames;
    Node * ans = nullptr;
    int index;
};

#endif