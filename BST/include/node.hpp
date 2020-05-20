#ifndef __node_HPP__
#define __node_HPP__

#include <memory>  // std::unique_ptr
#include <iostream> //std::cout
#include <utility>  // std::pair
#include "ap_error.h"

namespace AP_node{

	// Definition and declaration of the templated node structure 
	// which will be inserted in the Binary Tree structure
	// The nodes have a value and they have three pointers pointing to right/left children and parent.

	template<class T>
	struct node{

		T value; 
		std::unique_ptr<node<T>> left;
		std::unique_ptr<node<T>> right;
		node<T>* upper; //this one is not a unique_ptr because it will be shared with the other children

		node() noexcept : value{}, left{nullptr}, right{nullptr}, upper{nullptr} {} //constructor setting value to zero and to nullptr all the pointers

	    node(const T& v, node<T>* pu) noexcept : value{v}, left{nullptr}, right{nullptr}, upper{pu}{  //custom ctor with value of the pointer for the father
	      #ifdef __DEBUG_NODE
          std::cout << "CALL: custom ctor AP_node::node" << std::endl;
          #endif
		}

		node(T&& v, node<T>* pu) noexcept : value{std::move(v)}, left{nullptr}, right{nullptr}, upper{pu}{ //move ctor
	      #ifdef __DEBUG_NODE
          std::cout << "CALL: custom mctor AP_node::node" << std::endl;
          #endif
		}
	};
}
#endif 
