#ifndef FIND_NODE_BY_PATHNAME_VISITOR_H
#define FIND_NODE_BY_PATHNAME_VISITOR_H

#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include"node.h"
#include"node_visitor.h"
using namespace std;

class File;
class Folder;
class Link;

class FindNodeByPathnameVisitor:public NodeVisitor{
public:
    FindNodeByPathnameVisitor(vector<string>* pathnames):_pathnames(pathnames){
        index = 0;
    }
    void visitFolder(Folder * folder);
    void visitFile(File * file);
    void visitLink(Link * link);
    void clear();
    Node * getNode() const; //return the Node object if the path indicate the node in the file system, and if not, return nullptr.
private:
    vector<string>* _pathnames;
    Node * ans = nullptr;
    int index;
};

#endif