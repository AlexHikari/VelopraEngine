#include "VE_Memory.h"

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

		// Future custom memory management functions can be implemented here.

		/*
		As the engine grows and you need more sophisticated memory management, 
		you may implement custom allocators. For example, you might want a pool allocator for small fixed-size objects or a stack allocator for temporary objects. 
		The custom allocator functions can be added to the Memory namespace and used throughout your engine.
		*/

	} // namespace Core
} // namespace VelopraEngine
