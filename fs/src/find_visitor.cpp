#include <sys/stat.h>
#include <string>
#include "node_iterator.h"
#include "file.h"
#include "folder.h"
#include "find_visitor.h"

void FindVisitor::visitFile(File * file){
    if(file->name() == _target) _result = _target;
    else _result = "";
}

void FindVisitor::visitFolder(Folder * folder){
    NodeIterator * it = folder->createIterator();
    for(it->first();!it->isDone();it->next()){
        struct stat st;
        if(it->currentItem()->name()==_target)
            ans.push_back(it->currentItem()->path());
        if(lstat( it->currentItem()->path().c_str() ,&st) == 0 && S_ISDIR(st.st_mode))
            it->currentItem()->acceptJump(this);
    }
}

void FindVisitor::clear(){
    ans.clear();
    _result = "";
}

void FindVisitor::now_path(string path){
    _now_path = path;
}

string FindVisitor::findResult(){
    string now = _now_path;
    for(int i=0;i<ans.size();i++){
        _result += "." + ans[i].substr(now.size(), ans[i].size());
        if(i!=(ans.size()-1))_result += "\n"; 
    }
    return _result;
}