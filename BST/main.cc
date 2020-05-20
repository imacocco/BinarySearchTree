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
      double mean=0;
      double std=0;
      std::size_t n_sample = 200;
      for(std::size_t k=0;k<n_sample;k++){
        int random_key= rand() % static_cast<int>(i);
        t.start();
        my_map.find(random_key);
        auto appo=t.stop();
        mean+=appo;
        std+=appo*appo;
      }
      mean/=n_sample;
      std=sqrt((std-mean*mean))/n_sample;
      file<<i<< "\t"<<mean<<"\t"<<std<<std::endl;
      my_map.clear();
  }
  return ;
}

void test_time_tree(std::string nome, bool balance, bool ordered){
  std::ofstream file{nome};
  BST::bst<int,int> tree{};
  for(std::size_t i=1000;i<50000;i+=1000){
      std::cout<<i<<std::endl;
      std::vector<int> v(i);
      std::iota(v.begin(),v.end(),0);
      if(!ordered)
        std::shuffle(v.begin(),v.end(),std::mt19937{std::random_device{}()});
      for(std::size_t l=0;l<i;l++){
          tree[v[l]]=0;
      }
      if(balance) 
        tree.balance();

      double mean=0;
      double std=0;
      std::size_t n_sample = 200;
      for(std::size_t k=0;k<n_sample;k++){
        int random_key= rand() % static_cast<int>(i);
        t.start();
        tree.find(random_key);
        auto appo=t.stop();
        mean+=appo;
        std+=appo*appo;
      }
      mean/=n_sample;
      std=sqrt((std-mean*mean))/n_sample;
      file<<i<< "\t"<<mean<<"\t"<<std<<std::endl;
      tree.clear();
  }
  return ;
}


int main(){

  /*
  std::vector<int> key{1,2,3,4,5,6,7,8,9,10};
  //std::vector<int> value{0,2,0,0,0};	
  //print_vector(key,"key");
  BST::bst<int,int> tree{};
  for(std::size_t i=0;i<key.size();i++){
  	tree.insert(std::pair<int,int>(key[i],0));
  }
  //std::cout << tree;
  
  std::cout << tree<<std::endl;

  tree.balance();*/

  
  //benchmark_ordered
  std::map<int,int> or_map;
  std::unordered_map<int,int> un_map;
  bool ordered = true;
  test_time_map(or_map,"Benchmark/Ordered_map.txt",ordered);
  test_time_map(un_map,"Benchmark/Unordered_map.txt",ordered);
  std::cout<<"Unbalanced_tree"<<std::endl;
  test_time_tree("Benchmark/Unbalanced_tree.txt",0,ordered);
  std::cout<<"Balanced_tree"<<std::endl;
  test_time_tree("Benchmark/Balanced_tree.txt",1,ordered);

  //benchmark unordered
  ordered=false;
  test_time_map(or_map,"Benchmark_unordered/Ordered_map.txt",ordered);
  test_time_map(un_map,"Benchmark_unordered/Unordered_map.txt",ordered);
  test_time_tree("Benchmark_unordered/Unbalanced_tree.txt",0,ordered);
  test_time_tree("Benchmark_unordered/Balanced_tree.txt",1,ordered);

  return 0;


}