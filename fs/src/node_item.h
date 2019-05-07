#ifndef node_item_h
#define node_item_h

#include <wx/treectrl.h>
#include "node.h"

class NodeItem:public wxTreeItemData{
public:
    NodeItem(Node * node):_node(node){ }

    Node * getNodeItem(){
        return _node;
    }
private:
    Node * _node;
};

#endif