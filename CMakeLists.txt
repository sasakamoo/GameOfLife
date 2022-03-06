# CMake for MinGW Makefiles
cmake_minimum_required(VERSION 3.7)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

set(Executable ${PROJECT_NAME})
set(SourceDir src)

file(GLOB_RECURSE SourceFiles ${SourceDir}/*.cpp)

add_executable(${Executable} ${SourceFiles})

if (WIN32)
    target_link_libraries(${Executable} ${WinSDK})
    target_link_libraries(${Executable} "-lopengl32")
    target_link_libraries(${Executable} "-lgdiplus")
    target_link_libraries(${Executable} "-lShlwapi")
    target_link_libraries(${Executable} "-ldwmapi")
endif (WIN32)