#include "bst.hpp"

template < class K, class V, class cmp >
void BST::bst<K,V,cmp>::erase_head(){

  using pair_type = typename std::pair<const K,V>;
  using iterator  = typename AP_it::__iterator<AP_node::node<pair_type>,pair_type>; 


  //case head is the only node:
  if(head.get()->right==nullptr && head.get()->left==nullptr)
    head.reset();
  
  //the node has children
  else{

    //head has just left child
    if(head.get()->right==nullptr){
      (head.get()->left)->upper=nullptr;
      head.reset(head.get()->left.release());
    }

    //head has right child 
    else{

      iterator H{head.get()};

      auto node_successor = (++H).current;
      //reset the father of node's left child to node successor
      if(head.get()->left.get()){
        (head.get()->left)->upper=node_successor;
    
        //reset the successor's left child to the left child of the node to erase
        //we know for sure that the node_successor->left=nullptr
        //otherwise wouldn't be the successor
        node_successor->left.reset(head.get()->left.release());
      }

      //case 1) successor is the right child of the head
      if(node_successor==head.get()->right.get()){
        head.reset(head.get()->right.release());
        node_successor->upper=nullptr;
      }
      //case 2) general case successor is not the right child of the head
      else{
        
        //if the successor has a child (which has to be a right child)
        if (node_successor->right.get()) {
          
          //we set the father of the right child to the father of the node successor
          //and we set as left child of the father this node 
          //for sure node_successor was a left child otherwise we are in the former case 
          (node_successor->right)->upper = node_successor->upper;
          (node_successor->upper)->left.reset(node_successor->right.release());
        
        }

        //set the right child of the node as the right child of the node_successor 
        node_successor->right.reset(head.get()->right.release());
        head.reset(node_successor);
        (node_successor->right)->upper=node_successor;
                  
        //set the father of the node successor to be the father of the node_to_erase
        node_successor->upper=nullptr;
        //set the child of the father to node successor
        
      } 
    }               
  }
  return;
}