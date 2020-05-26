#ifndef __bst_cc__
#define __bst_cc__

#include "bst.hpp"

/*
 *COPY CONSTRUCTOR: deep copy of a given tree
 */
template < class K, class V, class cmp >
BST::bst<K,V,cmp>::bst(const BST::bst<K,V,cmp>& tree) : op{tree.op},
    head{ std::unique_ptr<AP_node::node<std::pair<const K,V>>>( new AP_node::node<std::pair<const K,V>>(tree.head.get()->value, nullptr) ) } {
  if (tree.head.get()->left)
    __copy(tree, tree.head.get()->left);
          
  if (tree.head.get()->right) 
    __copy(tree, tree.head.get()->right);
   
}

/*
 * single node copy helper
 */

template < class K, class V, class cmp >
void BST::bst<K,V,cmp>::__copy(const BST::bst<K,V,cmp>& tree, std::unique_ptr<AP_node::node<std::pair<const K, V>>>& a) {
  
  this->emplace(a.get()->value);

  if (a.get()->left)
    __copy(tree, a.get()->left);
            
  if (a.get()->right)
    __copy(tree, a.get()->right);
            
  return;
        }
//*******************************************************
//FIND: definition of find function;
//it simply navigates from the head using the op operator and 
//stopping if the key is found.
template < class K, class V, class cmp >
AP_it::__iterator<AP_node::node<std::pair<const K,V>>,std::pair<const K,V>> BST::bst<K,V,cmp>::find(const K& x){
    
  auto t = head.get();
  while(t){
    if(op(x,t->value.first)){
      if(t->left)
        t=t->left.get();
      else 
        return end();
    }
    else if(op(t->value.first, x)){
      if(t->right)
        t=t->right.get();
      else 
        return end();
    }
    else 
      return iterator{t}; 
  }
  return iterator{nullptr};
}

//*******************************************************
//FIND: returning a const iterator
template < class K, class V, class cmp >
AP_it::__iterator<AP_node::node<std::pair<const K,V>>,const std::pair<const K,V>> BST::bst<K,V,cmp>::find(const K& x) const{

  auto t = head.get();
  while(t){
    if(op(x,t->value.first)){
      if(t->left)
        t=t->left.get();
      else
        return cend();
    }
    else if(op(t->value.first,x)){
      if(t->right)
        t=t->right.get();
      else
        return cend();
    }
    else
      return const_iterator{t}; 
    }
  return const_iterator{nullptr};
}

//*******************************************************
//BALANCE: function balancing the bst. 
//It calls iteratively the helping function
//sortedArrayToBst for the re-insertion of the nodes. 
//First, it builds a vector having the ordered pairs of the BST
template < class K, class V, class cmp >
void BST::bst<K,V,cmp>::balance(){
  
  std::vector<pair_type> app;
  int tmp=0;
  for(auto i=cbegin(); i != cend(); ++i){
    app.push_back(*i);
    tmp++;
  }

  bst balanced_tree{};
  sortedArrayToBST(app,0,app.size()-1,balanced_tree);
  clear();
  head.reset(balanced_tree.head.release());
  return;
}

//*******************************************************
//SORTEDARRAYTOBST: function which find the median of a ordered-vector
//and it calls insert with the key=V[median]
//then it calls iteratively itself on the left side 
//and right side of the median   
template < class K, class V, class cmp >
void BST::bst<K,V,cmp>::sortedArrayToBST(std::vector<std::pair<const K,V>> data,int start, int end, BST::bst<K,V,cmp> &balanced_tree){  
  /* Base Case */
  if (start > end)  
    return;  
  /* Get the middle element and make it root */
  int mid = (start + end)/2; 
  
  balanced_tree.insert(data[mid]);  

  /* Recursively construct the left subtree  
  and make it left child of root */
  sortedArrayToBST(data, start, mid - 1,balanced_tree);  

 /* Recursively construct the right subtree  
  and make it right child of root */
  sortedArrayToBST(data, mid + 1, end,balanced_tree);  

  return;  
}  

//*******************************************************
//ERASE: Given a key it finds if present and 
//in such case it removes the node  
//and it repairs the tree without that node
template < class K, class V, class cmp >
void BST::bst<K,V,cmp>::erase(const K& x){

  auto it_erase = find(x);
  auto node_to_erase = it_erase.current;

  if( it_erase == end()){
    std::cout<< "The key is not present."<<std::endl; 
    return;
  }

  else{

    //case 1) node_to_erase=head
    if(node_to_erase==head.get())
      erase_head();
    
    //case 2) node_to_erase is generic
    else 
      erase_generic(it_erase);

    return;
  }
  }

//*******************************************************
//ERASEGENERIC: function called by erase which erases a generic (not the one poitned by the head) node with a given key.
//the implementation is explained step by step within the function according to the all possibilities
template < class K, class V, class cmp >
void BST::bst<K,V,cmp>::erase_generic(AP_it::__iterator<AP_node::node<std::pair<const K,V>>,std::pair<const K,V>> it_erase){

  //using pair_type = typename std::pair<const K,V>;
  //using iterator  = typename AP_it::__iterator<AP_node::node<pair_type>,pair_type>; 

  auto node_to_erase = it_erase.current;
  
  auto father = node_to_erase->upper;   
      
  //node_to erase has no child reset to nullptr the father's pointer
  if(node_to_erase->left == nullptr  && node_to_erase->right == nullptr){
      
      node_to_erase->upper=nullptr;

      if(op(node_to_erase->value.first,father->value.first))
        father->left.reset();
       
      else
        father->right.reset();
  }
  
    
  //second case the node has just right child
  else if(node_to_erase->left.get() == nullptr && node_to_erase->right.get() != nullptr){
      
      //we set the upper pointer of the right child to its "grandfather"
      (node_to_erase->right)->upper=father;
      
      //let's find if the node to be eliminated was a left or right child
      if(op(node_to_erase->value.first,father->value.first))
        //this case is when the node to be eliminated was a left child
        //and we reset the ownership 
        father->left.reset(node_to_erase->right.release());
      
      //in this case was the right child
      else
        father->right.reset(node_to_erase->right.release());

      //and we set the upper pointer to nullptr
      node_to_erase->upper=nullptr;
      
  }

    //second case the node has just left child
  else if(node_to_erase->left.get() != nullptr && node_to_erase->right.get() == nullptr){
      
      //we set the upper pointer of the right child to its "grandfather"
      (node_to_erase->left)->upper=father;
      
      //let's find if the node to be eliminated was a left or right child 
      if(op(node_to_erase->value.first,father->value.first))
        
        father->left.reset(node_to_erase->left.release());
      
      //in this case was the right child
      else
        father->right.reset(node_to_erase->left.release());   

      //we set the upper pointer to nullptr
      node_to_erase->upper=nullptr;
      
  }

  //node to eliminate has two children

  else{
    
    //find the successor which will be on the right of the node_to_delete
    auto node_successor=(++it_erase).current;
   
    //reset the father of node's left child to node successor
    (node_to_erase->left)->upper=node_successor;
    
    //reset the successor's left child to the left child of the node to erase
    //we know for sure that the node_successor->left=nullptr
    //otherwise wouldn't be the successor
    node_successor->left.reset(node_to_erase->left.release());

    //case 1) successor is the right child of the node to delete
    if(node_successor==node_to_erase->right.get()){
      
      //set the node_successor_father to father of the node to erase
      node_successor->upper=father;
      node_to_erase->upper=nullptr;

      //set the child of the father to node successor
      if(op(node_to_erase->value.first,father->value.first))
        //this case is when the node to be eliminated was a left child
        //and we reset the ownership
        father->left.reset(node_to_erase->right.release());

      //in this case was the right child
      else
        father->right.reset(node_to_erase->right.release());  

    }
    //case 2) general case successor is not the right child of the node to delete
    else{
      
      //if the successor has a child (which has to be a right child)
      if (node_successor->right) {
        
        //we set the father of the right child to the father of the node successor
        //and we set as left child of the father this node 
        //for sure node_successor was a left child otherwise we are in the former case 
        (node_successor->right)->upper = node_successor->upper;
        (node_successor->upper)->left.reset(node_successor->right.release());
      
      }

      //set the right child of the node as the right child of the node_successor
       
      node_successor->right.reset(node_to_erase->right.release());
      (node_successor->right)->upper=node_successor;
                
      //set the father of the node successor to be the father of the node_to_erase
      node_successor->upper=father;
      node_to_erase->upper=nullptr;

  
      //set the child of the father to node successor
      if(op(node_to_erase->value.first,father->value.first))

        //this case is when the node to be eliminated was a left child
        //and we reset the ownership
        father->left.reset(node_to_erase->right.release());
       
      //in this case was the right child
      else
        father->right.reset(node_to_erase->right.release());  

    } 
  }
  return;
}

//*******************************************************
//ERASE_HEAD: erase function for the node pointed by the head
//the implementation is explained step by step within the function according to the all possibilities
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

//*******************************************************
//INSERT: it creates a node with values passed in the argument if the key is
//not already present and it returns the iterator pointing to the new node andd a bool=true
//otherwise it returns the iterator pointing to the already present node and a bool=false
template < class K, class V, class cmp >
template<class OT>
std::pair< AP_it::__iterator<AP_node::node<std::pair<const K,V>>, std::pair<const K,V> >, bool> BST::bst<K,V,cmp>::insert(OT&& x){

  auto t = head.get();

  while(t){
      if(op(x.first,t->value.first)){
        if(t->left)
          t=t->left.get();
        else{
          
          t->left.reset(new node_type {std::forward<OT>(x),t}); 
          return std::make_pair(iterator{t->left.get()},true) ;
        }
      }         
      else if(op(t->value.first,x.first)){
        if(t->right)
          t=t->right.get();
        else{
          t->right.reset(new node_type{std::forward<OT>(x),t});
          return std::make_pair(iterator{t->right.get()},true) ;
        }
      }
      else return std::make_pair(iterator{t},false) ;
    }

    head.reset(new node_type{std::forward<OT>(x), nullptr}) ;
    return std::make_pair(iterator{head.get()},true) ;

}  

#endif