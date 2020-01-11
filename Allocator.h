#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <list>
#include "Queue.h"

//Класс списка
template <class T>
class List
{
private:
    struct element
    {
        T value;
        element* next;
        element* prev;
    };
    element* root;
    unsigned int size;
public:
    List()
    {
        root = nullptr;
        size = 0;
    }
    ~List()
    {
        if (root == nullptr)
            return;
        element* stat = root->next;
        while (stat)
        {
            stat = stat->next;
            delete stat->prev;
        }
        stat = root->prev;
        while (stat)
        {
            stat = stat->prev;
            delete stat->next;
        }
        delete root;
        root = nullptr;
    }
    unsigned int get_size() const
    {
        return size;
    }
    void push_front(const T &value)
    {
        element* stat = root;
        if (stat == nullptr)
        {
            stat = new element;
            stat->prev = nullptr;
            stat->next = nullptr;
            stat->value = value;
        }
        else
        {
            while (stat->next != nullptr)
                stat = stat->next;
            stat->next = new element;
            element* res = stat->next;
            res->next = nullptr;
            res->prev = stat;
            res->value = value;
        }
    }
    void push_back(const T &value)
    {
        element* stat = root;
        if (stat == nullptr)
        {
            stat = new element;
            stat->prev = nullptr;
            stat->next = nullptr;
            stat->value = value;
        }
        else
        {
            while (stat->prev != nullptr)
                stat = stat->prev;
            stat->prev = new element;
            element* res = stat->prev;
            res->prev = nullptr;
            res->next = stat;
            res->value = value;
        }
    }
    void pop_front()
    {
        if (root == nullptr)
            return;
        element* stat = root;
        while (stat->next != nullptr)
            stat = stat->next;
        element* res = stat;
        res->prev->next = nullptr;
        delete stat;
    }
    void pop_back()
    {
        if (root == nullptr)
            return;
        element* stat = root;
        while (stat->prev != nullptr)
            stat = stat->prev;
        element* res = stat;
        res->next->prev = nullptr;
        delete stat;
    }
    element* begin()
    {
        if (!root)
            return root;
        element* stat = root;
        while(stat->prev)
            stat = stat->prev;
        return stat;
    }
};


//Класс аллокатора//
namespace allocators
{
////Реализованный класс аллокатора

	template<class T, size_t ALLOC_SIZE>
	struct my_allocator {
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using is_always_equal = std::false_type;

		template<class U>
		struct rebind {
			using other = my_allocator<U, ALLOC_SIZE>;
		};

		my_allocator() :
			pool_begin(new char[ALLOC_SIZE]),
			pool_end(pool_begin + ALLOC_SIZE),
			pool_tail(pool_begin)
		{}

		my_allocator(const my_allocator&) = delete;
		my_allocator(my_allocator&&) = delete;

        ~my_allocator()
        {
			delete[] pool_begin;
		}

		T* allocate(std::size_t n);
		void deallocate(T* ptr, std::size_t n);

	private:
		char* pool_begin;
		char* pool_end;
		char* pool_tail;
        List<char*> free_blocks;
	};

	template<class T, size_t ALLOC_SIZE>
	T* my_allocator<T, ALLOC_SIZE>::allocate(std::size_t n) {
		if (n != 1) {
            throw std::logic_error("Error: Сan`t allocate arrays");
		}
        if (std::size_t(pool_end - pool_tail) < sizeof(T))
        {
            if (free_blocks.get_size())
            {
				auto it = free_blocks.begin();
				char* ptr = *it;
				free_blocks.pop_front();
				return reinterpret_cast<T*>(ptr);
			}
			throw std::bad_alloc();
		}
		T* result = reinterpret_cast<T*>(pool_tail);
		pool_tail += sizeof(T);
		return result;
	}

	template<class T, size_t ALLOC_SIZE>
	void my_allocator<T, ALLOC_SIZE>::deallocate(T* ptr, std::size_t n) {
        if (n != 1)
            throw std::logic_error("Error: Can`t allocate arrays, consequently can`t deallocate them too");
        if (ptr == nullptr)
			return;
		free_blocks.push_back(reinterpret_cast<char*>(ptr));
	}
};
