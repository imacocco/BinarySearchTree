#include "bst.hpp"
#include <vector>

template <typename T>
void print_vector(const std::vector<T>& v, const std::string& s) {
  std::cout << s << ": ";
  for (const auto& x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

int main(){


  std::vector<int> key{6,7,10,15,11,20};
  std::vector<int> value{0,2,0,0,0};	
  print_vector(key,"key");
  BST::bst<int,int> tree{};
  for(std::size_t i=0;i<key.size();i++){
  	tree.insert(std::pair<int,int>(key[i],value[i]));
  }
  std::cout << tree;
  
  std::cout<<tree[4]<<std::endl;
  //std::cout << tree ;

  /*tree.clear();
  std::cout<< "After clear the tree: " <<std::endl;
  std::cout<<tree;
  tree.insert(std::pair<int,int>(1,1));
  std::cout<<tree.find(1)->first<<std::endl;*/
  tree.erase(6);
  tree.insert(std::pair<int,int>(6,5));
  std::cout<<tree;


  return 0;


}
