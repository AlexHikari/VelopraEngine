# Velopra Engine

The Velopra Engine is a versatile, high-performance game engine designed for developing both 2D and 3D games. It offers a comprehensive suite of tools and a robust framework, including mathematics, memory management, rendering capabilities, and more, crucial for contemporary game development.

## Core Features

- **Vector2 and Vector3 structures** for efficient 2D/3D mathematical computations.
- **Matrix4 structure** for handling affine transformations and projections.
- **Optimized arithmetic operations** for vectors and matrices, catering to performance-critical applications.
- **Advanced memory management utilities** for dynamic allocation, deallocation, and aligned memory operations.
- **Integrated logging system** for streamlined error reporting and debugging.
- **Powerful OpenGL-based rendering module**, supporting shader management, mesh processing, texture handling, and more.
- **Shader class** for efficient loading, compiling, and utilizing GLSL shaders.
- **Mesh class** dedicated to managing vertex data and rendering meshes.
- **Basic model class** for handling 3D models and their meshes, with ongoing enhancements for full implementation.

## Core Components

### Core Module (VelopraCore)
- Central part of the engine, handling core functionalities.
- Singleton Core class for managing the engine's main operations.
- Manages event queue and event bus for event handling and dispatching.
- Implements VE_Logger for logging, utilizing spdlog for efficient logging.
- Handles dynamic linking with spdlog to avoid duplicate linking issues.
- Added Time class for delta time calculations and frame time management.

### Rendering Module (VelopraRenderer)
- Manages rendering-related tasks using OpenGL.
- Interacts with external libraries like GLEW, GLFW, Assimp, and glm.
- Resolved initial linking issues with spdlog through dynamic linking in the Core module.

### Input System Module (VelopraInputSystem) [Ongoing]
- Handles input events and processing.
- Integrated with the Core module for event handling.
- Contains InputUpdateLayer for updating input states.
- Development and integration are ongoing.

### UI Module (VelopraUI)
- Utilizes Qt for creating and managing user interfaces.
- Integrated with the Core and Rendering modules for seamless UI interaction within games.
- Provides tools for developing in-game menus, editors, and custom user interfaces.

### Application Module
- The executable part of the engine, where main application logic resides.
- Initializes and ties together other modules (Core, Renderer, Input System, UI).
- Implements the main loop, managing rendering, input processing, and UI interactions.

## Event Handling
- Event bus and event queue systems for efficient event handling.
- Events are dispatched and processed through these systems for a modular and decoupled architecture.

## Logging System
- Utilizes spdlog for logging, integrated into the Core module.
- Offers various logging levels (trace, info, warn, error, critical).
- Macros for easy logging throughout the engine.

## Time Management
- A Time class introduced for managing time-related functionalities like delta time.
- Ensures consistent frame time calculations across the engine.

## Asset Management Module (Planned)
- Future plans to include an asset management module for handling game assets (textures, models, audio files, scripts).
- Will manage loading, caching, and unloading of resources.

## Challenges and Resolutions
- Faced challenges with spdlog linking, resolved by ensuring dynamic linking and proper CMake configurations.
- Adjusted CMake files and project structure for modular design and inter-module dependencies.

## Future Enhancements
- Integration of physics, audio, and advanced input handling.
- Expansion of the rendering module for more graphics features.
- Implementing a user interface and editor tools.

## Development Environment
- Developed with C++ (C++20 standard).
- Uses CMake for build automation and cross-platform compilation.
- Utilizes Microsoft Visual Studio and vcpkg for package management.

## Getting Started

### Prerequisites

Before starting, ensure you have:
- A C++17 compliant compiler (e.g., GCC, Clang, MSVC).
- [CMake](https://cmake.org/download/) for managing the build process.
- A package manager like [vcpkg](https://github.com/microsoft/vcpkg) (optional, for dependency management).

### Dependencies

Velopra Engine leverages `spdlog` for logging, `GLEW` for OpenGL extension wrangling, `GLM` for mathematics, `Assimp` for model loading and `qt5` for the UI. Use vcpkg or a similar package manager to install these dependencies:

```bash
vcpkg install spdlog glew assimp glm qt5
```

If you're not using a package manager, ensure you include the necessary libraries in your project.

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

To utilize Velopra Engine in your projects, include the core and rendering headers and link against the Velopra Engine libraries.

## Contributing

Contributions are currently closed but will open in the future as the engine evolves.

## License

Velopra Engine is under the MIT License. Refer to the LICENSE file for more information.

## Distribution

Pre-compiled binaries for each release will be available soon.
