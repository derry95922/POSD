#ifndef NODE_H
#define NODE_H

#include <sys/stat.h>
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include <cstddef>
#include"node_iterator.h"
#include"null_iterator.h"
using namespace std;
class NodeVisitor;
class FindVisitor;

class Node{
public:
  Node(char * path): _path(path){
    lstat(_path, &_st);
  }

  int size() const{
    return _st.st_size;
  }

  virtual void add(Node *node){
    throw std::string("unable to add");
  }

  virtual int numberOfChildren() const{
    throw std::string("number of children: not applicable");
  }

  string name(){
    string str = _path;
    size_t found = str.find_last_of("/\\");
    // cout << " path: " << str.substr(0,found) << '\n';
    // cout << " file: " << str.substr(found+1) << '\n';
    return str.substr(found+1);
  }

  string path(){
    return _path;
  }
  
  virtual void accept(NodeVisitor * nv) {}

  virtual void acceptJump(NodeVisitor * nv){}

  virtual NodeIterator * createIterator(){  //factory method
    return new NullIterator();
  }

  Node * getParent() const{
    return _node;
  }
  
  void setParent (Node * p){
    _node = p;
  }

  void setPath(char * new_path){
    _path = new_path;
  }
  
private:
  char * _path;
  struct stat _st;
  Node * _node=nullptr;
};

#endif