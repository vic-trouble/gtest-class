#pragma once

#include <string>
#include <vector>

namespace Recent
{

	class RUList
	{
	public:
		RUList() = default;
		explicit RUList(size_t capacity);

		void push(const std::string &item);

		size_t size() const;
		const std::string &operator[](size_t index) const;
	};

}