#include <sys/stat.h>
#include "node.h"
#include "node_iterator.h"
#include "folder.h"
#include "link.h"
#include "file.h"
#include "find_link_visitor.h"

void FindLinkVisitor::visitFile(File * file){

}

void FindLinkVisitor::visitFolder(Folder * folder){
    NodeIterator * it = folder->createIterator();
    for(it->first();!it->isDone();it->next()){
        struct stat st;
        if(lstat( it->currentItem()->path().c_str() ,&st) == 0 && S_ISLNK(st.st_mode))  //
            ans.push_back(it->currentItem()); //S_IFLNK?
        if(lstat( it->currentItem()->path().c_str() ,&st) == 0 && S_ISDIR(st.st_mode))
            it->currentItem()->acceptJump(this);
    }
}

void FindLinkVisitor::visitLink(Link * link){
    ans.push_back(link);
}

vector<Node*> FindLinkVisitor::getLinks(){
    return ans;
}

void FindLinkVisitor::clear(){
    ans.clear();
}