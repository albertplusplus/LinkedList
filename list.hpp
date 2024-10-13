#include <memory>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <cstddef>

namespace bear {
	template <typename T>
	class linkedlist
	{
	public:

		using value_type = T;
		using size_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		class iterator;

	private:
		struct node_type
		{
			value_type data;
			std::unique_ptr<node_type> next;
			explicit node_type(std::unique_ptr<node_type>&& next, value_type data)
				: next{ std::move(next) }, data{ data } {}
		};

		std::unique_ptr<node_type> head = nullptr;
		size_type length = 0;

	public:
		linkedlist() = default;
		//linkedlist(const linkedlist& other);
		//linkedlist(linkedlist&& other) noexcept;
		linkedlist(std::initializer_list<T> il);
		template <typename Iter>
		linkedlist(Iter first, Iter last);

		~linkedlist() {}

		void push_front(const T& value);
		//	void push_front(T&& value);
		void pop_front();
		void print_nodes();
		iterator begin() noexcept;
		iterator end() noexcept;
		size_type size();

	};

	template <typename T>
	class linkedlist<T>::iterator
	{
		node_type* node = nullptr;

	public:
		friend class linkedlist<T>;

		using value_type = typename linkedlist<T>::value_type;
		using pointer = typename linkedlist<T>::pointer;
		using reference = typename linkedlist<T>::reference;
		iterator() = default;
		iterator(node_type* node) noexcept;
		iterator& operator++();
		iterator operator++(int);
		reference operator*() const;
		pointer operator->() const;
		bool operator==(iterator other) const noexcept;
		bool operator!=(iterator other) const noexcept;
	};



	template <typename T>
	void
		linkedlist<T>::push_front(const T& val)
	{
		head = std::make_unique<node_type>(std::move(head), val);
		++length;
	}

	template <typename T>
	typename linkedlist<T>::size_type
		linkedlist<T>::size()
	{
		return length;
	}

	template <typename T>
	void
		linkedlist<T>::pop_front()
	{
		if (head)
		{
			head = std::move(head->next);
			--length;
		}
	}

	template <typename T>
	template <typename Iter>
	linkedlist<T>::linkedlist(Iter first, Iter last)
	{
		//
	}

	template <typename T>
	void
		linkedlist<T>::print_nodes()
	{
		auto curr = head.get();
		while (curr)
		{
			std::cout << curr->data << "\n";
			curr = curr->next.get();
		}
	}

	template <typename T>
	typename linkedlist<T>::iterator
		linkedlist<T>::begin() noexcept
	{
		return { head.get() };
	}

	template <typename T>
	typename linkedlist<T>::iterator
		linkedlist<T>::end() noexcept
	{
		return { };
	}

	template <typename T>
	linkedlist<T>::iterator::iterator(node_type* node) noexcept : node{ node } {}

	template <typename T>
	typename linkedlist<T>::iterator&
		linkedlist<T>::iterator::operator++()
	{
		node = node->next.get();
		return *this;
	}

	template <typename T>
	typename linkedlist<T>::iterator
		linkedlist<T>::iterator::operator++(int)
	{
		auto copy = *this;
		++*this;
		return copy;
	}

	template<typename T>
	typename linkedlist<T>::iterator::reference linkedlist<T>::iterator::operator*() const
	{
		return node->data;
	}

	template<typename T>
	typename linkedlist<T>::iterator::pointer linkedlist<T>::iterator::operator->() const
	{
		return &node->data;
	}

	template <typename T>
	inline bool
		linkedlist<T>::iterator::operator==(iterator other) const noexcept
	{
		return node == other.node;
	}

	template <typename T>
	inline bool
		linkedlist<T>::iterator::operator!=(iterator other) const noexcept
	{
		return !(*this == other);
	}
}
