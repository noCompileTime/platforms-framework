cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

project(GLFW VERSION 3.5.0 LANGUAGES C HOMEPAGE_URL "https://www.glfw.org/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

string(COMPARE EQUAL "." "${CMAKE_SOURCE_DIR}" GLFW_STANDALONE)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" ${GLFW_STANDALONE})
option(GLFW_BUILD_TESTS "Build the GLFW test programs" ${GLFW_STANDALONE})

include(GNUInstallDirs)
include(CMakeDependentOption)

cmake_dependent_option(GLFW_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)

cmake_dependent_option(GLFW_USE_HYBRID_HPG "Force use of high-performance GPU on hybrid systems" OFF "WIN32" OFF)
cmake_dependent_option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON "MSVC" OFF)

set(GLFW_LIBRARY_TYPE "${GLFW_LIBRARY_TYPE}" CACHE STRING "Library type override for GLFW (SHARED, STATIC, OBJECT, or empty to follow BUILD_SHARED_LIBS)")

if (GLFW_LIBRARY_TYPE)
    if (GLFW_LIBRARY_TYPE STREQUAL "SHARED")
        set(GLFW_BUILD_SHARED_LIBRARY TRUE)
    else()
        set(GLFW_BUILD_SHARED_LIBRARY FALSE)
    endif()
else()
    set(GLFW_BUILD_SHARED_LIBRARY ${BUILD_SHARED_LIBS})
endif()

list(APPEND CMAKE_MODULE_PATH "${GLFW_SOURCE_DIR}/CMake/modules")

find_package(Threads REQUIRED)

#--------------------------------------------------------------------
# Apply Microsoft C runtime library option
# This is here because it also applies to tests and examples
#--------------------------------------------------------------------
if (MSVC AND NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

#--------------------------------------------------------------------
# Create generated files
#--------------------------------------------------------------------
include(CMakePackageConfigHelpers)

set(GLFW_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/glfw3")

configure_package_config_file(CMake/glfw3Config.cmake.in
                              src/glfw3Config.cmake
                              INSTALL_DESTINATION "${GLFW_CONFIG_PATH}"
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(src/glfw3ConfigVersion.cmake
                                 VERSION ${GLFW_VERSION}
                                 COMPATIBILITY SameMajorVersion)

#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------
add_subdirectory(src)

if (GLFW_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (GLFW_BUILD_TESTS)
    add_subdirectory(tests)
endif()