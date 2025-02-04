cmake_minimum_required(VERSION 3.10)

# Set Clang as the compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(ScreenExtender)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set uWebSockets paths
set(UWEBSOCKETS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/uWebSockets/src/")
set(UWEBSOCKETS_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/uWebSockets/uSockets/uSockets.a")
message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}/lib/uWebSockets/src/")


# Enable Objective-C++
enable_language(OBJCXX)

# Find required packages
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

#Find dependencies for uWebSockets
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)


# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/output)

# Add source files
set(SOURCE_FILES
    src/main.cpp
    lib/ConnectionCodeGeneration.cpp
    src/WallpaperCapture.mm
    lib/Communication.cpp
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})


# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
    ${UWEBSOCKETS_INCLUDE_DIR}
)


target_link_libraries(${PROJECT_NAME} 
    ${wxWidgets_LIBRARIES}
    ${UWEBSOCKETS_LIBRARIES}  # Add uWebSockets libraries
    OpenSSL::SSL
    OpenSSL::Crypto
    ZLIB::ZLIB
    "-framework Cocoa"  # Add Cocoa framework for macOS
)

