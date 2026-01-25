file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(Util STATIC ${srcs})
target_include_directories(Util PUBLIC include)
