
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(Command STATIC ${srcs})
target_include_directories(Command PUBLIC include)