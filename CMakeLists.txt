cmake_minimum_required(VERSION 3.20)
project(sandbox LANGUAGES CXX)

# ---------------
# Global settings
# ---------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Disable compiler-specific language extensions (enforce strict ISO C++:
# -std=c++XX instead of -std=gnu++XX)
set(CMAKE_CXX_EXTENSIONS OFF)

# Supported compilers
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}."
                      "Only GCC and Clang are supported.")
endif()

# Default to Release if not set (single-config generators)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "" FORCE)
endif()

add_executable(main src/main.cpp src/utils.hpp src/utils.cpp)

target_include_directories(main SYSTEM
                           PRIVATE ${CMAKE_SOURCE_DIR}/submodules/lyra/include)

target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Wconversion
                                    -Werror)
