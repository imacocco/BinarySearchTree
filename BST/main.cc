#include "bst.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "timer.hpp"
#include <fstream>
#include <unordered_map>
#include <map>
#include <string>
timer<> t;

int main(){

  
  std::vector<int> key{1,2,3,4,5};
  BST::bst<int,int> tree{};
  for(std::size_t i=0;i<key.size();i++){
  	tree.insert(std::pair<int,int>(key[i],0));
  }
  std::cout<<"Printing the tree"<<std::endl;
  std::cout << tree;
  
  std::cout << "Value at the key=3 before put to operation: "<<tree[3]<<std::endl;
  std::cout << "tree[3]=4"<<std::endl;
  tree[3]=4;
  std::cout<< "Value at the key=3 after put to operation: "<<tree[3]<<std::endl;

  std::cout<< "call of tree.erase(5)" << std::endl;
  tree.erase(5);
  std::cout<<"Without the key=5"<<std::endl;
  std::cout<<tree<<std::endl;
  
  tree.emplace(12,3);
  std::cout<<"After call of emplace(12,3):"<<std::endl;
  std::cout<<tree<<std::endl;

  BST::bst<int,int> tree_copy{tree};
  tree.emplace(7,1);
  std::cout<<"Printing tree_copy after modification of tree -> tree_copy has not changed -> deep copy"<<std::endl;
  std::cout<<tree_copy<<std::endl;

  BST::bst<int,int> tree_move{std::move(tree)};
  tree.emplace(10,1);
  std::cout<<"Printing the original tree after it is moved to tree_move and performing an emplace(10,1)"<<std::endl;
  std::cout<<tree<<std::endl;

  std::cout<<"Printing the original tree which was moved to tree_move"<<std::endl;
  std::cout<< tree_move<<std::endl;

  tree.clear();
  std::cout<<"After clearing the tree has nothing:"<<std::endl;
  std::cout<<tree<<std::endl;

  std::cout << "test std::pair< std::string, std::string >" << std::endl;
  BST::bst<std::string, std::string > STR{};
  std::cout << "create and insert a pair:\nauto b = std::pair< std::string,std::string >('b', 'second element')\nSTR.insert(b)\n" << std::endl;
  auto a = std::pair<std::string,std::string>("b", "second element");
  STR.insert(a);
  std::cout << "emplace a pair: STR.emplace('a', 'first element')\n" << std::endl;
  STR.emplace("a", "first element");
  std::cout << "print the tree" << std::endl;
  std::cout << STR << std::endl;
  return 0;


}