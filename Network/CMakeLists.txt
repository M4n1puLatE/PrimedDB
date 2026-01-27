file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(Network STATIC ${srcs})
target_include_directories(Network PUBLIC include)