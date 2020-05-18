#ifndef __iterator_HPP__
#define __iterator_HPP__

#include <iterator>

namespace BST {
    template<typename K, typename V, typename cmp>
    class bst;
}
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
	  
	    /*if(t == NULL){
	            return;
	        inorder(t->left);
	        cout << t->data << " ";
	        inorder(t->right);
	    }*/


	  __iterator& operator++() noexcept{
		
		node* p;		  	

	    /*if (current == nullptr){
	        // ++ from end(). get the root of the tree
	        current = bst->head.get();

	        // error! ++ requested for an empty tree
	        if (current == nullptr)
	        	throw UnderflowException { };

	        // move to the smallest value in the tree,
	        // which is the first node inorder
	        while (current -> l != nullptr) {
	             current = current->l;
	        }
	    }*/
    
    //else
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
        	// stopping if the parent becomes NULL. a non-NULL parent
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

	  __iterator operator++(int) noexcept {
		    __iterator tmp{current};
		    ++(*this);
		    return tmp;
	  }
	  

	    // pre increment

	  friend bool operator==(const __iterator& a, const __iterator& b) {
		    return a.current == b.current;
	  }

	  friend bool operator!=(const __iterator& a, const __iterator& b) {
		    return !(a == b);
	  }

	  /*void print_node(){
	  	current->AP_node::print_node();
	  	return;
	  }*/


	  template<typename K, typename V, typename cmp>
      friend class 	BST::bst;


	};
}

#endif