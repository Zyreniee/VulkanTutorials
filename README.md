<div align="center">

# Core Vulkan Tutorials

**Incremental Learning Workspace for Bare-Metal Vulkan & C++**

<p>
  <img src="https://img.shields.io/badge/Vulkan-C40000?style=for-the-badge&logo=vulkan&logoColor=white" />
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Active_Development-4EAA25?style=for-the-badge" />
</p>


</div>

---

## About This Workspace

A C++ Vulkan learning repository focused on building fundamentals through small, incremental experiments. 

Unlike higher-level APIs, Vulkan demands strict control over every aspect of the GPU. This repository serves as a learning workspace where code structure and abstractions will actively evolve as new topics are introduced, and older components are refactored for better performance and architectural integrity.

## Project Scope

**What you can expect to find here:**
- Vulkan initialization (Instance, Validation Layers, Physical/Logical Device selection).
- Swap chain lifecycle management (Recreation on window resize, surface capabilities, image views).
- Graphics pipeline architecture (Fixed-function state manipulation, render passes, and attachments).
- Low-level execution (Command buffers, queues, and strict synchronization primitives).
- Shader integration (GLSL compiled to SPIR-V byte-code).

**Non-goals (for now):**
- Providing a stable, production-ready Engine API.
- Cross-platform build systems (Currently optimized for Windows/Visual Studio).
- Long-term backward compatibility between commits.

---

## Build Instructions (Windows / Visual Studio)

### Prerequisites
- A Vulkan-capable GPU with up-to-date drivers.
- **Vulkan SDK** installed (Required for validation layers and shader compiler tools).
- **Visual Studio** (x64 toolchain).

### Build Steps
1. Open `Vulkan.sln` in Visual Studio.
2. Select the `x64` architecture and either `Debug` or `Release` mode.
3. Build and run the startup project.

*Note: If the build system cannot find Vulkan headers or libraries, verify that the Vulkan SDK is correctly installed and your environment variables are configured properly.*

---

## Shader Compilation (GLSL to SPIR-V)

Vulkan does not consume raw GLSL text files; it requires compiled SPIR-V binaries. All shader source files are located in the `Shaders/` directory.

- **Windows Users:** Run the provided `compile.bat` script to automate the build process.
- **Manual Compilation:** Alternatively, use the `glslc` executable provided by the Vulkan SDK to compile `.vert` and `.frag` files into `.spv` outputs.

Ensure that the generated `.spv` files remain in the location expected by the application runtime.

---

## Repository Layout

```text
.
├── Shaders/              # GLSL source files and compiled SPIR-V binaries
├── lve_*.{hpp,cpp}       # Vulkan wrapper classes and core abstractions
├── main.cpp              # Application entry point and primary demo runner
└── Vulkan.sln            # Visual Studio solution file
