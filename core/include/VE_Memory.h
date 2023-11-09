#ifndef HISIDIAN_ENGINE_CORE_MEMORY_H
#define HISIDIAN_ENGINE_CORE_MEMORY_H

#include <cstddef>

namespace VelopraEngine {
	namespace Core {

		// Allocates a block of memory of the given size.
		void* Allocate(std::size_t size);

		// Deallocates a block of memory pointed to by ptr.
		void Deallocate(void* ptr);

		// You might later add custom allocators for different purposes, e.g.,
		// void* AllocateAligned(std::size_t size, std::size_t alignment);
		// void DeallocateAligned(void* ptr);

	} // namespace Core
} // namespace VelopraEngine

#endif // HISIDIAN_ENGINE_CORE_MEMORY_H