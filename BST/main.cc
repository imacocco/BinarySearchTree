#include "bst.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "timer.hpp"
#include <fstream>
timer<> t;

template <typename T>
void print_vector(const std::vector<T>& v, const std::string& s) {
  std::cout << s << ": ";
  for (const auto& x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

int main(){


  std::vector<int> key{6,7,14,15,11,20,3,1,2,5};
  std::vector<int> value{0,2,0,0,0};	
  //print_vector(key,"key");
  BST::bst<int,int> tree{};
  for(std::size_t i=0;i<key.size();i++){
  	tree.insert(std::pair<int,int>(key[i],value[i]));
  }
  //std::cout << tree;
  
  std::cout<<tree[4]<<std::endl;
  std::cout << tree ;

  /*tree.clear();
  std::cout<< "After clear the tree: " <<std::endl;*/
  /*std::cout<<tree;
  tree.insert(std::pair<int,int>(1,1));*/
  /*std::cout<<tree.find(1)->first<<std::endl;
  tree.erase(10);
  tree.insert(std::pair<int,int>(6,5));
  //std::cout<<tree;
  //std::cout<<tree.begin()->first<<std::endl;
  tree.balance();

  std::cout<<tree.begin()->first<<std::endl;
  */
  std::cout<<std::endl;
  BST::bst<int,int> new_tree=tree;
  std::cout<<new_tree<<std::endl;
  tree.insert(std::pair<int,int>(25,1));
  std::cout<<new_tree<<std::endl;
  std::cout<<tree<<std::endl;

  std::ofstream Ut{"Unbalanced_tree.txt"};
  std::ofstream Ot{"Balanced_tree.txt"};
  std::ofstream Um{"Unordered_map.txt"};
  std::ofstream Om{"Ordered_map.txt"};
  //benchmark
  for(auto i=100; i < 50000; i+=500){
    std::vector<int> key(i);
    for(auto j=0;j<i;j++){
      key[j]=j;
    }
    std::random_shuffle(key.begin(), key.end());
    BST::bst<int,int> tree{};
    for(std::size_t i=0;i<key.size();i++){
        tree.insert(std::pair<int,int>(key[i],0));
    }
    double mean=0;
    double std=0;
    for(auto k=0;k<50;k++){
      int random_key= rand() % static_cast<int>(i);
      t.start();
      tree.find(random_key);
      auto appo=t.stop();
      mean+=appo;
      std+=appo*appo;
    }
    mean/=50;
    std=sqrt((std-mean*mean))/50;
    Ut<<i<< "\t"<<mean<<"\t"<<std<<std::endl;
  }






  return 0;


}