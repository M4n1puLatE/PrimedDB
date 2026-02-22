project(Tester)
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
find_package(Boost REQUIRED CONFIG COMPONENTS 
    system          # Often needed by other components
    filesystem      # Often needed by other components  
    thread          # Needed by Boost.Log
    log             # The core logging library
    log_setup       # For initialization settings
    atomic          # Needed by Boost.Log
    date_time       # Often needed by logging features
    regex           # Sometimes needed by filters/patterns
    chrono          # Needed by some timing features
    serialization   # If using advanced features
)
find_package(cryptopp CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
add_executable(Tester ${srcs})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Util
        LogLib
        ErrorHandler
        Command
        PkgConfig::gmp
        Boost::log
        Boost::log_setup
        Boost::system
        Boost::thread
        Boost::filesystem
        Boost::date_time
        Boost::chrono
        Boost::atomic
        Boost::regex
)