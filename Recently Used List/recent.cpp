#include "recent.h"

Recent::RUList::RUList(size_t capacity)
	: capacity_(capacity)
{
}

void Recent::RUList::push(const std::string &item)
{
	auto it = std::find(storage_.begin(), storage_.end(), item);
	if (it != storage_.end())
		storage_.erase(it);

	storage_.insert(storage_.begin(), item);
	if (capacity_ && storage_.size() > capacity_)
		storage_.resize(capacity_);
}

size_t Recent::RUList::size() const
{
	return storage_.size();
}

const std::string & Recent::RUList::operator[](size_t index) const
{
	return storage_[index];
}
