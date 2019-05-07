#include <sys/stat.h>
#include "node_iterator.h"
#include "find_link_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
void FindLinkVisitor::visitFile(File * file){

}
void FindLinkVisitor::visitLink(Link * link){
    ans.push_back(link);
}
void FindLinkVisitor::visitFolder(Folder * folder){
    NodeIterator * it = folder->createIterator();
    for(it->first();!it->isDone();it->next()){
        struct stat st;
        if(lstat( it->currentItem()->path().c_str() , &st)==0 && S_ISLNK(st.st_mode))
            ans.push_back(it->currentItem());
        if(lstat( it->currentItem()->path().c_str() , &st)==0 && S_ISDIR(st.st_mode))
            it->currentItem()->acceptJump(this);        
    }
}
void FindLinkVisitor::clear(){
    ans.clear();
}
vector<Node*> FindLinkVisitor::getLinks(){
    return ans;
}