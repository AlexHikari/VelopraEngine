#ifndef VELOPRA_ENGINE_CORE_MEMORY_H
#define VELOPRA_ENGINE_CORE_MEMORY_H

#include <cstddef>

namespace VelopraEngine {
	namespace Core {

		// Allocates a block of memory of the given size.
		void* Allocate(std::size_t size);

		// Deallocates a block of memory pointed to by ptr.
		void Deallocate(void* ptr);

		void* AllocateAligned(std::size_t size, std::size_t alignment);

		void DeallocateAligned(void* ptr);

	} // namespace Core
} // namespace VelopraEngine

#endif // VELOPRA_ENGINE_CORE_MEMORY_H