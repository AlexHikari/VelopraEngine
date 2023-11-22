#ifndef VE_CORE_MEMORY_H
#define VE_CORE_MEMORY_H

#include "VE_CoreAPI.h"
#include <cstddef>

namespace velopraEngine {
namespace core {

// Allocates a block of memory of the given size.
VELOPRACORE_API void *Allocate(std::size_t size);

// Deallocates a block of memory pointed to by ptr.
VELOPRACORE_API void Deallocate(void *ptr);

VELOPRACORE_API void *AllocateAligned(std::size_t size, std::size_t alignment);

VELOPRACORE_API void DeallocateAligned(void *ptr);

} // namespace core
} // namespace velopraEngine

#endif // VE_CORE_MEMORY_H