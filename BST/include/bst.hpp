#ifndef __bst__
#define __bst__

#include "node.hpp"
#include "iterator.hpp"
#include <functional> //std::less
#include <vector>

namespace BST{
	
	//class templated on the values of the pair to be inserted in the tree K,V and on the 
	// comparison method which is in this case is chosen to be std::less
	//most of the implementation are performed on src/bst.cc

	template < class K, class V, class cmp=std::less<K> >
	class bst{
		
		using pair_type = typename std::pair<const K,V>;
		using node_type = typename AP_node::node<pair_type>;
		using iterator  = typename AP_it::__iterator<AP_node::node<pair_type>,pair_type>; 
		using const_iterator = typename AP_it::__iterator<AP_node::node<pair_type>,const pair_type>;
		
		private:
			
			cmp op; //defition of the operator less which will be called op
			
			std::unique_ptr<node_type> head;  //the tree has a head which points to the first node

			//function which return the pointer to the leftmost node
			node_type* __begin() const noexcept{
				if (!head) return nullptr;
				
				auto t = head.get();
				while(t->left)
					t=t->left.get();
				return t;
			}

			//function returning the pointer to the one past the rightmost node 
			node_type* __end() const noexcept {
				auto t = head.get();
				if(t == nullptr)
					return t;
				else{
					while(t)
						t=t->right.get();
					return t;
				}
			}

			//function which erase the head which is called within the public erase function
			void erase_head();
			
			//function which erase a generic node within the tree which is
			//called from the publica erase function
			void erase_generic(iterator it_erase);

  	
		public:

			bst() noexcept : op{}, head{nullptr} {}  //empty constructor 
			bst(bst&& ) noexcept = default;   //default move constructor
			bst& operator=(bst&& ) noexcept = default; //default move assignment

			bst(const bst& ); //copy constructor
			bst& operator=(const bst& tree ){ //copy assignement
				(*this).clear;
    		for(auto i=tree.begin(); i != tree.end(); ++i){
      		(*this).insert(*i);
  			}
  			return *this;	
			}


			
			template<class... Types>  // variadic templates
      std::pair<iterator,bool> emplace(Types&&... args) { //insert for variadics arguments
           return insert(pair_type{std::forward<Types>(args)...});
      }

			
      //insert operator accepting both rvalue and lvalue variable thanks to the 
      //extra template OT. It returns a pair made up by the iterator pointing to the node in which
      //such key was inserted and a bool which is true if the key has been inserted 
  		template<class OT>
		  std::pair<iterator, bool> insert(OT&& x);  

		  //begin function returning the iterator pointing to the first node
			iterator begin() noexcept { return iterator{__begin()};}
			const_iterator begin() const noexcept{ return const_iterator{__begin()};}
			const_iterator cbegin() const noexcept{ return const_iterator{__begin()};}
			
			//iterator pointing to the end node
			iterator end() noexcept	{ return iterator{__end()};}
			const_iterator end() const noexcept { return const_iterator{__end()};}
			const_iterator cend() const noexcept { return const_iterator{__end()};}

			//function returning the iterator pointing to 
			//the node having key x if present otherwise nullptr
			iterator find(const K& x);

			const_iterator find(const K& x) const;

			//function which clears the whole bst
			void clear(){
				this->head.reset();
			}

			//function erasing the node having the key x
			void erase(const K& x);

			//function which balance the the bst
    	void balance();
    	//helping function for balance
    	void sortedArrayToBST(std::vector<pair_type> data,int start, int end,bst &balanced_tree);

    	//put-to operator returning the value corresponding such key if present
    	//otherwise it adds the node and set the value to zero
    	//this can act both on rvalue and lvalue thakns to 
    	//the template OT
			template<class OT>
 			V& operator[](OT&& x){
 				return insert(pair_type{std::forward<OT>(x), V()}).first->second;
 			} 

 			//stream operator for printing the tree
			friend
			std::ostream& operator<<(std::ostream& os, const bst& x){
				if(x.head.get() == nullptr)
					std::cout<<"The tree is empty"<<std::endl;

				for ( auto v : x )
	    			std::cout << "Key = " << v.first << "\tValue = " << v.second  << std::endl;
				return os;
			}
				
	};
}
#endif
#include "../src/bst.cc"