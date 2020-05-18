#ifndef __bst__
#define __bst__

#include "node.hpp"
#include "iterator.hpp"
#include <functional> //std::pair

namespace BST{
	//class templated on the values of the pair to be inserted in the tree K,V and on the 
	// comparison method which is in this case is chosen to be std::less

	template < class K, class V, class cmp=std::less<K> >
	class bst{
		
		using pair_type = typename std::pair<const K,V>;
		using node_type = typename AP_node::node<pair_type>;
		using iterator  = typename AP_it::__iterator<AP_node::node<pair_type>,pair_type>; 
		using const_iterator = typename AP_it::__iterator<AP_node::node<pair_type>,const pair_type>;
		
		private:
			
			cmp op;
			
			std::unique_ptr<node_type> head;

			
			node_type* __begin() const noexcept{

				if (!head) return nullptr;

				auto t = head.get();
				while(t->left){
					t=t->left.get();
				}
				
				return t;

			}

			node_type* __end() const noexcept {

				/*auto t = head.get();
				
				if(t == nullptr)
					return t;
				
				
				else{
					
					while(t){
						
						t=t->right.get();
					}

					return t;
				}*/
				return nullptr;
			
			}

			/*template<class OT>
  			bool insert_p(OT&& x, node_type* t, node_type* par){
  				std::cout<<"ciao_r_value_p"<<std::endl;
        		if( t == nullptr ){
    				t=new node_type{std::forward<OT>(x), par};
            		return true;
        		}
        		else if(op(x.first,t->value.first)) 
           			return insert_p( x, t->left.get(), t );
        		else if(!(op(x.first,t->value.first))) 
           			return insert_p( x, t->right.get(), t );
				else
           			//return std::pair<__iterator<OT>,bool>(__iterator<OT>{t},0);
				return false;
			}*/



  	
		public:

			bst() noexcept : op{}, head{nullptr} {}
			bst(bst&& ) noexcept = default;  
			bst& operator=(bst&& ) noexcept = default;

			bst(const bst& ); 
			bst& operator=(const bst& );

			//node* get_head(){return head.get();}

			
			template<class... Types>  // variadic templates
        	std::pair<iterator,bool> emplace(Types&&... args) {
            	return insert(pair_type{std::forward<Types>(args)...});
        	}

			

  			template<class OT>
		  	std::pair<iterator, bool> insert(OT&& x){

		  		auto t = head.get();
				
				while(t){
					//std::cout<<t->value.first<<std::endl;
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


			iterator begin() noexcept { return iterator{__begin()};}
			const_iterator begin() const noexcept{ return const_iterator{__begin()};}
			const_iterator cbegin() const noexcept{ return const_iterator{__begin()};}
			
			iterator end() noexcept	{ return iterator{__end()};}
			const_iterator end() const noexcept { return const_iterator{__end()};}
			const_iterator cend() const noexcept { return const_iterator{__end()};}

			
			iterator find(const K& x){
		
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

			const_iterator find(const K& x) const{

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

			void clear(){
				this->head.reset();
			}


			void erase(const K& x){
				//std::cout<<"ciao"<<std::endl;
				//std::cout<<find(x)->first<<std::endl;
				auto it_erase = find(x);
				auto node_to_erase = it_erase.current
				
				if( it_erase == end())
					std::cout<< "The key is not present."<<std::endl; 
				else{
					auto father = node_to_erase->upper;		
					
					//first case the node to remove has no child 
					if(node_to_erase->left == nullptr  && node_to_erase->right == nullptr){
						
						if(op(node_to_erase->value.first,father->value.first)){
							father->left.reset();
						} 
						else
							father->right.reset();
					}
					//second case the node has just right child
					else if(node_to_erase->left == nullptr && node_to_erase->right != nullptr){
						//and we set the upper pointer to nullptr
						node_to_erase->upper=nullptr;
						
						//we set the upper pointer of the right child to its "grandfather"
						auto child = it_node.current->right;
						child->upper=father;
						
						//let's find if the node to be eliminated was a left or right child
						
						//this case is when the node to be eliminated was a left child
						//and we reset the ownership 
						if(op(node_to_erase->value.first,father->value.first))
							father->left.reset(node_to_erase->right.release());
						
						//in this case was the right child
						else
							father->right.reset(node_to_erase->right.release());
					}

					//second case the node has just left child
					else if(node_to_erase->left != nullptr && node_to_erase->right == nullptr){
						//we set the upper pointer to nullptr
						node_to_erase->upper=nullptr;
						
						//we set the upper pointer of the right child to its "grandfather"
						auto child = node_to_erase->left;
						child->upper=father;
						
						//let's find if the node to be eliminated was a left or right child
						//this case is when the node to be eliminated was a left child
						//and we reset the ownership 
						if(op(node_to_erase->value.first,father->value.first)){
							father->left.reset(node_to_erase->left.release());
						} 
						//in this case was the right child
						else
							father->right.reset(node_to_erase->left.release());						
					}

					//node to eliminate has two children

					else{
						
						//find the successor 
						auto node_successor=(++it_node).current;

						//setting the upper pointer of the successor at the same value of
						//the upper pointer of the node to eliminate and we 
						//set to nullptr the upper one of the node to eliminate.
						node_successor->upper=node_to_erase->upper;
						node_to_erase->upper=nullptr;

						//reset the successor's children of the node to the node's children
						node_successor->right.reset(node_to_erase->right.release())
						node_successor->left.reset(node_to_erase->left.release())

					}


				}
			}







			template<class OT>
 			V& operator[](OT&& x){
 				return insert(pair_type{std::forward<OT>(x), V()}).first->second;
 			} 





			friend
			std::ostream& operator<<(std::ostream& os, const bst& x){
				
				for ( auto v : x ){
	    			std::cout << "Key = " << v.first << "\tValue = " << v.second  << std::endl;
				}

  				return os;
			}

  				
				/*for(auto i=x.begin();i != x.end();i++){
					std::cout<< i->first<<std::endl;
				}
				return os;*/
  				
 




				
};
#endif
}


