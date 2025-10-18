
cmake_minimum_required(VERSION 3.15)	# Проверка версии CMake. Если версия установленой программы старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME Console_Store_Simulator)	# задать значение PROJECT_NAME	 
project("${PROJECT_NAME}")	# установить имя проекта

set(CMAKE_CXX_STANDARD 20)	# устанавливаем 20 стандарт языка

set(SOURCES src/main.cpp src/storage.cpp include/storage.h)

add_executable("${PROJECT_NAME}" "${SOURCES}")	# Сказать программе, что должен быть исполняемый файл main.cpp и другие (по необходимости добавлять)
include_directories(include)