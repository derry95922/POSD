#include <wx/wx.h>
#include "tree_test.h"
#include "tree_frame.h"
#include <string>
#include <iostream>
#include "mock_tree_view.h"
using namespace std;

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit() 
{
  TreeFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100,100,700,500);
  frame->Show(true);
  Observer * ob = new MockTreeView(frame);
  this->SetTopWindow(frame);
  return true;
}
