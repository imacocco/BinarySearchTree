#ifndef __iterator_HPP__
#define __iterator_HPP__

#include <iterator>

namespace BST {
    template<typename K, typename V, typename cmp>
    class bst;
}

//iterator class for the bst_tree with nodes having left and right children. 
//The iterator has a pointer to a node called current.
//The aim of these iterators is to move easily following the nodes 

namespace AP_it{
	template <typename node,typename O>
	class __iterator{
	  
	  node* current;
	
	  public:
	  
	  __iterator(node* x) noexcept : current{x} {}

	  using value_type = O;
	  using difference_type = std::ptrdiff_t;
	  using iterator_category = std::forward_iterator_tag;
	  using reference = value_type&; 
	  using pointer = value_type*;

	  reference operator*() const noexcept { return current -> value; } 
	  pointer operator->() const noexcept { return &(*(*this)); } 

	  //pre-increment operator ++ to get the in order successor along the tree
	  __iterator& operator++() noexcept{
		
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

	  //post-increment operator ++
	  __iterator operator++(int) noexcept {
		    __iterator tmp{current};
		    ++(*this);
		    return tmp;
	  }
	  

	  friend bool operator==(const __iterator& a, const __iterator& b) {
		    return a.current == b.current;
	  }

	  friend bool operator!=(const __iterator& a, const __iterator& b) {
		    return !(a == b);
	  }

	  //we set as friend class the bst class in order to be able to access the data member
	  template<typename K, typename V, typename cmp>
      friend class 	BST::bst;


	};
}

#endif