#pragma once

// std includes
#include <assert.h>

// my includes
#include "ErrorHandler.h"

class StackAllocator
{
public:
	StackAllocator(size_t num) : size(num), top(0) {

		data = malloc(size);

	}

	~StackAllocator() {

		free(data);

	}

	size_t set_data(size_t num_bytes, void* source) {
	
		assert(top + num_bytes <= size);

		size_t ret = top;
		top += num_bytes;

		memcpy(((char*)data) + ret, source, num_bytes);

		return ret;
	}

	void* get_data(size_t index) {
		
		return ((char*)data) + index;

	}

	void delete_data(size_t index) {
		assert(index < size && index < top);
		top = index;
	}

	void clear_data() {
	
		top = 0;
	
	}

private:
	void* data{};
	int size{};
	size_t top{};
};

