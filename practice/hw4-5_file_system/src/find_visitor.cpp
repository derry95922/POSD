#include "node_iterator.h"
#include "find_visitor.h"
#include "file.h"
#include "folder.h"
#include <string>
#include <sys/stat.h>
void FindVisitor::visitFile(File * file){
    if(file->name()==_target)_result = _target;//路徑
    else _result = "";
}

void FindVisitor::visitFolder(Folder * folder){
    NodeIterator * it = folder->createIterator();
    for(it->first();!it->isDone();it->next()){
        struct stat st;
        if(it->currentItem()->name()==_target)
            ans.push_back(it->currentItem()->path());
        if(lstat( it->currentItem()->path().c_str() ,&st) == 0 && S_ISDIR(st.st_mode))//他的小孩
            it->currentItem()->acceptJump(this);
    }
}