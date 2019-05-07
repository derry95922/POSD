#ifndef info_content_visitor_h
#define info_content_visitor_h
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

    int getContentSize(){
        return _size;
    }

private:
    int _size;
};
#endif