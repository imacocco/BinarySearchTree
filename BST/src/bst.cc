#include "bst.hpp"


/*
template < class K, class V, class cmp> 
template <typename O>
class bst<K, V, cmp>::__iterator {
  
  using __it= typename bst<K,V,cmp>::__iterator<O>;
  using node = typename bst<K,V,cmp>::node;

  node* current;


  public:
  
  explicit __iterator(node* x) noexcept : current{x} {}

  using value_type = O;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = value_type&; 
  using pointer = value_type*;

  reference operator*() const noexcept { return current->P; }
  pointer operator->() const noexcept { return &(*(*this)); }
  /*
  }

  __iterator& operator+r() noexcept {  // pre increment
        current = current->r.get();
	    return *this;
  }

  __iterator& operator--() noexcept {  // pre increment
        current = current->u.get();
	    return *this;
  }*/

  /*__iterator operator++(int) noexcept {
	    __iterator tmp{current};
	    ++(*this);
	    return tmp;
	  }
  */

  /*if(t == NULL){
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }


  __iterator& operator++() noexcept;  // pre increment

  friend bool operator==(const __iterator& a, const __iterator& b) {
	    return a.current == b.current;
  } 
  friend bool operator!=(const __iterator& a, const __iterator& b) {
	    return !(a == b);
  }
};*/

template <class K,class V, class cmp>
std::ostream& operator<<(std::ostream& os, const bst<K,V,cmp>& tree){
    auto tmp = tree.begin();
    while (tmp){
      os << *tmp->P.first << " " << *tmp->P.second << std::endl;
      ++tmp;
    }
    return os;
}

template < class K, class V, class cmp>
template <class O> 
typename bst<K,V,cmp>::template __iterator<O>& bst<K,V,cmp>::template __iterator<O>::operator++() noexcept{
    node *p;

    /*if (current == nullptr){
        // ++ from end(). get the root of the tree
        current = bst->head.get();

        // error! ++ requested for an empty tree
        if (current == nullptr)
        	throw UnderflowException { };

        // move to the smallest value in the tree,
        // which is the first node inorder
        while (current->l != nullptr) {
             current = current->l;
        }
    }*/
    
    //else
        if (current->r != nullptr){
        // successor is the farthest left node of
        // right subtree
            current = current->r;

            while (current->l != nullptr) {
                  current = current->l;
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
        	p = current->u;
        	while (p != nullptr && current == p->r){
                   current = p;
                   p = p->u;
            }

            // if we were previously at the right-most node in
            // the tree, current = nullptr, and the iterator specifies
            // the end of the list
            current = p;
        }

        return *this;
}



/*










	template <class T>
	typename List<T>::node* List<T>::tail() noexcept {
	  auto tmp = head.get();

	  while (tmp->next)
	    tmp = tmp->next.get();

	  return tmp;
	}

	template <class T>
	template <class OT>
	void List<T>::insert(OT&& v, const method m) {
	  if (!head) {
	    // head.reset(new node{v,nullptr});
	    head = std::make_unique<node>(std::forward<OT>(v), nullptr);
	    return;
	  }
	  switch (m) {
	    case method::push_back:
	      push_back(std::forward<OT>(v));
	      break;

	    case method::push_front:
	      push_front(std::forward<OT>(v));
	      break;
	    default:
	      AP_ERROR(false) << "Unknown insertion method";
	      break;
	  };
	}

	template <class T>
	template <class OT>
	void List<T>::push_back(OT&& v) {
	  node* last = tail();
	  // last->next.reset(new node{v, nullptr});
	  last->next = std::make_unique<node>(std::forward<OT>(v), nullptr);
	}

	template <class T>
	std::ostream& operator<<(std::ostream& os, const List<T>& l) {
	  auto tmp = l.head.get();
	  while (tmp) {
	    os << tmp->value << " ";
	    tmp = tmp->next.get();
	  }
	  return os;
	}

	template <class T>
	List<T>::List(const List& l) {
	  // auto tmp = l.head.get();
	  // while(tmp){
	  //   insert(tmp->value,method::push_back);
	  //   tmp=tmp->next.get();
	  // }
	  head = std::make_unique<node>(l.head);
	}

*/
