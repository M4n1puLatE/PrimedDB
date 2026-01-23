project("Command")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")

# 如果是库：
add_library("Command" STATIC ${SOURCES})
target_include_directories("Command" PUBLIC include)
