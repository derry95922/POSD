#ifndef UT_FS_H
#define UT_FS_H

#include <gtest/gtest.h>
#include <sys/stat.h>
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "../src/node.h"
#include "../src/node_visitor.h"
#include "../src/node_builder.h"
#include "../src/find_link_visitor.h"
#include "../src/find_node_by_pathname_visitor.h"
using namespace std;

TEST (MiscTest, lstatOnFolder)
{
  const char * path = "./test_data";
  struct stat st;
  ASSERT_EQ(0, lstat(path, &st));
  ASSERT_EQ(4096, st.st_size);
  ASSERT_EQ(true, S_ISDIR(st.st_mode));
  ASSERT_EQ(false, S_ISREG(st.st_mode));
  ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

class FileSystemTest: public ::testing::Test
{
protected:
  void SetUp() override
  {
    test_data = new Folder ("./test_data");
    folder = new Folder("./test_data/folder");
    hello_cpp = new File("./test_data/hello.cpp");
    a_out = new File("./test_data/folder/a.out");
    hello = new Link("./test_data/hello", a_out);
    folder->add(a_out);
    test_data->add(folder);
    test_data->add(hello);
    test_data->add(hello_cpp);
  }

  void TearDown() override
  {
    delete a_out;
    delete hello_cpp;
    delete hello;
    delete folder;
    delete test_data;
  }

  Node * test_data;
  Node * folder;
  Node * hello_cpp;
  Node * a_out;
  Node * hello;

};

TEST_F (FileSystemTest, Size)
{
  ASSERT_EQ(4096,test_data->size());
  ASSERT_EQ(4096, folder->size());
  ASSERT_EQ(9, hello_cpp->size());
  ASSERT_EQ(5, a_out->size());
  ASSERT_EQ(12, hello->size());
  ASSERT_EQ(5, dynamic_cast<Link *>(hello)->getSource()->size());
  ASSERT_EQ(3, test_data->numberOfChildren());
}

TEST_F (FileSystemTest, Visitor)
{
  // NodeVisitor * flv = new FindLinkVisitor();
  InfoContentVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(5, icv->getContentSize());
  delete icv;

  // InfoContentVisitor * icv10 = new InfoContentVisitor();
  NodeVisitor * icv10 = new InfoContentVisitor();
  hello->accept(icv10);
  ASSERT_EQ(12,icv10->getContentSize());
  // icv = new InfoContentVisitor("");
  InfoContentVisitor * icv2 = new InfoContentVisitor();
  folder->accept(icv2);
  ASSERT_EQ(5, icv2->getContentSize());

  InfoContentVisitor * icv3 = new InfoContentVisitor();
  test_data->accept(icv3);
  ASSERT_EQ(26,icv3->getContentSize());
}
TEST_F (FileSystemTest,NodeIterator){
  std::unique_ptr<NodeIterator> it(test_data->createIterator());
  // NodeIterator * it = test_data->createIterator();
  it->first();
  ASSERT_EQ(4096, it->currentItem()->size());
  it->next();
  ASSERT_EQ(12, it->currentItem()->size());
  it->next();
  ASSERT_EQ(9, it->currentItem()->size());
  it->next();
  ASSERT_TRUE(it->isDone());
  ASSERT_ANY_THROW(it->currentItem());
  ASSERT_ANY_THROW(it->next());

  // delete it;
}

TEST_F (FileSystemTest, NodeBuilderOnFile) {
  NodeBuilder nb;
  nb.build("test_data/hello.cpp");
  ASSERT_EQ(9, nb.getRoot()->size());

  nb.build("test_data/hello");
  ASSERT_EQ(12, nb.getRoot()->size());
  // ASSERT_EQ(8432, dynamic_cast<Link *>(nb.getRoot())->getSource()->size());

  nb.build("test_data/folder");
  ASSERT_EQ(4096, nb.getRoot()->size());

  std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
  it->first();
  ASSERT_EQ(5, it->currentItem()->size());

  it->next();
  ASSERT_TRUE(it->isDone());

  nb.build("test_data");
  ASSERT_EQ(4096, nb.getRoot()->size());
  
}

TEST_F (FileSystemTest, NodeTypeError)
{
  ASSERT_ANY_THROW(new File("./test_data/folder"));//Do not indicate the file path.
  ASSERT_ANY_THROW(new Folder("./test_data/hello"));//Do not indicate the Folder path.
  ASSERT_ANY_THROW(new Link("./test_data/hello.cpp"));//Do not indicate the Link path.
}



TEST_F (FileSystemTest, FindLinkVisitor) {
  NodeBuilder nb;
  nb.build("test_data");
  // NodeIterator *it=nb.getRoot()->createIterator();
  // for(it->first();!it->isDone();it->next()){
  //   cout<<it->currentItem()->path()<<endl;
  // }
  // NodeVisitor * icv = new InfoContentVisitor();
  FindLinkVisitor * flv = new FindLinkVisitor();
  nb.getRoot()->accept(flv);
  ASSERT_EQ("hello",flv->getLinks()[0]->name());
  // ASSERT_EQ(0,flv->getLinks().size());

}

TEST (FindNodeByPathnameVisitor, Folder){
  Node * test_data = new Folder("./test_data");
  vector<string>* names = new vector<string>{string("test")};
  FindNodeByPathnameVisitor * fnpv = new FindNodeByPathnameVisitor(names);
  test_data->accept(fnpv);
  ASSERT_EQ(nullptr, fnpv->getNode());

  vector<string>* names1 = new vector<string>{string("test_data")};
  FindNodeByPathnameVisitor * fnpv1 = new FindNodeByPathnameVisitor(names1);
  test_data->accept(fnpv1);
  ASSERT_EQ(test_data, fnpv1->getNode());

  FindNodeByPathnameVisitor * fnpv2 = new FindNodeByPathnameVisitor(names1);
  test_data->accept(fnpv2);
  ASSERT_EQ(test_data, fnpv2->getNode());
  
}

TEST (FindNodeByPathnameVisitor, Link){
  Node * hello = new Link("./test_data/hello");
  vector<string>* names = new vector<string>{string("hello")};
  FindNodeByPathnameVisitor * fnpv = new FindNodeByPathnameVisitor(names);
  hello->accept(fnpv);
  ASSERT_EQ(hello, fnpv->getNode());
}

TEST (FindNodeByPathnameVisitor, LinkInFolder){
  Node * test_data = new Folder ("./test_data");
  Node * hello = new Link("./test_data/hello");
  test_data->add(hello);
  // ASSERT_EQ(test_data,hello->getParent());
  vector<string>* names = new vector<string>{string("test_data"), string("hello")};
  FindNodeByPathnameVisitor * fnpv = new FindNodeByPathnameVisitor(names);  
  test_data->accept(fnpv);
  ASSERT_EQ(hello, fnpv->getNode());
}

TEST (FindNodeByPathnameVisitor, nonExistingFileInFileSystem){
  Node * test_data = new Folder ("./test_data");
  vector<string>* names = new vector<string>{string("test_data"), string("helloWorld")};
  FindNodeByPathnameVisitor * fnpv = new FindNodeByPathnameVisitor(names);  
  test_data->accept(fnpv);
  ASSERT_EQ(nullptr, fnpv->getNode());
}

TEST (FindNodeByPathnameVisitor, FolderInFolder){
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder ("./test_data/folder");
  test_data->add(folder);
  vector<string>* names = new vector<string>{string("test_data"), string("folder")};
  FindNodeByPathnameVisitor * fnpv = new FindNodeByPathnameVisitor(names);  
  test_data->accept(fnpv);
  ASSERT_EQ(folder, fnpv->getNode());
}

// ////////////////////////////////////////

// TEST (fileTest, FileSearchItsSelf)
// {
//   Node * a_out = new File("./test_data/folder/a.out");
//   //ASSERT_EQ("a.out",a_out->name());
//   //cout<<a_out->name()<<endl;
//   //cout<<a_out->find("")<<endl;
//   ASSERT_EQ("a.out",a_out->find("a.out"));
// }

// TEST (fileTest, FileSearchNotItsSelf)
// {
//   Node * a_out = new File("./test_data/folder/a.out");
//   ASSERT_EQ("",a_out->find("b.out"));
// }

// TEST (fileTest, FolderSearchItsSelf)
// {
//   Node * folder = new Folder("./test_data/folder");
//   //cout<<folder->name()<<endl;
//   ASSERT_EQ("",folder->find("folder"));
// }

// TEST (fileTest, FolderSearchNotItsSelf)
// {
//   Node * folder = new Folder("./test_data/folder");
//   ASSERT_EQ("",folder->find("test_data"));
// }

// TEST (fileTest, SearchFileInFolder)
// {
//   Node * folder = new Folder("./test_data/folder");
//   Node * a_out = new File("./test_data/folder/a.out");
//   Node * b_out = new File("./test_data/folder/b.out");
//   folder->add(a_out);
//   folder->add(b_out);
//   // cout<<folder->name()<<endl;
//   // cout<<a_out->name()<<endl;
//   ASSERT_EQ("./a.out",folder->find("a.out"));
// }

// TEST (fileTest, SearchFolderInFolder)
// {
//   Node * test_data = new Folder ("./test_data");
//   Node * folder = new Folder("./test_data/folder");
//   test_data->add(folder);
//   ASSERT_EQ("./folder",test_data->find("folder"));
// }


// TEST (fileTest, SearchAllFolderInFolder)
// {
//   Node * test_data = new Folder ("./test_data");
//   Node * folder = new Folder("./test_data/folder");
//   Node * folder1 = new Folder("./test_data/folder/folder");
//   test_data->add(folder);
//   folder->add(folder1);
//   ASSERT_EQ("./folder\n./folder/folder",test_data->find("folder"));
// }

// TEST (fileTest, SearchAllFileInFolder){
//   Node * test_data = new Folder("./test_data");
//   Node * folder = new Folder("./test_data/folder");
//   Node * folder1 = new Folder("./test_data/folder/folder");
//   Node * a_out = new File("./test_data/a.out");
//   Node * a_out2 = new File("./test_data/folder/folder/a.out");
//   Node * a_out1 = new File("./test_data/folder/a.out");
  
//   test_data->add(folder);
//   test_data->add(a_out);
//   folder->add(folder1);
//   folder1->add(a_out2);
//   folder->add(a_out1);
//   ASSERT_EQ("./a.out\n./folder/a.out\n./folder/folder/a.out",test_data->find("a.out"));
// }

// TEST_F (FileSystemTest, Visitor1){
//   // File * a_out = new File("./test_data/folder/a.out");
//   NodeVisitor * icv = new InfoContentVisitor();
//   a_out->accept(icv);
//   ASSERT_EQ(5, icv->getContentSize());
//   delete icv;
//   icv = new InfoContentVisitor();
//   // NodeVisitor * icv2 = new InfoContentVisitor();
//   // Node * folder = new Folder("./test_data/folder");
//   // folder->add(a_out);
//   // folder->accept(icv2);
//   // ASSERT_EQ(8432, icv2->getContentSize());
//   NodeBuilder nb;
//   nb.build("test_data");
//   NodeVisitor * icv3 = new InfoContentVisitor();
//   nb.getRoot()->accept(icv3);
//   ASSERT_EQ(26,icv3->getContentSize());

// }

// TEST(VisitorTest,FileSearchFileItself){
//   NodeVisitor * fv = new FindVisitor("a.out");
//   Node * a_out = new File("./test_data/folder/a.out");
//   a_out->accept(fv);
//   ASSERT_EQ("a.out",fv->findResult());
// }

// TEST (VisitorTest, FileSearchNotItsSelf)
// {
//   NodeVisitor * fv = new FindVisitor("b.out");
//   Node * a_out = new File("./test_data/folder/a.out");
//   a_out->accept(fv);
//   ASSERT_EQ("",fv->findResult());
// }
// //1
// TEST (VisitorTest, FolderSearchItsSelf)
// {
//   NodeVisitor * fv = new FindVisitor("folder");
//   Node * folder = new Folder("./test_data/folder");
//   folder->accept(fv);
//   ASSERT_EQ("",fv->findResult());
// }

// TEST (VisitorTest, FolderSearchNotItsSelf)
// {
//   NodeVisitor * fv = new FindVisitor("test_data");
//   Node * folder = new Folder("./test_data/folder");
//   folder->accept(fv);
//   ASSERT_EQ("",fv->findResult());
// }


// TEST (VisitorTest, SearchFileInFolder)
// {
//   NodeVisitor * fv = new FindVisitor("a.out");
//   Node * folder = new Folder("./test_data/folder");
//   Node * a_out = new File("./test_data/folder/a.out");
//   folder->add(a_out);
//   folder->accept(fv);
//   ASSERT_EQ("./a.out",fv->findResult());
// }

// TEST (VisitorTest, SearchFolderInFolder)
// {
//   NodeVisitor * fv = new FindVisitor("folder");
//   Node * test_data = new Folder ("./test_data");
//   Node * folder = new Folder("./test_data/folder");
//   test_data->add(folder);
//   test_data->accept(fv);
//   ASSERT_EQ("./folder",fv->findResult());
// }

// TEST(VisitorTest,SearchAllFolderInFolder){
//   NodeVisitor * fv = new FindVisitor("folder");
//   Node * test_data = new Folder ("./test_data");
//   Node * folder = new Folder("./test_data/folder");
//   Node * folder1 = new Folder("./test_data/folder/folder");
//   test_data->add(folder);
//   folder->add(folder1);
//   test_data->accept(fv);
//   ASSERT_EQ("./folder\n./folder/folder",fv->findResult());
// }

// TEST(VisitorTest,SearchAllFileInFolder){
//   NodeVisitor * fv = new FindVisitor("a.out");
//   Node * test_data = new Folder("./test_data");
//   Node * folder = new Folder("./test_data/folder");
//   Node * folder1 = new Folder("./test_data/folder/folder");
//   Node * a_out = new File("./test_data/a.out");
//   Node * a_out1 = new File("./test_data/folder/a.out");
//   Node * a_out2 = new File("./test_data/folder/folder/a.out");
//   test_data->add(folder);
//   test_data->add(a_out);
//   folder->add(folder1);
//   folder1->add(a_out2);
//   folder->add(a_out1);
//   test_data->accept(fv);
//   ASSERT_EQ("./a.out\n./folder/a.out\n./folder/folder/a.out",fv->findResult());
// }

// TEST(FileSystemTest,NodeIterator){
//   Node * folder = new Folder("./test_data/folder");
//   Node * test_data = new Folder("./test_data");
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   Node * a_out = new File("./test_data/folder/a.out");
//   test_data->add(folder);
//   test_data->add(hello_cpp);
//   folder->add(a_out);
//   NodeIterator * it = test_data->createIterator();
//   it->first();
//   ASSERT_EQ(4096, it->currentItem()->size());
//   it->next();//
//   ASSERT_EQ(89, it->currentItem()->size());
//   it->next();
//   ASSERT_TRUE(it->isDone());
//   ASSERT_ANY_THROW(it->currentItem());
//   ASSERT_ANY_THROW(it->next());
// }

#endif
