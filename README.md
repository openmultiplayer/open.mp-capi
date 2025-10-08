# open.mp C API

A single-header C API for [open.mp](https://www.open.mp/) (Open Multiplayer), providing a comprehensive interface to create open.mp components and interact with the server.

## Overview

This library provides a complete C API for open.mp server functionality, allowing you to create components in C or any language that supports C FFI (Foreign Function Interface). The API covers all major aspects of the open.mp server including:

- **Players**: Player management, properties, actions, and state
- **Vehicles**: Vehicle creation, control, and modification
- **Objects**: Static and player-attached objects
- **Actors**: NPC actors with animations and properties
- **Checkpoints**: Race checkpoints and regular checkpoints
- **TextDraws**: 2D text drawing for HUD elements
- **TextLabels**: 3D text labels in the game world
- **Pickups**: Collectible items in the world
- **GangZones**: Territory marking and management
- **Menus**: Interactive menu systems
- **Dialogs**: Player dialog interfaces
- **Classes**: Player class/spawn configurations
- **Custom Models**: Custom model management
- **Events**: Event system for hooking into server events
- **Configuration**: Server configuration access
- **Core**: Core server functionality and utilities

## Features

- **Header-only**: Single header file with complete API definitions
- **Cross-platform**: Supports Windows and Unix-like systems (Linux, macOS, etc.)
- **FFI-friendly**: Can be used from any language supporting C FFI (Python, Rust, Go, etc.)
- **Complete API coverage**: Provides access to all open.mp server functionality
- **Dynamic loading**: Built-in support for dynamic library loading on both Windows and Unix

## Usage

### Basic Setup

1. Include the header file in your C/C++ project:

```c
#include "ompcapi.h"
```

2. Initialize the API by creating an `OMPAPI_t` instance and calling `omp_initialize_capi`:

```c
#include "ompcapi.h"

struct OMPAPI_t api;

int main() 
{
    // Initialize the API - this loads the $CAPI library and all functions
    if (!omp_initialize_capi(&api))
    {
        // Initialization failed - library not found or functions couldn't be loaded
        printf("Failed to initialize open.mp C API\n");
        return 1;
    }

    // Now you can use the API
    // Example: Create an actor
    int actor_id;
    void* actor = api.Actor.Create(123, 0.0f, 0.0f, 3.0f, 0.0f, &actor_id);

    return 0;
}
```

The `omp_initialize_capi` function:
- Returns `true` if initialization succeeds
- Returns `false` if the library cannot be loaded or if API functions cannot be found
- Automatically loads the appropriate library (`$CAPI.dll` on Windows, `$CAPI.so` on Unix)
- Populates the `OMPAPI_t` structure with all available API functions

### Using with CMake

Add this repository as a subdirectory:

```cmake
add_subdirectory(open.mp-capi)
target_link_libraries(your_component PRIVATE ompcapi)
```

## API Documentation

The complete API documentation is available in the `apidocs/` directory:
- `api.json`: Complete JSON specification of all API functions
- `events.json`: Event system documentation

## Project Structure

```
open.mp-capi/
├── include/
│   └── ompcapi.h       # Main header file with complete API
├── apidocs/
│   ├── api.json        # API function specifications
│   └── events.json     # Event system specifications
├── CMakeLists.txt      # CMake configuration
├── LICENSE.md          # Mozilla Public License 2.0
└── README.md           # This file
```

## License

This project is licensed under the Mozilla Public License Version 2.0. See [LICENSE.md](LICENSE.md) for details.