#include <iostream>
#include <fstream>
#include "AnyData.h"
#include "string"
#include "Tree.h"
using namespace Sukhinsky;

// I thout that it would be strange if you will have a problem with making sample tree to test the code
// So that tree is the same with a tree from task description
Tree::Tree sampleTree() {
   AnyData::AnyData data0 = AnyData::AnyData(8);
   AnyData::AnyData data1 = AnyData::AnyData(std::string("bar"));
   AnyData::AnyData data2 = AnyData::AnyData(2.015);
   AnyData::AnyData data3 = AnyData::AnyData(2015);
   AnyData::AnyData data4 = AnyData::AnyData(std::string("2015"));
   AnyData::AnyData data5 = AnyData::AnyData(9);
   AnyData::AnyData data6 = AnyData::AnyData(std::string("baz"));
   AnyData::AnyData data7 = AnyData::AnyData(std::string("foo"));
   AnyData::AnyData data8 = AnyData::AnyData(6.28318);
   AnyData::AnyData data9 = AnyData::AnyData(std::string("hello"));

   Tree::Tree obj = Tree::Tree(data0);
   auto iter = obj.beginPreOrder();
   iter.insertChild(AnyData::AnyData(data1));
   iter.insertChild(AnyData::AnyData(data6));
   iter++;
   iter.insertChild(AnyData::AnyData(data2));
   iter.insertChild(AnyData::AnyData(data3));
   iter.insertChild(AnyData::AnyData(data4));
   iter++;
   iter.insertChild(AnyData::AnyData(data5));
   iter++;
   iter++;
   iter++;
   iter++;
   iter.insertChild(AnyData::AnyData(data7));
   iter.insertChild(AnyData::AnyData(data8));
   iter++;
   iter++;
   iter.insertChild(AnyData::AnyData(data9));
   return obj;
}


int main(int argc, const char ** argv) {

   if (argc != 5) { // prog -i i_name -o o_name
      std::cout << "Sorry, Dear User, but I can't work without my standart parameters: " << std::endl;
      std::cout << " -i - name of file, which contains serialized tree " << std::endl;
      std::cout << " -o - name of file, which will be used for tree serialization " << std::endl;
   }
   else {
      std::ifstream input(argv[2]);
      std::ofstream output(argv[4]);

      Tree::Tree tree = sampleTree();
      tree.ASCIIVisualisation(std::cout);
      tree.serialize(output);
   }

}