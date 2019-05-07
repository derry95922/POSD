#include <gtest/gtest.h>
#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/link.h"
// #include "../src/info_content_visitor.h"
#include "../src/node_builder.h"
#include "../src/find_link_visitor.h"
#include "../src/find_node_by_pathname_visitor.h"

class FileSystemTest: public ::testing::Test
{
protected:
  void SetUp() override
  {
    test_data = new Folder ("./test_data");
    a_out     = new File("./test_data/a.out");
    folder  = new Folder("./test_data/folder");
    hello = new Link("./test_data/hello", a_out1);
    hello_cpp = new File("./test_data/hello.cpp");
    a_out1     = new File("./test_data/folder/a.out");
    folder1  = new Folder("./test_data/folder/folder");
    a_out2     = new File("./test_data/folder/folder/a.out");
    
    folder1->add(a_out2);
    folder->add(a_out1);
    folder->add(folder1);
    test_data->add(a_out);
    test_data->add(folder);
    test_data->add(hello);
    test_data->add(hello_cpp);
  }

  void TearDown() override
  {
    delete test_data;
    delete folder;
    delete folder1;
    delete hello;
    delete hello_cpp;
    delete a_out;
    delete a_out1;    
    delete a_out2;
  }

  Node * test_data;
  Node * folder;
  Node * folder1;
  Node * hello;
  Node * hello_cpp;
  Node * a_out;
  Node * a_out1;
  Node * a_out2;
};


TEST(FileTest,first){
  ASSERT_TRUE(true);
}

//no TEST_F
TEST_F(FileSystemTest,Size){  //注意名字(FileSystemTest)
    // Node * test_data = new Folder("./test_data");
    ASSERT_EQ(4096,test_data->size());
    // Node * folder = new Folder("./test_data/folder");
    ASSERT_EQ(4096, folder->size());
    // Node * hello_cpp = new File("./test_data/hello.cpp");
    ASSERT_EQ(89, hello_cpp->size());
    // test_data->add(folder);
    // test_data->add(hello_cpp);
    ASSERT_EQ(4,test_data->numberOfChildren());
}

TEST_F(FileSystemTest,InfoContent){
    ASSERT_EQ(5,a_out->infoContent());
    ASSERT_EQ(89,hello_cpp->infoContent());
    ASSERT_EQ(5,folder->infoContent());
    ASSERT_EQ(113,test_data->infoContent());
}
//HW4-5
TEST(VisitorTest,InfoContent){
  File * a_out = new File("./test_data/folder/a.out");
  NodeVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(5,icv->getContentSize());
  delete icv;

  NodeVisitor * icv2 = new InfoContentVisitor();
  Node * folder = new Folder("./test_data/folder");
  folder->add(a_out);
  folder->accept(icv2);
  ASSERT_EQ(5, icv2->getContentSize());

  NodeVisitor * icv3 = new InfoContentVisitor();
  Node * test_data = new Folder("./test_data");
  Node * hello_cpp = new File("./test_data/hello.cpp");
  test_data->add(folder);
  test_data->add(hello_cpp);
  test_data->accept(icv3);
  ASSERT_EQ(94,icv3->getContentSize());
}

TEST(VisitorTest,FileSearchFileItself){
  NodeVisitor * fv = new FindVisitor("a.out");
  Node * a_out = new File("./test_data/folder/a.out");
  a_out->accept(fv);
  ASSERT_EQ("a.out",fv->findResult());
}

TEST (VisitorTest, FileSearchNotItsSelf)
{
  NodeVisitor * fv = new FindVisitor("b.out");
  Node * a_out = new File("./test_data/folder/a.out");
  a_out->accept(fv);
  ASSERT_EQ("",fv->findResult());
}

TEST (VisitorTest, FolderSearchItsSelf)
{
  NodeVisitor * fv = new FindVisitor("folder");
  Node * folder = new Folder("./test_data/folder");
  folder->accept(fv);
  ASSERT_EQ("",fv->findResult());
}

TEST (VisitorTest, FolderSearchNotItsSelf)
{
  NodeVisitor * fv = new FindVisitor("test_data");
  Node * folder = new Folder("./test_data/folder");
  folder->accept(fv);
  ASSERT_EQ("",fv->findResult());
}


TEST (VisitorTest, SearchFileInFolder)
{
  NodeVisitor * fv = new FindVisitor("a.out");
  Node * folder = new Folder("./test_data/folder");
  Node * a_out = new File("./test_data/folder/a.out");
  folder->add(a_out);
  folder->accept(fv);
  ASSERT_EQ("./a.out",fv->findResult());
}

TEST (VisitorTest, SearchFolderInFolder)
{
  NodeVisitor * fv = new FindVisitor("folder");
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  test_data->add(folder);
  test_data->accept(fv);
  ASSERT_EQ("./folder",fv->findResult());
}

TEST(VisitorTest,SearchAllFolderInFolder){
  NodeVisitor * fv = new FindVisitor("folder");
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  Node * folder1 = new Folder("./test_data/folder/folder");
  test_data->add(folder);
  folder->add(folder1);
  test_data->accept(fv);
  ASSERT_EQ("./folder\n./folder/folder",fv->findResult());
}

TEST(VisitorTest,SearchAllFileInFolder){
  NodeVisitor * fv = new FindVisitor("a.out");
  Node * test_data = new Folder("./test_data");
  Node * folder = new Folder("./test_data/folder");
  Node * folder1 = new Folder("./test_data/folder/folder");
  Node * a_out = new File("./test_data/a.out");
  Node * a_out1 = new File("./test_data/folder/a.out");
  Node * a_out2 = new File("./test_data/folder/folder/a.out");
  test_data->add(folder);
  test_data->add(a_out);
  folder->add(folder1);
  folder1->add(a_out2);
  folder->add(a_out1);
  test_data->accept(fv);
  ASSERT_EQ("./a.out\n./folder/a.out\n./folder/folder/a.out",fv->findResult());
}

//HW6

TEST_F (FileSystemTest, Size_HW6)
{
  ASSERT_EQ(4096,test_data->size());
  ASSERT_EQ(4096, folder->size());
  ASSERT_EQ(89, hello_cpp->size());
  ASSERT_EQ(5, a_out->size());
  ASSERT_EQ(14, hello->size());
  // ASSERT_EQ(14, dynamic_cast<Link *>(hello)->getSource()->size());
  ASSERT_EQ(4, test_data->numberOfChildren());
}

TEST_F (FileSystemTest, Visitor)
{
  // NodeVisitor * flv = new FindLinkVisitor();
  InfoContentVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(5, icv->getContentSize());
  delete icv;

  NodeVisitor * icv10 = new InfoContentVisitor();
  // cout<<hello->size()<<endl;
  hello->accept(icv10);
  ASSERT_EQ(14,icv10->getContentSize());

  InfoContentVisitor * icv2 = new InfoContentVisitor();
  folder->accept(icv2);
  ASSERT_EQ(5, icv2->getContentSize());

  InfoContentVisitor * icv3 = new InfoContentVisitor();
  test_data->accept(icv3);
  ASSERT_EQ(113,icv3->getContentSize());

}
TEST_F (FileSystemTest,NodeIterator){
  std::unique_ptr<NodeIterator> it(test_data->createIterator());
  // NodeIterator * it = test_data->createIterator();
  it->first();
  ASSERT_EQ(5, it->currentItem()->size());
  it->next();
  ASSERT_EQ(4096, it->currentItem()->size());
  it->next();
  ASSERT_EQ(14, it->currentItem()->size());
  it->next();
  ASSERT_EQ(89, it->currentItem()->size());
  it->next();
  ASSERT_TRUE(it->isDone());
  ASSERT_ANY_THROW(it->currentItem());
  ASSERT_ANY_THROW(it->next());

  // delete it;
}

TEST_F (FileSystemTest, NodeBuilderOnFile) {
  NodeBuilder nb;
  nb.build("test_data/hello.cpp");
  ASSERT_EQ(89, nb.getRoot()->size());

  nb.build("test_data/hello");
  ASSERT_EQ(14, nb.getRoot()->size());
  // ASSERT_EQ(8432, dynamic_cast<Link *>(nb.getRoot())->getSource()->size());

  nb.build("test_data/folder");
  ASSERT_EQ(4096, nb.getRoot()->size());

  std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
  it->first();

  ASSERT_EQ(5, it->currentItem()->size());

  it->next();
  cout<<it->currentItem()->name()<<endl;
  
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

TEST (NodeBuilder, FindLinkVisitor) {
  NodeBuilder nb;
  nb.build("test_data");
  cout<<nb.getRoot()->name()<<endl;
  // NodeIterator *it=nb.getRoot()->createIterator();
  // for(it->first();!it->isDone();it->next()){
  //   cout<<it->currentItem()->path()<<endl;
  // }
  FindLinkVisitor * flv = new FindLinkVisitor();
  nb.getRoot()->accept(flv);
  ASSERT_EQ("hello",flv->getLinks()[0]->name());
  ASSERT_EQ(1,flv->getLinks().size());
}

// TEST(NodeBuilder, file){
//   NodeBuilder nb;
//   nb.build("makefile");
//   ASSERT_EQ(627, nb.getRoot()->size());
// }

//HW7

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