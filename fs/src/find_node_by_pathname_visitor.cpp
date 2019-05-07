#include <sys/stat.h>
#include "node.h"
#include "node_iterator.h"
#include "folder.h"
#include "link.h"
#include "file.h"
#include "find_node_by_pathname_visitor.h"

void FindNodeByPathnameVisitor::visitFolder(Folder * folder){
    if(_pathnames->empty())return;
    if(folder->name()==_pathnames->at(index) &&_pathnames->at(index)==_pathnames->back())
        ans=folder;
    if(folder->name()==_pathnames->at(index)){
        if(_pathnames->at(index)!=_pathnames->back())index++;
        NodeIterator * it = folder->createIterator();
        for(it->first();!it->isDone();it->next()){
            if(it->currentItem()->name()==_pathnames->at(index)){
                it->currentItem()->acceptJump(this);
            }
        }
    }
}
void FindNodeByPathnameVisitor::visitFile(File * file){
    if((*_pathnames).empty())return;
    if(file->name() == _pathnames->at(index))ans=file;
}

void FindNodeByPathnameVisitor::visitLink(Link * link){
    if((*_pathnames).empty())return;
    if(link->name() == _pathnames->at(index))ans=link;
}

void FindNodeByPathnameVisitor::clear(){
    ans=nullptr;
}

Node * FindNodeByPathnameVisitor::getNode()const{
    return ans;
}