#ifndef FOLDER_H
#define FOLDER_H

#include <sys/stat.h>
#include <iostream>
#include <map>
#include "node.h"
#include "node_iterator.h"
#include "info_content_visitor.h"
#include "find_visitor.h"
class Folder:public Node{
public:

  class FolderIterator : public NodeIterator
  {
  public:
    FolderIterator(Folder * f): _folder(f){   }
    void first(){
      _it = _folder->_children.begin();
    }

    Node* currentItem(){
      if (isDone()){
        throw std::string("no current item");
      }
      return _it->second;//2
    }
    void next(){
      if (isDone()){
        throw std::string("moving past the end");
      }
      _it++;
    }
    bool isDone(){
      return _it == _folder->_children.end();
    }
  private:
    Folder * _folder;
    map<string,Node *>::iterator _it;
  };

  
  Folder(char* path):Node(path){
    struct stat st;
    if (lstat(path,&st) == 0 && !S_ISDIR(st.st_mode))throw string ("Do not indicate the folder path.");
  }

  void add(Node * node){
    _children.insert(pair<string , Node *>(node->name(),node));
    node->setParent(this);
  }

  int numberOfChildren() const{
    return _children.size();
  }

  void accept(NodeVisitor * nv)
  {
    nv->clear();
    nv->now_path(Node::path());
    nv->visitFolder(this);
  }

  void acceptJump(NodeVisitor * nv){
    nv->visitFolder(this);
  }

  NodeIterator * createIterator(){
    return new FolderIterator(this);
  }

private:
  map<string,Node *>_children;
};

#endif