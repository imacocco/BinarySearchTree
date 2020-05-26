#ifndef __bst__
#define __bst__

#include "node.hpp"
#include "iterator.hpp"
#include <functional> //std::less
#include <vector>

namespace BST{
	
	/**
	 * Binary Search Tree class, templated on the values to be assigned to the nodes and on the comprison method
	 * In this particular case, the data is initialised to a std::pair<key_type =K, value_typr=V> 
	 * and the comparison method is chosen to be std::less<key_type>.
	 * Most of the implementations are written in src/bst.cc
	 */

	template < class K, class V, class cmp=std::less<K> >
	class bst{
		
		using pair_type = typename std::pair<const K,V>;
		using node_type = typename AP_node::node<pair_type>;
		using iterator  = typename AP_it::__iterator<AP_node::node<pair_type>,pair_type>; 
		using const_iterator = typename AP_it::__iterator<AP_node::node<pair_type>,const pair_type>;
		
		private:
			/**
			 * Declaration of the "less" operator as a data memmber of the class
			 * It will be called as op(LHS, RHS) and returns true if LHS < RHS
			 */
			cmp op; 
			
			/**
			 * The tree has a head which points to the first inserted node
			 */
			std::unique_ptr<node_type> head;  

			/**
			 * Returns a pointer to the leftmost node 
			 */
			node_type* __begin() const noexcept{
				if (!head) return nullptr;
				
				auto t = head.get();
				while(t->left)
					t=t->left.get();
				return t;
			}

			/**
			 * Returns a pointer to the one past the rightmost node 
			 */
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

			/**
			 * erases the head; it is called within the public erase() function
			 */
			void erase_head();
			
			/**
			 * erases a generic node within the tree;
			 * it is called within the public erase() function
			 */
			void erase_generic(iterator it_erase);

  	
		public:

			/**
			 * Default (empty) constructor of a BST;
			 * it initialize the comparison method to default
			 * and the head to nullptr
			 */
			bst() noexcept : op{}, head{nullptr} {}

			/**
			 * Default move constructor of a BST
			 */
			explicit bst(bst&&) noexcept = default;

			/**
			 * Default move assignement of a BST
			 */
			bst& operator=(bst&&) noexcept = default;

			/**
			 * Copy constructor of a BST
			 */
			explicit bst(const bst&);		

			/**
			 * Copy assignement	
			 */
			bst& operator=(const bst& tree){

				(*this).clear;
				bst tree_new(tree);
				*this = std::move(tree_new);
				return *this;
			}

			/**
			 * Emplace function, inserts a node with the simple expression emplace(a,b)
			 * while insert needs an explicit pair_type
			 */
			template<class... Types>  // variadic templates
      std::pair<iterator,bool> emplace(Types&&... args) {
           return insert(pair_type{std::forward<Types>(args)...});
      }

      /**
       * helper copy function
       */
      void __copy(const bst& t, std::unique_ptr<node_type>&);

			/**
       * insert operator accepts both rvalue and lvalue variables thanks to the 
       * extra template OT. It returns a pair made up by the iterator pointing to the inserted node
       * and a bool which is true if the key has been inserted or false if it was already present
       */
  		template<class OT>
		  std::pair<iterator, bool> insert(OT&& x);  

		  /**
		   * returns an iterator pointing to the first node
		   */
			iterator begin() noexcept { return iterator{__begin()};}
		  /**
		   * returns a constant iterator pointing to the first node
		   */
			const_iterator begin() const noexcept{ return const_iterator{__begin()};}
		  /**
		   * returns a constant iterator pointing to the first node
		   */			
			const_iterator cbegin() const noexcept{ return const_iterator{__begin()};}
			
		  /**
		   * returns an iterator pointing to the node found with __end()
		   */
			iterator end() noexcept	{ return iterator{__end()};}
		  /**
		   * returns a constant iterator pointing to the node found with __end()
		   */
			const_iterator end() const noexcept { return const_iterator{__end()};}
		  /**
		   * returns a constant iterator pointing to the node found with __end()
		   */
			const_iterator cend() const noexcept { return const_iterator{__end()};}

			/**
			 * navigate from the head using the op operator and stopping if the key is found.
			 * If key x is present, it returns the iterator pointing to the corresponding node;
			 * otherwise ir returns nullptr
			 */
			iterator find(const K& x);
			/**
			 * const interator version of find() funxtion
			 */
			const_iterator find(const K& x) const;

			/**
			 * clears the whole bst by resetting the head to nullptr
			 */
			void clear(){
				this->head.reset();
			}

			/**
			 * erases the node having the key x if present; is such a case the tree needs
			 * to be "jointed" back in order not to lose the parent-child relationships
			 * see src/bst.cc implementation for a step-by-step explanation
			 */ 
			void erase(const K& x);

			/**
			 * balances the the bst by successively inserting the median of the odered
			 * sub-vectors associated with the tree. See src/bst.cc implementation for a step-by-step explanation
			 */
    	void balance();

    	/**
    	 * helping function for balance()
    	 */
    	void sortedArrayToBST(std::vector<pair_type> data,int start, int end,bst &balanced_tree);

    	/**
    	 * put-to operator, returs the value corresponding to such key if present;
    	 * otherwise it adds the node and set the value to zero or to the rhs_value, according to
    	 * bst[key] = rhs_value.
    	 * It can act both on rvalue and lvalue thanks to the extra template OT
    	 */
			template<class OT>
 			V& operator[](OT&& x){
 				return insert(pair_type{std::forward<OT>(x), V()}).first->second;
 			} 

 			/**
 			 * stream operator, prints each node of the tree from the first to the last
 			 * node according to the comparison method
 			 */
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