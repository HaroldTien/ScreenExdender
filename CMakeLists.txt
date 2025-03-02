cmake_minimum_required(VERSION 3.10)

# Set Clang as the compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(ScreenExtender)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Enable Objective-C++
enable_language(OBJCXX)

# Find required packages
set(wxWidgets_ROOT_DIR "/opt/homebrew/opt/wxwidgets")
set(wxWidgets_CONFIG_EXECUTABLE "${wxWidgets_ROOT_DIR}/bin/wx-config")
find_package(wxWidgets REQUIRED COMPONENTS core base)
if(wxWidgets_FOUND)
    message("wxWidgets found")
    include(${wxWidgets_USE_FILE})  
else()
    message(FATAL_ERROR "wxWidgets not found")
endif()


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
    lib/WebSockets/src/WebSocketServer.cpp
    lib/WebSockets/src/SHA1.cpp
    lib/WebSockets/src/Base64.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} 
    ${wxWidgets_LIBRARIES}
    "-framework Cocoa"  # Add Cocoa framework for macOS
)

