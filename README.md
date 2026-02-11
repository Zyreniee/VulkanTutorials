# VulkanTutorials

A C++ Vulkan learning repository focused on building fundamentals through small, incremental experiments:
instance/device setup, swap chain management, graphics pipeline creation, command buffers, synchronization, and GLSL shaders.

This is a learning workspace. Code structure and abstractions will evolve as new topics are added and old parts are refactored.

## Scope

What you can expect to find here:
- Vulkan initialization (instance, validation layers, physical/logical device)
- Swap chain lifecycle handling (recreate on resize, surface capabilities, image views)
- Graphics pipeline setup (shaders, fixed-function state, render pass / attachments)
- Command buffers, queues, and synchronization primitives
- GLSL shaders compiled to SPIR-V

Non-goals (for now):
- A stable engine API
- Cross-platform build system
- Long-term backward compatibility between commits

## Build (Windows / Visual Studio)

### Prerequisites
- Vulkan-capable GPU and driver
- Vulkan SDK installed (includes validation layers and shader compiler tools)
- Visual Studio (x64 toolchain)

### Steps
1. Open `Vulkan.sln` in Visual Studio.
2. Select `x64` + `Debug` or `Release`.
3. Build and run the startup project.

If the build cannot find Vulkan headers/libraries, verify that the Vulkan SDK is installed correctly and your environment is configured.

## Shader compilation (GLSL -> SPIR-V)

GLSL shaders live under `Shaders/`. Compile them to SPIR-V before running the application.

- Use the provided script (`compile.bat`) if you are on Windows.
- Alternatively, use `glslc` from the Vulkan SDK to compile `.vert/.frag` files into `.spv` outputs.

Keep generated `.spv` files in the location expected by the application at runtime.

## Repository layout (high level)

- `Shaders/`           Shader sources and SPIR-V outputs
- `lve_*.{hpp,cpp}`    Vulkan wrappers/abstractions used during learning
- `main.cpp`           Current entry point / demo runner
- `Vulkan.sln`         Visual Studio solution

## Notes

This repository is intentionally iterative:
- Commits may contain partial work while a feature is being explored.
- Refactors are expected as understanding improves.
- If you are using this as reference, prefer reading the latest commit on `main`.

## References

- Vulkan Specification and official resources: https://www.khronos.org/vulkan/
- Vulkan SDK (LunarG): https://vulkan.lunarg.com/
- Vulkan validation layers: https://github.com/KhronosGroup/Vulkan-ValidationLayers

## License

No license file is provided in this repository at the moment.
If you plan to reuse or redistribute any part of this code, add an explicit license first.
