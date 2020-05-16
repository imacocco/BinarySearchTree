#ifndef __bst__
#define __bst__

#include "node.hpp"
//#include "iterator.hpp"
#include <functional> //std::pair

namespace BST{
	//class templated on the values of the pair to be inserted in the tree K,V and on the 
	// comparison method which is in this case is chosen to be std::less

	template < class K, class V, class cmp=std::less<K> >
	class bst{
		
		using pair_type = typename std::pair<const K,V>;
		using node_type = typename AP_node::node<pair_type>;
		//using iterator = typename APutils::__iterator<node_type,  pair_type>;
		//using const_iterator = typename APutils::__iterator<node_type, const pair_type>;

		private:
			
			cmp op;
			
			std::unique_ptr<node_type> head;

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

			/*
			template<class... Types>  // variadic templates
        	std::pair<iterator,bool> emplace(Types&&... args) {
            	return insert(pair_type{std::forward<Types>(args)...});
        	}*/

	

  			template<class OT>
		  	bool insert(OT&& x){
		  		std::cout<<"ciao_r_value_p"<<std::endl;

		  		auto t = head.get();
		  		std::cout<<"ciao_r_value_p"<<std::endl;
				while(t){
		        	if(op(x.first,t->value.first)){
		        		if(t->left)
		        			t=t->left.get();
		        		else{
		        			t->left.reset(new node_type {std::forward<OT>(x),t});
		        			return true;
		        		}
		        	}     		
		        	else if(op(t->value.first,x.first)){
		        		if(t->right)
		        			t=t->right.get();
		        		else{
		        			t->right.reset(new node_type{std::forward<OT>(x),t});
		        			return true;
		        		}
		        	}
		        	else return false;
		        }

		        head.reset(new node_type{std::move(x), nullptr});
            	return true;

		    }  



    /*
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
	*/

	
	/*
	template<class OT>
	bool insert(OT&& x){
		std::cout<<"ciao_r_value"<<std::endl;
		return insert_p(x, head.get() , nullptr);
	} */
	/*
	bool insert(const pair_type& x){
		std::cout<<"ciao_l_value"<<std::endl;
		return insert_p(x, head.get() , nullptr);
	}*/
	/*
	friend std::ostream& operator<<(std::ostream&, const bst<K,V,cmp>&);

	iterator begin() noexcept { return iterator{head.get()}; }
	iterator end() { return iterator{nullptr}; }

	const_iterator begin() const { return const_iterator{head.get()}; }
	const_iterator end() const { return const_iterator{nullptr}; }

	const_iterator cbegin() const { return const_iterator{head.get()}; }
	const_iterator cend() const { return const_iterator{nullptr}; }
	*/
	
	


};
#endif
}


