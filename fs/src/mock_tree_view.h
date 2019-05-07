#ifndef MOCK_TREE_VIEW_H
#define MOCK_TREE_VIEW_H
#include "tree_frame.h"
#include "observer.h"
#include "node.h"
#include "node_iterator.h"

class MockTreeView : public Observer {
public:
  MockTreeView(TreeFrame * tf) : _tf(tf) {
    _tf->attach(this);
  }

  void update(Node * root){
    NodeIterator * it = root->createIterator();
    for(it->first(); !it->isDone();it->next()){
      char * newname = new char[(it->currentItem()->getParent()->path()+"/"+it->currentItem()->name()).length()];
      strcpy(newname,(it->currentItem()->getParent()->path()).c_str());
      strcat(newname,"/");
      strcat(newname,(it->currentItem()->name()).c_str());
      it->currentItem()->setPath(newname);
      update(it->currentItem());
    }
  }

  void update(){
    wxMessageDialog * dialog = new wxMessageDialog(_tf,wxT("You want save?"),wxT("Confirm"),wxYES_NO|wxCANCEL);
    if(dialog->ShowModal()!=wxID_YES)_tf->getwxTextCtrl()->LoadFile(_tf->getHover()->path());
    _tf->getwxTextCtrl()->SaveFile(_tf->getHover()->path());
  }

private:
  TreeFrame * _tf;
};

#endif
