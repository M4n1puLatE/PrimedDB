project(Tester)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
find_package(PkgConfig REQUIRED)
add_executable(Tester ${srcs})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(Tester PRIVATE Boost::boost)
target_link_libraries(Tester
    PRIVATE
        LogLib
        Util
        ErrorHandler
        Command
        Compiler
        PkgConfig::gmp
)