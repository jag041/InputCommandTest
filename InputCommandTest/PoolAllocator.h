#pragma once
// std includes
#include <string>

// my includes
#include "ErrorHandler.h"

template<typename T>
class PoolAllocator {

public:
	PoolAllocator(size_t num) : size(num), top(0) {
		{

			size_t data_size = sizeof(T);
			ptr_scl = data_size / sizeof(T**);

			// ensure that byte alignment will work
			assert(data_size % sizeof(void*) == 0); 

			// if data size is smaller than a void pointer, then the empty chunk list will overwrite its own data
			if (data_size < sizeof(void*)) {
				throw ErrorHandler("ERROR: custom heap allocator data size too small!!");
			}

			data = malloc(size * data_size);

			if (data == nullptr) {
				throw ErrorHandler("ERROR: data cannot be allocated to pool allocator!!");
			}

			// initialize linked list of empty spaces in heap
			for (size_t i = 0; i < num; ++i)
			{
				size_t pos = i + 1;
				if (pos == num)
				{
					// make final pointer null as sentinel
					((T**)data)[i * ptr_scl] = nullptr;
					break;
				}
				// store the address of the next T in the heap at the current address so empty chunks are stored in a linked list
				((T**)data)[i * ptr_scl] = &((T*)data)[pos];
#ifndef N_DEBUG
				std::cout << "T** address:    " << &((T**)data)[i * ptr_scl] << std::endl;
				std::cout << "T* address:     " << &((T*)data)[i] << std::endl;
				std::cout << "stored pointer: " << ((T**)data)[top * ptr_scl] << std::endl;
#endif				

			}

			//top = (T*)data;
			

		}
	}

	~PoolAllocator()
	{
		free(data);
	}

	size_t set_data(T* chunk) {
#ifndef N_DEBUG
		std::cout << "setting data" << std::endl;
		std::cout << "top = " << top << std::endl;
		std::cout << "data ref = " << data << std::endl;
		std::cout << "stored ptr = " << (((T**)data)[top * ptr_scl]) << std::endl;
#endif
		// get the address of the T* stored at top
		auto temp = ((T**)data)[top * ptr_scl];
#ifndef N_DEBUG
		std::cout << "temporary address " << temp << std::endl;
#endif
		// if it is null, throw an error and do not overwrite the data
		if (temp == nullptr)
		{
			throw ErrorHandler("Not enough data allocated in custom heap!!");
		}

		// else allocate the chunk to the top slot in the empty chunks list
#ifndef N_DEBUG
		std::cout << "data chunk ref = " << &((T*)data)[top] << std::endl;
#endif
		memcpy(((T*)data) + top, chunk, sizeof(T));
#ifndef N_DEBUG
		std::cout << "chunk allocated" << std::endl;
#endif
		//std::cout << ((T*)data)[top] << std::endl;

		// store top index into a return value
		size_t ret = top;

		// set top equal to the address of the value formerly stored in top minus the address of the raw data pointer
		top = size_t(temp - (T*)data);
#ifndef N_DEBUG
		std::cout << "new top: " << top << std::endl;
#endif
		// return the index to the just allocated data chunk
		return ret;
	}

	// return pointer to data stored at index
	T* get_data(size_t index) const {
#ifndef N_DEBUG
		std::cout << "data ref: " << data << std::endl;
		std::cout << "index data ref: " << ((T*)data) + index << std::endl;
#endif
		return ((T*)data) + index;
	}

	void delete_data(size_t index) {
		// store the address of top to a temporary variable
		T* temp = ((T*)data) + top;

		// set the data at the index to be equal to the address of top
		*(((T**)data) + index * sizeof(T) / sizeof(T*)) = temp;

		// set top equal to the index
		top = index;
#ifndef N_DEBUG
		std::cout << "new top: " << top << std::endl;
#endif

	}

	void clear_data() {
		for (size_t i = 0; i < size; ++i) {
			size_t pos = i + 1;
			if (pos == size)
			{
				// make final pointer null as sentinel
				((T**)data)[i * ptr_scl] = nullptr;
				break;
			}
			// store the address of the next T in the heap at the current address so empty chunks are stored in a linked list
			((T**)data)[i * ptr_scl] = ((T*)data) + pos;
		}
		top = 0;
	}

private:
	void* data{};
	int size{};
	size_t ptr_scl{};
	size_t top{};
};
