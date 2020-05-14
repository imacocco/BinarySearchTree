#include "bst.hpp"

template < class K, class V, class cmp=std::less<K> > 
template <typename O>
class bst<K, V, cmp>::__iterator {
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

  if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

  __iterator& operator++() noexcept {  // pre increment
        if(iterator->right=nullptr)
        	return;

        
        current = current->l.get();
	    return *this;

  friend bool operator==(const __iterator& a, const __iterator& b) {
	    return a.current == b.current;
  } 
  friend bool operator!=(const __iterator& a, const __iterator& b) {
	    return !(a == b);
  }
};

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