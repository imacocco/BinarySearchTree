#ifndef __iterator_HPP__
#define __iterator_HPP__

#include <iterator>

namespace BST {
    template<typename K, typename V, typename cmp>
    class bst;
}


namespace AP_it{

	/**
 	 * Iterator class for the bst_tree with nodes having left and right children. 
 	 * The iterator has a pointer to a node called current.
 	 * The aim of these iterators is to move easily following the nodes 
 	 */
	template <typename node,typename O>
	class __iterator{
	  
	  node* current;
	
	  public:
	  
	  /**
	   * Explicit constructor of iterator, it initializes its temporary node to given a node
	   */
	  explicit __iterator(node* x) noexcept : current{x} {}

	  using value_type = O;
	  using difference_type = std::ptrdiff_t;
	  using iterator_category = std::forward_iterator_tag;
	  using reference = value_type&; 
	  using pointer = value_type*;

	  /**
	   * Dereferent operator, it dereference the iterator returning the value of the node 
	   * the iterator is pointing to
	   */
	  reference operator*() const noexcept { return current -> value; } 

	  /**
	   * Arrow operator, it returns a pointer to the value of the node 
	   * the iterator is pointing to
	   */	  
	  pointer operator->() const noexcept { return &(*(*this)); } 

	  /**
	   * pre-increment operator ++, it easily moves from a node to the in order successor node 
	   * along the tree
	   */
	  __iterator& operator++() noexcept{
		// allocate a pointer to a temporary node
		node* p;		  	

        if (current -> right != nullptr){
        // successor is the farthest left node of
        // right subtree
            current = current->right.get();

            while (current->left != nullptr) {
                  current = current->left.get();
            }
        }
        else{
        	// have already processed the left subtree, and
        	// there is no right subtree. move up the tree,
        	// looking for a parent for which current is a left child,
        	// stopping if the parent becomes nullptr. a non-nullptr parent
        	// is the successor. if parent is NULL, the original node
        	// was the last node inorder, and its successor
        	// is the end of the list
        	p = current->upper;
        	while (p != nullptr && current == p->right.get()){
                   current = p;
                   p = p->upper;
            }

            // if we were previously at the right-most node in
            // the tree, current = nullptr, and the iterator specifies
            // the end of the list
            current = p;
        }

        return *this;
	  }

	  /**
	   * post-increment operator ++, create a temporary iterator to the current node
	   * and then increase current with pre-increment 
	   */
	  __iterator operator++(int) noexcept {
		    __iterator tmp{current};
		    ++(*this);
		    return tmp;
	  }
	  
	  /**
	   * two iterators are equal if they point to the same node
	   */
	  friend bool operator==(const __iterator& a, const __iterator& b) {
		    return a.current == b.current;
	  }

	  /**
	   * not equal
	   */	  
	  friend bool operator!=(const __iterator& a, const __iterator& b) {
		    return !(a == b);
	  }

	  //we set as friend class the bst class in order to be able to access the data member
	  template<typename K, typename V, typename cmp>
      friend class 	BST::bst;


	};
}

#endif