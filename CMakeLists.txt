cmake_minimum_required(VERSION 3.18)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(PrimedDB LANGUAGES CXX)



# add_subdirectory(Command)
# add_subdirectory(Compiler)
add_subdirectory(ErrorHandler)

# add_subdirectory(Network)
# add_subdirectory(StorageUnit)
# add_subdirectory(Transaction)
add_subdirectory(Util)
add_subdirectory(LogLib)
add_subdirectory(Tester)
add_subdirectory(PrimedDB)
#添加 Until 到项目中

