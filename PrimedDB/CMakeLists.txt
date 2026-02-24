# 复制运行时依赖（Windows DLL等）
# PrimedDB 主程序
file(GLOB MAIN_SOURCES "*.cpp")
file(GLOB MAIN_HEADERS "*.h")

# 创建可执行文件
add_executable(PrimedDB ${MAIN_SOURCES} ${MAIN_HEADERS})

# 设置目标属性
target_include_directories(PrimedDB
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(PrimedDB PRIVATE cxx_std_20)

# 链接所有子库
target_link_libraries(PrimedDB
    PRIVATE
        LogLib
        Util
        ErrorHandler
        Command
        Compiler
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
