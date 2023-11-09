# Velopra Engine

The Velopra Engine is a lightweight, high-performance game engine designed for the development of both 2D and 3D games. It offers a powerful suite of tools and a robust core for mathematics and memory management that underpin the graphics and physics systems necessary for modern game development.

## Core Features

- Vector2 and Vector3 structures for 2D/3D mathematical computations.
- Matrix4 structure for affine transformations and projections.
- Inline arithmetic operations for vectors and matrices for performance-critical applications.
- Basic memory management utilities for dynamic allocation and deallocation.
- Integrated logging system for error reporting and debugging.

## Getting Started

### Prerequisites

Before you begin, ensure you have the following installed:
- A C++17 compliant compiler (e.g., GCC, Clang, MSVC)
- [CMake](https://cmake.org/download/) for the build process management
- A package manager like [vcpkg](https://github.com/microsoft/vcpkg) (optional, for managing dependencies)

### Dependencies

The Velopra Engine uses `spdlog` for logging. If you are using vcpkg, you can install `spdlog` as follows:

```bash
vcpkg install spdlog
```

[TODO]
If you're not using a package manager, make sure to include the spdlog library in your project or add the necessary submodules if you're using Git.

### Building the Project

To build the Velopra Engine, follow these steps:

```bash
git clone https://github.com/AlexHikari/VelopraEngine.git
cd VelopraEngine
mkdir build
cd build
cmake ..
make
```

### Usage

To use the Velopra Engine in your project, include the core header files in your source and link against the Velopra Engine library. Here is a simple example:

```cpp
#include "VelopraEngine/Core/Math.h"

int main() {
    using namespace VelopraEngine::Core;
    
    Vector3 position(1.0f, 2.0f, 3.0f);
    Vector3 velocity(0.1f, 0.2f, 0.3f);
    float deltaTime = 1.0f / 60.0f;
    
    // Update position using Euler integration
    position = position + velocity * deltaTime;
    
    return 0;
}
```

### Contributing

Right now contributions are closed but will be opened in the future as the engine expands!

### License

Velopra Engine is released under the MIT License. See the LICENSE file for more details.

### Distribution

[TODO] For users who prefer not to build from source, we provide pre-compiled binaries for each release on the 