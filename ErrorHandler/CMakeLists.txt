project(ErrorHandler)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(ErrorHandler STATIC ${srcs})
target_include_directories(ErrorHandler PUBLIC include)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Util
        LogLib
)