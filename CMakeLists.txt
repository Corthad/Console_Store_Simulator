cmake_minimum_required(VERSION 3.28) # Проверка версии CMake. Если версия установленой программы старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME Console_Store_Simulator)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp") # Рекурсивный поиск всех .cpp файлов в src
file(GLOB_RECURSE INCLUDES "include/*.h") # Рекурсивный поиск всех .h файлов в include

add_executable("${PROJECT_NAME}" "${SOURCES}" "${INCLUDES}")
include_directories(include)
