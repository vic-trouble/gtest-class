#pragma once

#include <string>
#include <vector>

namespace Recent
{

	using ru_list = std::vector<std::string>;

	/**
	Develop a recently-used-list class to hold strings uniquely in Last-In-First-Out order.

	- The most recently added item is first, the least recently added item is last.
	- Items can be looked up by index, which counts from zero.
	- Items in the list are unique, so duplicate insertions are moved rather than added.
	- A recently-used-list is initially empty.

	Optional extras:
	- Null insertions (empty strings) are not allowed.
	- A bounded capacity can be specified, so there is an upper limit to the number of items contained, with the least recently added items dropped on overflow.
	*/
	class RUList
	{
	public:
		RUList() = default;
		explicit RUList(size_t capacity);

		void push(const std::string &item);

		size_t size() const;
		const std::string &operator[](size_t index) const;

	private:
		std::vector<std::string> storage_;
		size_t capacity_ = 0;
	};

}