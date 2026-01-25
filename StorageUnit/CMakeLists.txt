file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(StorageUnit STATIC ${srcs})
target_include_directories(StorageUnit PUBLIC include)