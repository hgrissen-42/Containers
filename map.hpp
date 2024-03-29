
#pragma once

# include <iostream>
# include "tree.hpp"
# include "Bi_Iterator.hpp"
# include "ReverseIterator.hpp"
# include "Vector.hpp"

namespace ft {


	template < class Key,                                     // Map::key_type
	class T,                                                 // Map::mapped_type
	class Compare = std::less<Key>,                         // Map::key_compare
	class Alloc = std::allocator<pair< const Key,T> > >     // Map::allocator_type
	class Map {

		public:

			typedef Key                                     key_type;
			typedef T                                       mapped_type;
			typedef pair<const key_type, mapped_type>       value_type;
			typedef Compare                                 key_compare;
			

			class value_compare : public std::binary_function<value_type, value_type, bool> {
				protected:
					Compare __comp;
				public:
					value_compare(const Compare &c) : __comp(c) { }
					value_compare(){};
					bool operator()(const value_type &lhs, const value_type &rhs) const { return(__comp(lhs.first, rhs.first)); }
				// public:
				//     value_compare( Compare c ) : __comp(c) {}
				//     bool operator()( const value_type& lhs, const value_type& rhs ) const { return __comp(lhs.first, rhs.first); }
			};
			typedef Alloc                                                   allocator_type;
			typedef value_type&                                             reference;
			typedef const value_type&                                       const_reference;
			typedef value_type*                                             pointer;
			typedef const value_type*                                       const_pointer;
			typedef mapiterator< Key, T, key_compare, Alloc>                iterator;
			typedef mapiterator< Key, T, key_compare, Alloc>                const_iterator;
			typedef ft::reverse_iterator<iterator>                          reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type     difference_type;
			typedef size_t                                                  size_type;
			typedef node<key_type, mapped_type>                             node;

			size_type                                       _size;
			Alloc                                           _allocator;
			node*                                           _root;
			AVL<key_type, mapped_type, key_compare, Alloc>  _tree;
			Compare                                         _cmp;

			explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
			{
				_size = 0;
				_root = nullptr;
				_cmp = comp;
				_allocator = alloc;
			}

			template <class InputIterator>
			Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator())
			{
				_size = 0;
				_root = nullptr;
				_cmp = comp;
				_allocator = alloc;
				for (InputIterator it = first; it != last; it++)
				{
					_root = _tree.Insert(_root, nullptr, *it);
					_size++;
				}
			}

			Map (const Map& x)
			{
				_root = nullptr;
				_size = 0;
				*this = x;
				// std::cout << x.size() << std::endl;
				//
			}

			~Map() { _root = _tree.DeleteAll(_root); }

			Map& operator= (const Map& x)
			{
				if (this != &x)
				{
					_tree.DeleteAll(_root);
					_root = nullptr;
					_size = 0;
					for (iterator it = x.begin(); it != x.end(); it++)
					{
						_root = _tree.Insert(_root, nullptr, *it);
						_size++;
					}
				}
				return *this;
			}

			/*   Iterators: */

			iterator begin()                        { return iterator(_root, _tree.treeMinimum(_root)); }
			const_iterator begin() const            { return iterator(_root, _tree.treeMinimum(_root)); }
			iterator end()                          { return iterator(_root, nullptr); }
			const_iterator end() const              { return iterator(_root, nullptr); }
			reverse_iterator rbegin()               { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin() const   { return (reverse_iterator(end())); }
			reverse_iterator rend()                 { return (reverse_iterator(begin())); }
			const_reverse_iterator rend() const     { return (reverse_iterator(iterator(begin()))); }

			/* Capacity */

			bool empty() const              { return _size == 0; }
			size_type size() const          { return _size; }
			size_type max_size() const      {return _allocator.max_size(); }

			/* Element access */

			mapped_type& operator[] (const key_type& k)
			{
				iterator it = find(k);
				if (it == end()) {
					_root = _tree.Insert(_root, nullptr, ft::make_pair<  const key_type, mapped_type>(k, mapped_type()));
					_size++;
					return find(k)->second;
				}
				return it->second;
			}

			mapped_type& at (const key_type& k) 			{ iterator it = find(k);  return it->second; }
			const mapped_type& at (const key_type& k) const { iterator it = find(k);  return it->second; }

			/* Modifiers */

			pair<iterator,bool> insert (const value_type& val)
			{
				iterator it = find(val.first); 

				if (it != end()) { return pair<iterator, bool>(it, false); }

				_root = _tree.Insert(_root, nullptr, val);
				_size++;
				return pair<iterator, bool>(begin(), true);
			}

			iterator insert (iterator position, const value_type& val) {

				iterator it = find(val.first); 

				if (it != end()) { return position; }

				_root = _tree.Insert(_root, nullptr, val);
				_size++;
				return begin();
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {

				
				for (InputIterator it = first; it != last; it++)
				{
					_root = _tree.Insert(_root , nullptr, *it);
					_size++;
				}
			}


			size_type erase (const key_type& k) {
				int found = 1;
				_root = _tree.Delete(_root, ft::make_pair<Key, T>(k, T()), &found);
				if (_size > 0)
					_size -= 1;
				return found;

			}
			void erase (iterator position) {
			
				int found = 1;
				if (position != end())  {
					_root = _tree.Delete(_root, *position, &found);
					_size -= 1;
				}
			}



			void erase (iterator first, iterator last) {
			

				Vector<Key> tmp;

				for (iterator it = first; it != last; it++) {

					tmp.push_back(first->first);
					// first++;
				}
				for (size_type i = 0; i < tmp.size(); i++) { erase(tmp[i]); }
			}

			void swap (Map& x)
			{
				std::swap(_root, x._root);
				std::swap(_size, x._size);
				std::swap(_allocator, x._allocator);
				std::swap(_cmp, x._cmp);
			}

			void clear() { _size = 0; _root = nullptr;}//_tree->DeleteALL(_root);

			/* Observers */

			key_compare key_comp() const		{ return _cmp;}
			value_compare value_comp() const	{ return value_compare(_cmp); }

			/* Operations */

			iterator find (const key_type& k) 
			{
				node * found = _tree.find(_root, k);
				if (found != nullptr)
					return iterator(_root, found);
				return end();
			}
			const_iterator find (const key_type& k) const
			{
				node * found = _tree.find(_root, k);
				if (found != nullptr)
					return const_iterator(_root, found);
				return end();
			}
			
			size_type count (const key_type& k) const
			{
				iterator it = find(k);
				if (it == end())
					return 0;
				return 1;
			}

			iterator lower_bound (const key_type& k)										{ return iterator(_root, _tree.lowerBound(_root, k));}
			const_iterator lower_bound (const key_type& k) const							{ return const_iterator(_root, _tree.lowerBound(_root, k));}
			iterator upper_bound (const key_type& k)										{ return iterator(_root, _tree.upperBound(_root, k));}
			const_iterator upper_bound (const key_type& k) const							{ return const_iterator(_root, _tree.upperBound(_root, k));}
			pair<const_iterator, const_iterator> equal_range (const key_type& k) const 		{ return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));}
			pair<iterator, iterator> equal_range (const key_type& k) 						{ return pair<iterator, iterator>(lower_bound(k), upper_bound(k));}

			/* Allocator */

			allocator_type get_allocator() const { return _allocator; }

		};


		template <class Key, class T, class Compare, class Alloc>
		bool operator== ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator!= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator<  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator<= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{
			return !( rhs < lhs );
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator>  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator>= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y)
		{
			std::swap(x._root, y._root);
			std::swap(x._size, y._size);
			std::swap(x._allocator, y._allocator);
			std::swap(x._cmp, y._cmp);
		}
}
