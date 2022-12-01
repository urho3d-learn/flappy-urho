# Название таргета (экзешник игры, проект в Visual Studio)
set (TARGET_NAME angelscript_vs_cpp)

# Создаём список исходных файлов для таргета
# RECURSE - исходники будут искаться также в подпапках
# GROUP - Visual Studio будет отображать файлы как есть, а не раскидывать cpp- и h-файлы в разные категории
define_source_files (GLOB_CPP_PATTERNS *.cpp GLOB_H_PATTERNS *.h RECURSE GROUP)

# Указываем папки с ресурсами (CoreData и Data)
define_resource_dirs (GLOB_PATTERNS ${CMAKE_SOURCE_DIR}/../../engine/repo/bin/*Data)

# Создаём таргет
setup_main_executable ()

# В Visual Studio таргет angelscript_vs_cpp будет назначен стартовым вместо ALL_BUILD,
# чтобы не делать это вручную при отладке игры
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})
