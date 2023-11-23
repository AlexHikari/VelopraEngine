![VelopraLogo](https://github.com/AlexHikari/VelopraEngine/assets/15806836/1892d66b-1832-4eed-a5a4-b2ccd028b48a)

# Velopra Engine

The Velopra Engine is a versatile game engine designed for developing both 2D and 3D games. This project is primarily built for research purposes and as a learning platform for game engine architecture and advanced C++ techniques.

## Core Features

- **Vector2, Vector3, Matrix4, and Quaternion Structures**: Efficient mathematical computations for 2D/3D graphics and physics.
- **Optimized Arithmetic Operations**: High-performance operations for vectors, matrices, and quaternions, crucial for performance-critical applications.
- **Memory Management Utilities**: Robust tools for dynamic allocation, deallocation, and aligned memory operations, ensuring efficient resource management.
- **Integrated Logging System**: Streamlined error reporting and debugging, utilizing spdlog for efficient and flexible logging.
- **Rendering Module**: Advanced module supporting shader management, mesh processing, texture handling, and more, using OpenGL. Future plans include support for Vulkan, Metal, and DirectX to cater to a wider range of platforms and performance needs.
- **Qt for UI Development**: Utilizes Qt for creating sophisticated and responsive user interfaces, seamlessly integrated with the core engine for in-game and tool UIs.
- **Platform Agnostic Design**: Engineered to be cross-platform, ensuring compatibility with various operating systems and hardware configurations. This design philosophy extends to all aspects of the engine, from core functionalities to UI elements.

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

### Input System Module (VelopraInputSystem)
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
- Initializes and ties together other modules (Core, Renderer, Input System, UI...).
- Implements the main loop, managing rendering, input processing, and UI interactions.

## Event Handling
- Event bus and event queue systems for efficient event handling.
- Events are dispatched and processed through these systems for a modular and decoupled architecture.

## Logging System
- Utilizes spdlog for logging, integrated into the Core module.
- Offers various logging levels (trace, info, warn, error, critical).
- Macros for easy logging throughout the engine.

## Asset Management Module (Planned)
- Future plans to include an asset management module for handling game assets (textures, models, audio files, scripts).
- Will manage loading, caching, and unloading of resources.

## Future Enhancements
- Integration of **physics**, **audio**, and advanced input handling.
- Expansion of the rendering module for more graphics features.
- Implementing a user interface and editor tools.
- **Support for Multiple Rendering Libraries**: Plans to include support for Vulkan, Metal, and DirectX, enabling developers to leverage the engine's capabilities across different graphics APIs and platforms.
- **Expansion of Platform Support**: Continuous efforts to ensure the engine runs efficiently on various platforms, maintaining its platform-agnostic nature.

## Development Environment
- Developed with C++ (C++20 standard).
- Uses CMake for build automation and cross-platform compilation.
- Utilizes Microsoft Visual Studio and vcpkg for package management.

## Getting Started

### Prerequisites

Before starting, ensure you have:
- A C++20 compliant compiler (e.g., GCC, Clang, MSVC).
- [CMake](https://cmake.org/download/) for managing the build process.

### Setting Up Dependencies

The Velopra Engine uses several dependencies, including `spdlog` for logging, `GLEW` for OpenGL extension wrangling, `GLM` for mathematics, `Assimp` for model loading, and `Qt5` for the UI. The setup process will automatically handle the installation of these dependencies using vcpkg.

To set up your environment for the Velopra Engine, follow these steps:

1. Clone the Velopra Engine repository:
   ```bash
   git clone https://github.com/AlexHikari/VelopraEngine.git
    ```
2. Navigate to the cloned directory:
   ```bash
   cd VelopraEngine
   ```
3. Run the setup script:
    - On Windows:
   ```bash
   setup.bat
   ```
   - On Unix-based systems:
   ```bash
   sh setup.sh
   ```
This script will automatically download and install vcpkg locally in your project directory and use it to install the necessary dependencies.

### Building the Project

The Velopra Engine uses `CMakePresets.json` to define build configurations. To build the project using these presets, follow these steps:

1. Navigate to the project's root directory (where `CMakePresets.json` is located).
2. To configure the project using a specific preset, run:
   ```bash
   cmake --preset <preset-name>
   ```
   Replace <preset-name> with the desired preset name, such as x64-debug or x64-release.
3. To build the project using the configured preset, run:
   ```bash
   cmake --build --preset <preset-name>
   ```
   For example, to build the project with the x64-debug preset, you would run:
   ```bash
   cmake --preset x64-debug
   cmake --build --preset x64-debug
   ```
This ensures that the build process is consistent with the configurations defined in Visual Studio, allowing for a more unified development experience across different platforms and environments.

## Contributing

Contributions are currently closed but will open in the future as the engine evolves.

## License

Velopra Engine is under the MIT License. Refer to the LICENSE file for more information.

## Distribution

Pre-compiled binaries for each release will be available soon.
