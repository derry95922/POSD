#include "node.h"
#include "node_iterator.h"
#include "find_node_by_pathname_visitor.h"
#include "folder.h"
#include "file.h"
#include "link.h"

void FindNodeByPathnameVisitor::visitFile(File * file){
    if((*_pathnames).empty())return;
    if(file->name()==_pathnames->at(index))ans=file;
}
void FindNodeByPathnameVisitor::visitFolder(Folder * folder){
    if((*_pathnames).empty())return;
    if(folder->name()==(*_pathnames)[index]&&(*_pathnames)[index]==(*_pathnames).back())ans=folder;
    if(folder->name()==(*_pathnames)[index]){
        if((*_pathnames)[index]!=(*_pathnames).back())index++;
        NodeIterator * it = folder->createIterator();
        for(it->first();!it->isDone();it->next()){
            if(it->currentItem()->name()==(*_pathnames)[index])
                it->currentItem()->acceptJump(this);
        }
    }
}
void FindNodeByPathnameVisitor::visitLink(Link * link){
    if((*_pathnames).empty())return;
    if(link->name()==(*_pathnames)[index])ans=link;
}
void FindNodeByPathnameVisitor::clear(){
    ans=nullptr;
}
Node * FindNodeByPathnameVisitor::getNode()const{
    return ans;
}