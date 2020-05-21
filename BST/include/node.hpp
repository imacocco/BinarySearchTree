#ifndef __node_HPP__
#define __node_HPP__

#include <memory>  // std::unique_ptr
#include <iostream> //std::cout
#include <utility>  // std::pair

namespace AP_node{

	/** 
	 * Definition and declaration of the templated node structure 
	 * which will be inserted in the Binary Tree structure.
	 * The nodes have a value and they have three pointers pointing to right/left children and parent.
	 */ 

	template<class T>
	struct node{

		/**
		 * templated value contained by the node
		 */
		T value;

		/**
		 * unique pointer to the left child (which is clearly a node templated on the value type)
		 */		 
		std::unique_ptr<node<T>> left;
		/**
		 * unique pointer to the right child
		 */		
		std::unique_ptr<node<T>> right;
		/**
		 * pointer to the upper (parent) node. It cannot be unique as it can be possibly pointed
		 * by two different childern
		 */		
		node<T>* upper;

		/**
		 * standard constructor setting the value to zero and to nullptr all the pointers
		 */
		explicit node() noexcept : value{}, left{nullptr}, right{nullptr}, upper{nullptr} {} 

		/**
		 * custom constructor copying the value and setting only the upper pointer.
		 * Used whenever a left-value is given for the insertion in the tree
		 */
    explicit node(const T& v, node<T>* pu) noexcept : value{v}, left{nullptr}, right{nullptr}, upper{pu}{ 
      #ifdef __DEBUG_NODE
        std::cout << "CALL: custom ctor AP_node::node" << std::endl;
      #endif
		}

		/**
		 * custom move constructor, moving the value to the node and setting only the upper pointer.
		 * Used whenever a right-value is given for the insertion in the tree
		 */
		explicit node(T&& v, node<T>* pu) noexcept : value{std::move(v)}, left{nullptr}, right{nullptr}, upper{pu}{
	      #ifdef __DEBUG_NODE
          std::cout << "CALL: custom mctor AP_node::node" << std::endl;
          #endif
		}
	};
}
#endif 
