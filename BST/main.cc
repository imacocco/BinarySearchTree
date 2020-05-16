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


  std::vector<int> key{1,4,3,7,9};
  std::vector<int> value{0,0,0,0,0};	
  print_vector(key,"key");
  BST::bst<int,int> tree{};
  for(std::size_t i=0;i<key.size();i++){
  	tree.insert(std::pair<int,int>(key[i],value[i]));
  }
  std::cout<<"ciao"<<std::endl;
  //std::cout<<tree<<std::endl;
  //tree.insert() 
  return 0;


}
