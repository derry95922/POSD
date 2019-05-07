#ifndef find_visitor_h
#define find_visitor_h
#include <string>
#include <vector>
#include<iostream>
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
 
    string findResult(){
        string now = _now_path;
        for(int i=0;i<ans.size();i++){
            _result += "." + ans[i].substr(now.size(),ans[i].size());
            if(i!=(ans.size()-1))_result += "\n";
        }
        return _result;
    }

    void now_path(string path){
        if(_now_path=="")_now_path = path;
    }

    void clear(){
        ans.clear();
        _result = "";
    }
   
private:
    string _result,_target,_now_path;
    vector<string>ans;
};
#endif