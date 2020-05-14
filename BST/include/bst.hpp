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

	//template <class OT>
	std::pair<iterator, bool> insert(const pair_type& x); 
	std::pair<iterator, bool> insert(pair_type&& x);

	template <class O>
	friend std::ostream& operator<<(std::ostream&, const List<O>&);

	template <typename O>
	class __iterator;

	using iterator = __iterator<T>;
	using const_iterator = __iterator<const T>;

	iterator begin() noexcept { return iterator{head.get()}; }
	iterator end() { return iterator{nullptr}; }

	const_iterator begin() const { return const_iterator{head.get()}; }
	const_iterator end() const { return const_iterator{nullptr}; }

	const_iterator cbegin() const { return const_iterator{head.get()}; }
	const_iterator cend() const { return const_iterator{nullptr}; }

	




};
#endif