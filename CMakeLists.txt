cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(PrimedDB LANGUAGES CXX)


# add_subdirectory(Command)
# add_subdirectory(Compiler)
# add_subdirectory(ErrorHandler)
add_subdirectory(LogLib)
# add_subdirectory(Network)
# add_subdirectory(StorageUnit)
# add_subdirectory(Transaction)

add_subdirectory(Test)
add_subdirectory(PrimedDB)
#添加 Until 到项目中
add_subdirectory(Util)
