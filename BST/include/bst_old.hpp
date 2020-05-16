#ifndef __bst__
#define __bst__

#include <memory>
#include <iterator>
#include <functional>
#include <iostream>
#include <utility>
#include "ap_error.h"




template < class K, class V, class cmp=std::less<K> >
class bst{

private:

	using pair = typename std::pair<K,V>;

	cmp op;
	
	struct node {
	    std::unique_ptr<node> l,r,u;
	    pair P;
	    
	    node(const pair& v, node* p) : l{p->l}, r{p->r}, u{p->u} , P{v} {
	      std::cout << "copy ctor" << std::endl;
	    }
	    node(pair&& v, node* p) : l{p->l}, r{p->r},u{p->u}, P{std::move(v)} {
	      std::cout << "move ctor" << std::endl;
	    }

	    node(const pair& v, node* pl, node* pr, node* pu) : l{pl}, r{pr}, u{pu} , P{v} {
	      std::cout << "custom ctor" << std::endl;
	    }

	    node(pair&& v, node* pl, node* pr, node* pu) : l{pl}, r{pr}, u{pu} , P{std::move(v)} {
	      std::cout << "custom move ctor" << std::endl;
	    }

	    
	    /*explicit node(const std::unique_ptr<node>& p) : P{p->P} {
	      if (p->r)
	        r = std::make_unique<node>(p->r);
		}*/
	};

  	std::unique_ptr<node> head;
  	
        
public:

    bst() noexcept = default;
	bst(bst&& ) noexcept = default;
	bst& operator=(bst&& ) noexcept = default;

	bst(const bst& );
	bst& operator=(const bst& );

	node* get_head(){return head.get();}


	template <typename O>
    class __iterator{
  
  using __it= typename bst<K,V,cmp>::__iterator<O>;
  using node = typename bst<K,V,cmp>::node;

  node* current;


  public:
  
  __iterator(node* x) noexcept : current{x} {}

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
    }*/


  __iterator& operator++() noexcept;  // pre increment

  friend bool operator==(const __iterator& a, const __iterator& b) {
	    return a.current == b.current;
  } 
  friend bool operator!=(const __iterator& a, const __iterator& b) {
	    return !(a == b);
  }
};

	using iterator = __iterator<pair>;
  	using const_iterator = __iterator<const pair>;

  	std::pair<const_iterator, bool> insert(const pair& x){
  		auto t = head.get();
  		if( t == nullptr ){
            auto new_node = new node {x,nullptr,nullptr,nullptr};
    		head.reset(new_node);
    		//t = std::make_unique<node>(std::forward<OT>(x), nullptr, nullptr, par);
            const_iterator tmp{t};
            return std::pair<const_iterator,bool>(tmp,1);
        }

        while(t != nullptr){
        	if(op(x.first,t->P.first)){
        		if(t->l != nullptr)
        			t=t->l.get();
        		else{
        			auto new_node = new node {x,nullptr,nullptr,t};
        			t->l.reset(new_node);
        			return std::pair<const_iterator,bool>(const_iterator{t},1);
        		}
        	}     		
        	else if(op(t->P.first,x.first)){
        		if(t->r != nullptr)
        		t=t->r.get();
        		else{
        			auto new_node = new node{x,nullptr,nullptr,t};
        			t->r.reset(new_node);
        			return std::pair<const_iterator,bool>(const_iterator{t},1);
        		}
        	}
        	else return std::pair<const_iterator,bool>(const_iterator{t},0);
        }
    }    

  	std::pair<const_iterator, bool> insert(pair&& x){
  		auto t=head.get();
  		if( t == nullptr ){
            auto new_node = new node {std::move(x),nullptr,nullptr,nullptr};
    		head.reset(new_node);
    		//t = std::make_unique<node>(std::forward<OT>(x), nullptr, nullptr, par);
            const_iterator tmp{new_node};
            return std::pair<const_iterator,bool>(tmp,1);
        }

        while(t != nullptr){
        	if(op(x.first,t->P.first)){
        		if(t->l != nullptr)
        			t=t->l.get();
        		else{
        			auto new_node = new node {std::move(x),nullptr,nullptr,t};
        			t->l.reset(new_node);
        			const_iterator tmp{new_node};
        			return std::pair<const_iterator,bool>(tmp,1);
        		}
        	}     		
        	else if(op(t->P.first,x.first)){
        		if(t->r != nullptr)
        		t=t->r.get();
        		else{
        			auto new_node = new node{std::move(x),nullptr,nullptr,t};
        			t->r.reset(new_node);
        			const_iterator tmp{new_node};
        			return std::pair<const_iterator,bool>(const_iterator{t},1);
        		}
        	}
        	else{ 
        		const_iterator tmp{t};
        		return std::pair<const_iterator,bool>(tmp,0);
        	}
        }
    }    



  	/*template<class OT>
  	std::pair<__iterator<OT>, bool> insert_p(OT&& x, node* t, node* par){
        if( t == nullptr ){
            auto new_node = new node {x,nullptr,nullptr,par};
    		t=new_node;
    		//t = std::make_unique<node>(std::forward<OT>(x), nullptr, nullptr, par);
            return std::pair<__iterator<OT>,bool>(__iterator<OT>{t},1);
        }
        else if(op(x.first,t->P.first)) 
           return insert( x, t->left, t );
        else if(!(op(x.first,t->P->first))) 
           return insert( x, t->right, t );
		else
           return std::pair<__iterator<OT>,bool>(__iterator<OT>{t},0);
	}

  	template <class OT>
	std::pair<__iterator<OT>, bool> insert(OT&& x){
		std::cout<<"ciao"<<std::endl;
		return insert_p(x, head.get() , nullptr);
	} */

	friend std::ostream& operator<<(std::ostream&, const bst<K,V,cmp>&);

	iterator begin() noexcept { return iterator{head.get()}; }
	iterator end() { return iterator{nullptr}; }

	const_iterator begin() const { return const_iterator{head.get()}; }
	const_iterator end() const { return const_iterator{nullptr}; }

	const_iterator cbegin() const { return const_iterator{head.get()}; }
	const_iterator cend() const { return const_iterator{nullptr}; }

	
	


};
#endif