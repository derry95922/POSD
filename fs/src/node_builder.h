#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H

#include <sys/stat.h>
#include <string>
#include <dirent.h>
#include <string.h>
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
using namespace std;
class NodeBuilder {
public:
    NodeBuilder() {}

    void build(char * path) {
        struct stat st;
        if (lstat(path, &st) == 0) {
            if (S_ISREG(st.st_mode))
                _root = new File(path);
            else if (S_ISLNK(st.st_mode))
                _root = new Link(path);
            else if (S_ISDIR(st.st_mode)) {
                _root = new Folder(path);
                DIR * dir = opendir(path);
                if (dir == nullptr)
                    throw string("open folder error");

                struct dirent * entry = nullptr;
                while((entry = readdir(dir)) != nullptr) {
                    if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
                        NodeBuilder nb;
                        
                        char * pathName = new char [(string(path) + "/" + entry->d_name).length()];
                        strcpy(pathName,path);
                        strcat(pathName,"/");
                        strcat(pathName,entry->d_name);
                        nb.build(pathName);
                        _root->add(nb.getRoot());
                    }
                }
            }
        }
    }

    Node * getRoot() {
        return _root;
    }

private:
    Node * _root;
};

#endif
