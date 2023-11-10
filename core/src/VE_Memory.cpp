#include "VE_Memory.h"

#include <cstdlib>

namespace VelopraEngine {
	namespace Core {

		void* Allocate(size_t size) {
			// Use operator new to allocate memory.
			// This does not call constructors for non-POD types.
			return ::operator new(size);
		}

		void Deallocate(void* ptr) {
			// Use operator delete to deallocate memory.
			// This does not call destructors for non-POD types.
			::operator delete(ptr);
		}

		void* AllocateAligned(std::size_t size, std::size_t alignment) {
			#if defined(_MSC_VER)
				return _aligned_malloc(size, alignment);
			#else
				void* ptr = nullptr;
				if (posix_memalign(&ptr, alignment, size) != 0) {
					ptr = nullptr;
				}
			return ptr;
			#endif
		}

		void DeallocateAligned(void* ptr) {
			#if defined(_MSC_VER)
				_aligned_free(ptr);
			#else
				free(ptr);
			#endif
		}

		// Future custom memory management functions can be implemented here.

		/*
		As the engine grows and you need more sophisticated memory management, 
		you may implement custom allocators. For example, you might want a pool allocator for small fixed-size objects or a stack allocator for temporary objects. 
		The custom allocator functions can be added to the Memory namespace and used throughout your engine.
		*/

	} // namespace Core
} // namespace VelopraEngine
