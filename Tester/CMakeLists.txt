project(Tester)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_executable(Tester ${srcs} "src/Tests.cpp")
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Util
        LogLib
)
