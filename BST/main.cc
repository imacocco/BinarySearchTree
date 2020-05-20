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
  
  std::cout << "Value at the key=3 before = "<<tree[3]<<std::endl;
  tree[3]=4;
  std::cout<< "Value at the key=3 after = "<<tree[3]<<std::endl;
  tree.erase(5);
  std::cout<<"Without the key=5"<<std::endl;
  std::cout<<tree<<std::endl;
  
  tree.emplace(12,3);
  std::cout<<"After emplace of (12,3):"<<std::endl;
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
  return 0;


}