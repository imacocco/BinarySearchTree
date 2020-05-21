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

template<class T>
void FIND_AVE(T& my_map, std::size_t size, std::ofstream& file){
  double mean=0;
  double std=0;
  std::size_t n_sample = 200;
  for(std::size_t k=0;k<n_sample;k++){
    int random_key = rand() % static_cast<int>(size);
    t.start();
    my_map.find(random_key);
    auto appo=t.stop();
    mean+=appo;
    std+=appo*appo;
  }
  mean/=n_sample;
  std=sqrt((std-mean*mean))/n_sample;
  file<<size<< "\t"<<mean<<"\t"<<std<<std::endl;
  return;
}

template<class T>
void test_time_map(T& my_map, std::string nome,bool ordered){
  std::ofstream file{nome};
  for(std::size_t i=1000;i<50000;i+=1000){
    std::vector<int> v(i);
    std::iota(v.begin(),v.end(),0);
    if(!ordered)
      std::shuffle(v.begin(),v.end(),std::mt19937{std::random_device{}()});
    for(std::size_t l=0;l<i;l++){
      my_map[v[l]]=0;
    }
    FIND_AVE(my_map, i, file);
    my_map.clear();
  }
  return ;
}

void test_time_tree(std::string nome, bool balance, bool ordered_data){
  std::ofstream file{nome};
  BST::bst<int,int> tree{};
  std::vector<int> v;
  //cycle over number of (1000)*elements
  for(std::size_t i=1;i<50;++i){
      std::cout<<i<<std::endl;
      //if we want to balance, we simply add the new values and rebalance the tree
      //no difference if the initial data is ordered or not
      if(balance){
        for(std::size_t m = 0; m < 1000; ++m)
          tree[m+i*1000];
      
        tree.balance();

        FIND_AVE(tree, i, file);

      }
      //if we want to start from ordered data we just add them in order to the tree
      else if (ordered_data){
        for(std::size_t m = 0; m < 1000; ++m)
          tree[m+i*1000];

        FIND_AVE(tree, i, file);
      
      }
      //otherwise we add the data to a vector which is reshuffled and then add to an empty tree
      else{
        for (std::size_t m = 0; m < 1000; ++m)
          v.push_back(m+i*1000);

        std::shuffle(v.begin(),v.end(),std::mt19937{std::random_device{}()});
        for(std::size_t k = 0; k < i; ++k)
          tree[v[k]];

        FIND_AVE(tree, i, file);
        tree.clear();

      }
  }
  return ;
}


int main(){
  
  //benchmark_ordered
  std::map<int,int> or_map;
  std::unordered_map<int,int> un_map;
  bool ordered = true;
  test_time_map(or_map,"Benchmark/Ordered_map.txt",ordered);
  test_time_map(un_map,"Benchmark/Unordered_map.txt",ordered);
  test_time_tree("Benchmark/Unbalanced_tree.txt",false,ordered);
  
  //benchmark unordered
  ordered=false;
  test_time_map(or_map,"Benchmark_unordered/Ordered_map.txt",ordered);
  test_time_map(un_map,"Benchmark_unordered/Unordered_map.txt",ordered);
  test_time_tree("Benchmark_unordered/Unbalanced_tree.txt",false,ordered);
  test_time_tree("Benchmark_unordered/Balanced_tree.txt",true,ordered);

  return 0;


}