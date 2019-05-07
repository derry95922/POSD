#ifndef folder_h
#define folder_h
#include <sys/stat.h>
#include <map>
#include "node.h"
#include "node_iterator.h"
#include "node_visitor.h"
#include "vector"
#include "info_content_visitor.h"
#include "find_visitor.h"
// using namespace std;
class Folder:public Node{
public:
    friend class InfoContentVisitor;
    friend class FindVisitor;

    class FolderIterator:public NodeIterator{
    public:
        FolderIterator(Folder * f):_folder(f){ }
        
        void first(){
            _it = _folder->_children.begin();
        }
        Node* currentItem(){
            if(isDone())throw string("no current item");
            return _it->second;
        }
        void next(){
            if(isDone())throw string("moving past the end");
            _it++;
        }
        bool isDone(){
            return _it == _folder->_children.end();
        }
    private:
        Folder * _folder;
        map<string, Node*>::iterator _it;
    };

    Folder(const char * path):Node(path){
        struct stat st;
        if (lstat(path,&st) == 0 && !S_ISDIR(st.st_mode))throw string ("Do not indicate the folder path.");
    }

    void add(Node * node){
        // _children.push_back(node);
        _children.insert(pair<string,Node*>(node->name(),node));
        node->setParent(this);
    }

    int numberOfChildren(){
        return _children.size();
    }

    int infoContent(){
        int sum = 0;
        NodeIterator * it = createIterator();    
        for(it->first();!it->isDone();it->next()){
            sum += it->currentItem()->infoContent();
        }
        return sum;
    }

    void accept(NodeVisitor * nv){
        nv->clear();
        nv->now_path(Node::path());
        nv->visitFolder(this);
    }

    void acceptJump(NodeVisitor * nv){
        nv->visitFolder(this);
    }

    bool isdir(){
        return true;
    }

    NodeIterator * createIterator(){
        return new FolderIterator(this);
    }
    
private:
    // vector<Node*>_children;
    map<string,Node*>_children;
};
#endif