#ifndef node_visitor_h
#define node_visitor_h
#include <iostream>
#include <string>

using namespace std;
class Folder;
class File;
class Link;
class NodeVisitor{
public:
    virtual void visitFolder(Folder * folder) = 0;
    virtual void visitFile(File * file) = 0;
    virtual void visitLink(Link * link) = 0;
    virtual void clear(){}

    virtual int getContentSize() {throw string("ur welcome");}//infoContentVisitor
    
    virtual void now_path(string path){ }
    virtual string findResult() {throw string("ur welcome");}
};

#endif