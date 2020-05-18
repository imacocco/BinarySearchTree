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

			
			node_type* __begin() noexcept {

				auto t = head.get();
				
				while(t){
					
					t=t->left.get();
				}

				return t;

			}

			node_type* __end() noexcept{

				auto t = head.get();
				
				if(t == nullptr)
					return t;
				
				
				else{
					
					while(t){
						
						t=t->right.get();
					}

					return t->right.get();
				}
			
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

			friend
			std::ostream& operator<<(std::ostream& os, const bst& x){
				for(auto i= x.begin(); i != x.end(); ++i){
					std::cout AP_node::<< *i << std::endl;
				}
				return os;
			}
};
#endif
}


