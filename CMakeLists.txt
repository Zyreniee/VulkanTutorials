cmake_minimum_required(VERSION 3.10)
project(VulkanTutorials VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect only the cross-platform 'lve' tutorial sources
file(GLOB LVE_SOURCES
    "${CMAKE_SOURCE_DIR}/lve_*.cpp"
)
set(SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/first_app.cpp
    ${LVE_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

# Find Vulkan
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
endif()

# Find GLFW (via pkg-config) and link it
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
if(GLFW_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_LIBRARIES})
else()
    message(WARNING "GLFW not found via pkg-config. Ensure glfw is installed and headers are available.")
endif()

# Output binary to build dir
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

option(BUILD_SHADERS "Compile GLSL shaders with glslc if available" OFF)
option(ENABLE_VALIDATION_LAYERS "Enable Vulkan validation layers" OFF)
set(SHADER_DIR "shaders")
if(ENABLE_VALIDATION_LAYERS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_VALIDATION_LAYERS)
endif()
if(BUILD_SHADERS)
    find_program(GLSLC glslc)
    if(GLSLC)
        file(GLOB GLSL_SHADERS "${CMAKE_SOURCE_DIR}/Shaders/*.vert" "${CMAKE_SOURCE_DIR}/Shaders/*.frag")
        set(SPV_FILES)
        foreach(SH ${GLSL_SHADERS})
            get_filename_component(FNAME ${SH} NAME_WE)
            get_filename_component(EXT ${SH} EXT)
            set(OUT_SPV ${CMAKE_BINARY_DIR}/${SHADER_DIR}/${FNAME}${EXT}.spv)
            add_custom_command(
                OUTPUT ${OUT_SPV}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${SHADER_DIR}
                COMMAND ${GLSLC} ${SH} -o ${OUT_SPV}
                DEPENDS ${SH}
            )
            list(APPEND SPV_FILES ${OUT_SPV})
        endforeach()
        add_custom_target(compile_shaders ALL DEPENDS ${SPV_FILES})
        add_dependencies(${PROJECT_NAME} compile_shaders)
    else()
        message(WARNING "glslc not found; set BUILD_SHADERS=OFF or install Vulkan SDK to enable shader compilation")
        # Fall back to copying shaders if glslc isn't available
        add_custom_target(copy_shaders ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Shaders ${CMAKE_BINARY_DIR}/${SHADER_DIR}
            COMMENT "Copying shaders to build directory"
        )
        add_dependencies(${PROJECT_NAME} copy_shaders)
    endif()
else()
    # Default: copy precompiled .spv (and sources) from source tree
    add_custom_target(copy_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Shaders ${CMAKE_BINARY_DIR}/${SHADER_DIR}
        COMMENT "Copying shaders to build directory"
    )
    add_dependencies(${PROJECT_NAME} copy_shaders)
endif()
