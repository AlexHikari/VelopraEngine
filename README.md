![VelopraLogo](https://github.com/AlexHikari/VelopraEngine/assets/15806836/1892d66b-1832-4eed-a5a4-b2ccd028b48a)
<?xml version="1.0" encoding="utf-8"?>
<!-- Generator: Adobe Illustrator 24.0.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->
<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
	 viewBox="0 0 692 1024" style="enable-background:new 0 0 692 1024;" xml:space="preserve">
<g transform="translate(0.000000,1024.000000) scale(0.100000,-0.100000)">
	<path d="M908,7842c-170-1-308-5-308-9s49-99,109-212s265-503,456-866c844-1604,2289-4341,2295-4348c4-5,47,67,95,160
		c49,92,287,546,530,1008c536,1018,677,1287,1552,2955c377,718,687,1308,690,1313c2,4-203,7-456,7h-460l-90-172l-90-173l195-3
		c107-1,194-5,194-8s-38-76-84-162s-185-353-309-592c-302-583-456-879-607-1165c-26-49-148-283-270-520c-123-236-302-583-400-770
		c-432-829-480-923-480-936c0-8-3-9-9-4c-11,13-185,345-795,1515c-44,85-81,160-82,165c-2,6-84,165-184,355s-294,561-432,825
		s-303,581-368,705c-219,419-300,577-300,583c0,4,86,7,191,7c159,0,190,2,187,14c-2,8-41,87-88,175l-85,161l-145-2
		C1280,7846,1077,7844,908,7842z"/>
	<path d="M1998.5,7287.6c40-74,847-1624,1247-2395c120-233,221-423,224-423s47,82,97,183c110,218,248,486,700,1362
		c187,363,398,773,468,910c70,138,150,292,177,343l50,92l-262-2l-261-3l-235-455c-129-250-348-675-486-943l-251-488l-32,58
		c-17,32-189,360-380,728c-192,369-400,767-461,885l-112,215l-261,3l-262,2L1998.5,7287.6z"/>
	<polyline class="st0" points="1501.3,7701.6 1505,7850 1690.9,7493 1584.8,7493 1300,7493 3461,3345 5620,7494 5426,7502 
		5409.1,7493 3460,3767.7 1519.6,7493 	"/>
	<polyline points="856.1,7841.6 1300,7493 1695.2,7493 1505,7850 1300,7493 1154.3,7671.5 	"/>
	<polyline points="5411,7850 5226.5,7493 5620,7494 	"/>
</g>
</svg>
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
