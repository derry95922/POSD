#ifndef FIND_VISITOR
#define FIND_VISITOR

#include <string>
#include <vector>
#include "node.h"
#include "node_visitor.h"
using namespace std;
class File;
class Folder;
class Link;

class FindVisitor:public NodeVisitor{
public:
    FindVisitor(string target):_target(target){}

    void visitFile(File * file);
    void visitFolder(Folder * folder);
    void visitLink(Link * link){}

    void clear();
    string findResult();
    void now_path(string path);

private:
    string _target,_result,_now_path;
    vector<string>ans;
};

#endif