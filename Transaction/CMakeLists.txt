file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(Test STATIC ${srcs})
target_include_directories(Test PUBLIC include)