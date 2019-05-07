#ifndef node_h
#define node_h
#include <sys/stat.h>
#include <string>
#include <vector>
#include <cstddef> 
#include <string.h>
#include"node_iterator.h"
#include"null_iterator.h"
using namespace std; 
class InfoContentVisitor;
class FindVisitor;
class NodeVisitor;
class Node{
public:
    Node(const char * path):_path(path){
        lstat(_path,&_st);
    }

    int size() const{
        return _st.st_size;     //stat 表示大小
    }

    virtual void add(Node * node){
        throw string("Unable to add!");
    }
    
    virtual int numberOfChildren(){
        throw string("number of children: not applicable");
    }

    virtual int infoContent(){
        return size();
    }

    string name(){
        // string s = _path;
        // vector<string>content;
        // const char * del = "/";
        // char * s_t = new char [s.size()+1];
        // strcpy(s_t,s.c_str());
        // char * p = strtok(s_t,del);
        // while(p){
        //     content.push_back(p);
        //     p = strtok(NULL,del);
        // }
        // return content.back();
        string str = _path;
        size_t found = str.find_last_of("/\\");
        // cout << " path: " << str.substr(0,found) << '\n';
        // cout << " file: " << str.substr(found+1) << '\n';
        return str.substr(found+1);
    }

    // virtual string find(string target){
    //     if(name()==target)return target;
    //     else return "";
    // }

    string path(){
        return _path;
    }

    virtual void visit(string target,vector<string>&ans){ }

    virtual void accept(NodeVisitor * nv){ }

    virtual void acceptJump(NodeVisitor * nv){ }

    virtual bool isdir(){
        return false;
    }

    virtual NodeIterator * createIterator(){
        return nullptr;
    }

    Node * getParent()const{
        return _node;
    }
    
    void setParent(Node * p){
        _node = p;
    }

private:
    const char * _path;
    struct stat _st;
    Node * _node;
};
#endif