#ifndef __node_HPP__
#define __node_HPP__

#include <memory>  // std::unique_ptr
#include <iostream> //std::cout
#include <utility>  // std::pair
#include "ap_error.h"

namespace AP_node{

	// Definition and declaration of the templated node structure 
	// which will be inserted in the Binary Tree structure
	// The nodes have a value which in this implementation is implied to be under
	// the form of a std::pair. Then they have three pointers pointing to right/left children and parent.

	template<class T>
	struct node{

		T value; 
		std::unique_ptr<node<T>> left;
		std::unique_ptr<node<T>> right;
		std::shared_ptr<node<T>> upper; 

		node() noexcept : value{}, left{nullptr}, right{nullptr}, upper{nullptr} {}

	    node(const T& v, node<T>* pu) noexcept : value{v}, left{nullptr}, right{nullptr}, upper{pu}{
	      #ifdef __DEBUG_NODE
          std::cout << "CALL: custom ctor AP_node::node" << std::endl;
          #endif
		}

		node(T&& v, node<T>* pu) noexcept : value{std::move(v)}, left{nullptr}, right{nullptr}, upper{pu}{
	      #ifdef __DEBUG_NODE
          std::cout << "CALL: custom mctor AP_node::node" << std::endl;
          #endif
		}

		//~node();


		template<class O>
		friend std::ostream& operator<<(std::ostream& os, const node<O>& n){
			os << "Key = " << n->v.first << "\tValue = " << n->v.second << std::endl;
			return os;
		};
	



	};
}

#endif 
