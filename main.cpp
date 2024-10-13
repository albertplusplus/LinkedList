#include <iostream>
#include "list.hpp"

int main()
{
	bear::linkedlist<int> int_lst;
	int_lst.push_front(6);
	int_lst.push_front(24);
	int_lst.push_front(65);
	int_lst.push_front(43);
	
	for (auto v : int_lst)
		std::cout << v << "\n";
	std::cout << "\n";
	bear::linkedlist<std::string> str_lst;
	str_lst.push_front(std::string{ "World!" });
	str_lst.push_front(std::string{ "Hello" });
	for (auto v : str_lst)
		std::cout << v << " ";
	std::cout << "\n\n";
	return 0;
}