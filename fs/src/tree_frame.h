#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include "node.h"
#include "node_item.h"
#include "node_builder.h"
#include "observer.h"

class TreeFrame : public wxFrame
{
public:
  TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height):wxFrame((wxFrame *) nullptr, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
  {
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(300,500), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS );
    m_pTextCtrl = new wxTextCtrl(this, -1, _T("Welcome To POSD_EDITOR"),wxPoint(300,0), wxSize(400,300) , wxTE_MULTILINE);
    m_Save = new wxButton(this, BUTTON_Save, _T("Save"), wxPoint(300, 300), wxSize(400,200), 0);

    wxString rootName =wxGetApp().argv[1];  //加參數
    char * root_name = new char[(rootName.mb_str()).length()];
    strcpy(root_name,rootName.mb_str());

    NodeBuilder nb;
    nb.build(root_name);
    Node * root=nb.getRoot();

    wxString label_name = root->name() + ", " + to_string(root->size());    
    wxTreeItemId rootId = _tree->AddRoot(label_name,-1,-1,new NodeItem(root));
    buildTree(root,rootId);
    
    _tree->ExpandAllChildren(rootId);
  }

  void buildTree(Node * root, wxTreeItemId rootId){
    NodeIterator * it = root->createIterator();
    for(it->first(); !it->isDone();it->next()){
      string label_name = it->currentItem()->name()+ ", " + to_string(it->currentItem()->size());
      wxTreeItemId childId = _tree->AppendItem(rootId,label_name,-1,-1,new NodeItem(it->currentItem()));
      buildTree(it->currentItem(),childId);
    }
  }

  void OnBegin(wxTreeEvent& event){
    wxTreeItemId id = event.GetItem();
    original_label = _tree->GetItemText(id);
  }

  void OnEdit(wxTreeEvent& event){
    // std::cout << "edited" << std::endl;
    wxString edit_label = event.GetLabel();
    // cout<< edit_label.mb_str() <<endl;
    wxString dialog_message = wxT("label edited: ")+edit_label+wxT(" --old name was ")+(original_label).mb_str();
    wxMessageDialog * dialog = new wxMessageDialog(this,dialog_message,wxT("Confirm"),wxYES_NO|wxCANCEL);
    if(dialog->ShowModal()!=wxID_YES)
      event.Veto();

    wxTreeItemId id = event.GetItem();
    NodeItem * fb = dynamic_cast<NodeItem*>(_tree->GetItemData(id));

    char * oldname = new char [(fb->getNodeItem()->path()).length()];
    strcpy(oldname,(fb->getNodeItem()->path().c_str()));
    
    if(fb->getNodeItem()->getParent()!=nullptr){
      char * newname = new char [(fb->getNodeItem()->getParent()->path()+"/"+edit_label.mb_str()).length()];
      strcpy(newname,(fb->getNodeItem()->getParent()->path()).c_str());
      strcat(newname,"/");
      strcat(newname,edit_label.mb_str());
      rename(oldname,newname);
      // cout<<oldname<<endl;
      // cout<<newname<<endl;

      fb->getNodeItem()->setPath(newname);
      // renametree(fb->getNodeItem());
      notify(_ob.back(),event);
    }
  }

  void OpenFile(wxTreeEvent& event){
    wxTreeItemId id = event.GetItem();
    NodeItem * fb = dynamic_cast<NodeItem*>(_tree->GetItemData(id));

    hover = fb->getNodeItem();  //給save_button

    ifstream in;
    in.open(fb->getNodeItem()->path(),ifstream::in);
    m_pTextCtrl->LoadFile(fb->getNodeItem()->path());

    struct stat st;
    if(lstat( fb->getNodeItem()->path().c_str() ,&st) == 0 && S_ISREG(st.st_mode)){
      int c=0;
      while((c=in.get())!=EOF && c<=127);
      if(c==EOF){
        ifstream inn;
        inn.open(fb->getNodeItem()->path(),ifstream::in);
        stringstream buffer;
        buffer << inn.rdbuf();
        // cout<<buffer.str()<<endl;  
        // m_pTextCtrl->LoadFile(fb->getNodeItem()->path());
        m_pTextCtrl = new wxTextCtrl(this, -1, buffer.str(),wxPoint(300,0), wxSize(400,300) , wxTE_MULTILINE);
      }else{
        m_pTextCtrl = new wxTextCtrl(this, -1, wxT("The file is not displayed in the editor because it uses an unsupported text encoding."),wxPoint(300,0), wxSize(400,300) , wxTE_MULTILINE);  
      }
    }else{
      m_pTextCtrl = new wxTextCtrl(this, -1, wxT("The file is not displayed in the editor because it uses an unsupported text encoding."),wxPoint(300,0), wxSize(400,300) , wxTE_MULTILINE);
    }
    in.close();
  }

  void OnSave(wxCommandEvent & event){
  //   wxMessageDialog * dialog = new wxMessageDialog(this,wxT("You want save?"),wxT("Confirm"),wxYES_NO|wxCANCEL);
  //   if(dialog->ShowModal()!=wxID_YES)m_pTextCtrl->LoadFile(hover->path());
  //   m_pTextCtrl->SaveFile(hover->path());
    notify();
  }

  void attach(Observer * ob){
    _ob.push_back(ob);
  }
  void detach(){
    _ob.back() = nullptr;
  }
  void notify(Observer * ob,wxTreeEvent& event){
    wxTreeItemId id = event.GetItem();
    NodeItem * fb = dynamic_cast<NodeItem*>(_tree->GetItemData(id));
    ob->update(fb->getNodeItem());
  }
  void notify(){
    _ob.back()->update();
  }

  Node * getHover(){
    return hover;
  }
  wxTextCtrl * getwxTextCtrl(){
    return m_pTextCtrl;
  }

  enum{
    BUTTON_Save = wxID_HIGHEST + 1
	};

  wxTreeCtrl *_tree;
  wxTextCtrl * m_pTextCtrl;
  wxButton * m_Save;
private:
  wxString original_label;
  Node * hover;
  vector<Observer*>_ob;
  DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
  EVT_TREE_BEGIN_LABEL_EDIT (wxID_ANY, TreeFrame::OnBegin)
  EVT_TREE_END_LABEL_EDIT (wxID_ANY, TreeFrame::OnEdit)
  EVT_TREE_SEL_CHANGED(wxID_ANY, TreeFrame::OpenFile)
  EVT_BUTTON(BUTTON_Save,TreeFrame::OnSave)
END_EVENT_TABLE()
#endif
