#ifndef __bst__
#define __bst__

#include "node.hpp"
#include "iterator.hpp"
#include <functional> //std::less
#include <vector>
namespace BST{
	//class templated on the values of the pair to be inserted in the tree K,V and on the 
	// comparison method which is in this case is chosen to be std::less

	template < class K, class V, class cmp=std::less<K> >
	class bst{
		
		using pair_type = typename std::pair<const K,V>;
		using node_type = typename AP_node::node<pair_type>;
		using iterator  = typename AP_it::__iterator<AP_node::node<pair_type>,pair_type>; 
		using const_iterator = typename AP_it::__iterator<AP_node::node<pair_type>,const pair_type>;
		
		private:
			
			cmp op;
			
			std::unique_ptr<node_type> head;

			
			node_type* __begin() const noexcept{
				if (!head) return nullptr;
				
				auto t = head.get();
				while(t->left)
					t=t->left.get();
				return t;
			}

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

			void erase_head();
			
			void erase_generic(iterator it_erase);

  	
		public:

			bst() noexcept : op{}, head{nullptr} {}
			bst(bst&& ) noexcept = default;  
			bst& operator=(bst&& ) noexcept = default;

			bst(const bst& ); 
			bst& operator=(const bst& tree ){
				(*this).clear;
    		for(auto i=tree.begin(); i != tree.end(); ++i){
      		(*this).insert(*i);
  			}
  			return *this;	
			}


			
			template<class... Types>  // variadic templates
        	std::pair<iterator,bool> emplace(Types&&... args) {
            	return insert(pair_type{std::forward<Types>(args)...});
        	}

			

  		template<class OT>
		  std::pair<iterator, bool> insert(OT&& x);


			iterator begin() noexcept { return iterator{__begin()};}
			const_iterator begin() const noexcept{ return const_iterator{__begin()};}
			const_iterator cbegin() const noexcept{ return const_iterator{__begin()};}
			
			iterator end() noexcept	{ return iterator{__end()};}
			const_iterator end() const noexcept { return const_iterator{__end()};}
			const_iterator cend() const noexcept { return const_iterator{__end()};}

			
			iterator find(const K& x);

			const_iterator find(const K& x) const;

			void clear(){
				this->head.reset();
			}




			void erase(const K& x);

    	void balance();

    	void sortedArrayToBST(std::vector<pair_type> data,int start, int end,bst &balanced_tree);

			template<class OT>
 			V& operator[](OT&& x){
 				return insert(pair_type{std::forward<OT>(x), V()}).first->second;
 			} 





			friend
			std::ostream& operator<<(std::ostream& os, const bst& x){
				
				for ( auto v : x ){
	    			std::cout << "Key = " << v.first << "\tValue = " << v.second  << std::endl;
				}

  				return os;
			}

  				
				/*for(auto i=x.begin();i != x.end();i++){
					std::cout<< i->first<<std::endl;
				}
				return os;*/
  				
 




				
	};
}
#endif
#include "../src/bst.cc"