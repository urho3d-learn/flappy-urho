# https://urho3d-doxygen.github.io/doxygen/_using_library.html

# Минимальная версия CMake
cmake_minimum_required (VERSION 3.15)

# Название проекта (solution в Visual Studio)
project (angelscript_vs_cpp)

# Путь к скомпилированному движку
set (ENV{URHO3D_HOME} ${CMAKE_SOURCE_DIR}/../../engine/build_vs)

# Путь к модулям CMake
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../../engine/repo/cmake/Modules)

# Получаем доступ к функциям из модуля UrhoCommon.cmake
include (UrhoCommon)

# Выполняем скрипт CMakeLists.txt из папки src
add_subdirectory(src)
